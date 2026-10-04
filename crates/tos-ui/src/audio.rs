//! Original WAV effects and portable synthesis of the extracted MIDI scores.
//! Both backends receive identical PCM; no browser-only music implementation.
use std::{collections::BTreeMap, io::Cursor, sync::Arc};

#[derive(Clone)]
pub struct Pcm {
    pub samples: Arc<Vec<f32>>,
    pub channels: u16,
    pub rate: u32,
}

pub fn decode(bytes: &[u8], midi: bool) -> Result<Pcm, String> {
    if midi {
        return synthesize_midi(bytes);
    }
    let mut reader = hound::WavReader::new(Cursor::new(bytes)).map_err(|e| e.to_string())?;
    let spec = reader.spec();
    let samples = match spec.sample_format {
        hound::SampleFormat::Float => reader
            .samples::<f32>()
            .map(|s| s.map_err(|e| e.to_string()))
            .collect::<Result<Vec<_>, _>>()?,
        hound::SampleFormat::Int => {
            let divisor = (1_i64 << (spec.bits_per_sample - 1)) as f32;
            reader
                .samples::<i32>()
                .map(|s| s.map(|s| s as f32 / divisor).map_err(|e| e.to_string()))
                .collect::<Result<Vec<_>, _>>()?
        }
    };
    Ok(Pcm {
        samples: Arc::new(samples),
        channels: spec.channels,
        rate: spec.sample_rate,
    })
}

/// Small General MIDI-style oscillator synthesizer. Original notes, timing and
/// programs survive; hardware-dependent 1990s MIDI sound banks are not bundled.
pub fn synthesize_midi(bytes: &[u8]) -> Result<Pcm, String> {
    use midly::{MetaMessage, MidiMessage, Timing, TrackEventKind};
    let smf = midly::Smf::parse(bytes).map_err(|e| e.to_string())?;
    let ticks = match smf.header.timing {
        Timing::Metrical(t) => t.as_int() as f64,
        _ => return Err("SMPTE MIDI timing is unsupported".into()),
    };
    let mut events = vec![];
    for track in &smf.tracks {
        let mut tick = 0_u64;
        for event in track {
            tick += u64::from(event.delta.as_int());
            events.push((tick, event.kind));
        }
    }
    events.sort_by_key(|e| e.0);
    let mut programs = [0_u8; 16];
    let mut active = BTreeMap::<(u8, u8), (f64, u8, u8)>::new();
    let mut notes = vec![];
    let (mut previous, mut seconds, mut tempo) = (0_u64, 0_f64, 500_000_f64);
    for (tick, event) in events {
        seconds += (tick - previous) as f64 / ticks * tempo / 1_000_000.0;
        previous = tick;
        if seconds > 180.0 {
            break;
        }
        match event {
            TrackEventKind::Meta(MetaMessage::Tempo(t)) => tempo = t.as_int() as f64,
            TrackEventKind::Midi { channel, message } => {
                let ch = channel.as_int();
                match message {
                    MidiMessage::ProgramChange { program } => {
                        programs[ch as usize] = program.as_int()
                    }
                    MidiMessage::NoteOn { key, vel } if vel.as_int() > 0 => {
                        active.insert(
                            (ch, key.as_int()),
                            (seconds, vel.as_int(), programs[ch as usize]),
                        );
                    }
                    MidiMessage::NoteOn { key, .. } | MidiMessage::NoteOff { key, .. } => {
                        if let Some((start, velocity, program)) = active.remove(&(ch, key.as_int()))
                        {
                            notes.push((start, seconds, key.as_int(), velocity, program, ch));
                        }
                    }
                    _ => {}
                }
            }
            _ => {}
        }
    }
    for ((ch, key), (start, vel, program)) in active {
        notes.push((start, seconds.max(start + 0.15), key, vel, program, ch));
    }
    let rate = 16_000;
    let mut output = vec![0_f32; ((seconds + 1.0).clamp(1.0, 181.0) * rate as f64) as usize];
    for (start, end, key, velocity, program, channel) in notes {
        let frequency = 440.0 * 2.0_f64.powf((f64::from(key) - 69.0) / 12.0);
        let a = (start * rate as f64) as usize;
        let b = ((end + 0.12) * rate as f64) as usize;
        for (i, sample) in output.iter_mut().enumerate().take(b).skip(a) {
            let t = (i - a) as f64 / rate as f64;
            let phase = t * frequency * std::f64::consts::TAU;
            let attack = (t / 0.012).min(1.0);
            let release = ((end + 0.12 - start - t) / 0.12).clamp(0.0, 1.0);
            let decay = if program < 16 {
                (-t * 2.8).exp() * 0.8 + 0.2
            } else {
                1.0
            };
            let wave = if channel == 9 {
                // deterministic percussion, no global RNG
                let noise = ((i
                    .wrapping_mul(1664525)
                    .wrapping_add(key as usize * 1013904223))
                    % 65536) as f64
                    / 32768.0
                    - 1.0;
                (noise * 0.6 + phase.sin() * 0.4) * (-t * 22.0).exp()
            } else {
                match program / 8 {
                    0 | 1 => phase.sin() + 0.24 * (phase * 2.0).sin() + 0.1 * (phase * 3.0).sin(),
                    2 | 3 => phase.sin() + 0.3 * (phase * 3.0).sin(),
                    5..=7 => phase.sin() + 0.25 * (phase * 2.0).sin() + 0.15 * (phase * 4.0).sin(),
                    _ => phase.sin() + 0.15 * (phase * 3.0).sin(),
                }
            };
            *sample +=
                (wave * attack * release * decay * f64::from(velocity) / 127.0 * 0.055) as f32;
        }
    }
    for sample in &mut output {
        *sample = sample.tanh();
    }
    Ok(Pcm {
        samples: Arc::new(output),
        channels: 1,
        rate,
    })
}

pub struct Audio {
    pub enabled: bool,
    pub music_enabled: bool,
    pub volume: f32,
    pub unlocked: bool,
    pub effects_played: u64,
    pub music_name: String,
    pub error: Option<String>,
    cache: BTreeMap<String, Pcm>,
    #[cfg(not(target_arch = "wasm32"))]
    stream: Option<rodio::OutputStream>,
    #[cfg(not(target_arch = "wasm32"))]
    music: Option<rodio::Sink>,
    #[cfg(target_arch = "wasm32")]
    context: Option<web_sys::AudioContext>,
    #[cfg(target_arch = "wasm32")]
    gain: Option<web_sys::GainNode>,
    #[cfg(target_arch = "wasm32")]
    music: Option<web_sys::AudioBufferSourceNode>,
}

impl Default for Audio {
    fn default() -> Self {
        Self {
            enabled: true,
            music_enabled: true,
            volume: 0.55,
            unlocked: false,
            effects_played: 0,
            music_name: String::new(),
            error: None,
            cache: BTreeMap::new(),
            #[cfg(not(target_arch = "wasm32"))]
            stream: None,
            #[cfg(not(target_arch = "wasm32"))]
            music: None,
            #[cfg(target_arch = "wasm32")]
            context: None,
            #[cfg(target_arch = "wasm32")]
            gain: None,
            #[cfg(target_arch = "wasm32")]
            music: None,
        }
    }
}

impl Audio {
    pub fn unlock(&mut self) {
        if self.unlocked {
            return;
        }
        #[cfg(not(target_arch = "wasm32"))]
        match rodio::OutputStreamBuilder::open_default_stream() {
            Ok(mut s) => {
                s.log_on_drop(false);
                self.stream = Some(s);
                self.unlocked = true;
            }
            Err(e) => self.error = Some(e.to_string()),
        }
        #[cfg(target_arch = "wasm32")]
        match web_sys::AudioContext::new() {
            Ok(context) => {
                if let Ok(gain) = context.create_gain() {
                    gain.gain().set_value(self.volume);
                    let _ = gain.connect_with_audio_node(&context.destination());
                    self.gain = Some(gain);
                }
                let _ = context.resume();
                self.context = Some(context);
                self.unlocked = true;
            }
            Err(e) => self.error = Some(format!("WebAudio: {e:?}")),
        }
    }
    pub fn install(&mut self, name: &str, bytes: &[u8]) -> Result<(), String> {
        let pcm = decode(bytes, name.ends_with(".mid"))?;
        self.cache.insert(name.into(), pcm);
        Ok(())
    }
    pub fn has(&self, name: &str) -> bool {
        self.cache.contains_key(name)
    }
    pub fn refresh_volume(&mut self) {
        #[cfg(not(target_arch = "wasm32"))]
        if let Some(m) = &self.music {
            m.set_volume(if self.enabled && self.music_enabled {
                self.volume * 0.6
            } else {
                0.0
            });
        }
        #[cfg(target_arch = "wasm32")]
        if let Some(g) = &self.gain {
            g.gain()
                .set_value(if self.enabled { self.volume } else { 0.0 });
        }
        if !self.music_enabled {
            self.stop_music();
        }
    }
    pub fn play(&mut self, name: &str, music: bool) {
        if !self.unlocked || !self.enabled || (music && !self.music_enabled) {
            return;
        }
        if music && self.music_name == name && self.music.is_some() {
            return;
        }
        let Some(pcm) = self.cache.get(name).cloned() else {
            return;
        };
        if music {
            self.stop_music();
            self.music_name = name.into();
        } else {
            self.effects_played += 1;
        }
        #[cfg(not(target_arch = "wasm32"))]
        if let Some(stream) = &self.stream {
            use rodio::Source;
            let sink = rodio::Sink::connect_new(stream.mixer());
            sink.set_volume(self.volume * if music { 0.6 } else { 1.0 });
            let source =
                rodio::buffer::SamplesBuffer::new(pcm.channels, pcm.rate, (*pcm.samples).clone());
            if music {
                sink.append(source.repeat_infinite());
                self.music = Some(sink);
            } else {
                sink.append(source);
                sink.detach();
            }
        }
        #[cfg(target_arch = "wasm32")]
        if let Some(context) = &self.context {
            let result = (|| -> Result<web_sys::AudioBufferSourceNode, wasm_bindgen::JsValue> {
                let frames = pcm.samples.len() / pcm.channels as usize;
                let buffer =
                    context.create_buffer(pcm.channels as u32, frames as u32, pcm.rate as f32)?;
                for channel in 0..pcm.channels as usize {
                    let samples: Vec<f32> = pcm
                        .samples
                        .iter()
                        .skip(channel)
                        .step_by(pcm.channels as usize)
                        .copied()
                        .collect();
                    buffer.copy_to_channel(&samples, channel as i32)?;
                }
                let source = context.create_buffer_source()?;
                source.set_buffer(Some(&buffer));
                source.set_loop(music);
                let gain = context.create_gain()?;
                gain.gain().set_value(if music { 0.6 } else { 1.0 });
                source.connect_with_audio_node(&gain)?;
                if let Some(master) = &self.gain {
                    gain.connect_with_audio_node(master)?;
                } else {
                    gain.connect_with_audio_node(&context.destination())?;
                }
                source.start()?;
                Ok(source)
            })();
            match result {
                Ok(source) => {
                    if music {
                        self.music = Some(source);
                    }
                }
                Err(e) => self.error = Some(format!("Audio: {e:?}")),
            }
        }
    }
    pub fn stop_music(&mut self) {
        #[cfg(not(target_arch = "wasm32"))]
        if let Some(m) = self.music.take() {
            m.stop();
        }
        #[cfg(target_arch = "wasm32")]
        if let Some(m) = self.music.take() {
            use wasm_bindgen::JsCast;
            let _ = m
                .unchecked_ref::<web_sys::AudioScheduledSourceNode>()
                .stop();
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn midi_score_produces_non_silent_pcm() {
        let bytes = [
            0x4d, 0x54, 0x68, 0x64, 0, 0, 0, 6, 0, 0, 0, 1, 0, 96, 0x4d, 0x54, 0x72, 0x6b, 0, 0, 0,
            12, 0, 0x90, 69, 100, 96, 0x80, 69, 0, 0, 0xff, 0x2f, 0,
        ];
        let pcm = super::synthesize_midi(&bytes).unwrap();
        assert_eq!(pcm.rate, 16_000);
        assert!(pcm.samples.iter().any(|s| s.abs() > 0.01));
        assert!(pcm.samples.iter().all(|s| s.is_finite() && s.abs() <= 1.0));
    }
}
