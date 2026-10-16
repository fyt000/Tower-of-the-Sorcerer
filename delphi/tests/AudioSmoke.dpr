program AudioSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Forms,
  MPlayer,
  MMSystem,
  GameForms,
  GameState,
  GameContent,
  GameCore,
  GameGraphics,
  Audio;
{$R ..\GameResources.res}

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then
    raise Exception.Create(Message);
end;

procedure CheckHeader(const Path, Expected: string);
var
  Stream: TFileStream;
  Header: array[0..3] of Char;
  I: Integer;
begin
  Stream := TFileStream.Create(Path, fmOpenRead or fmShareDenyNone);
  try
    Require(Stream.Size >= 12, 'Audio asset size: ' + Path);
    Stream.ReadBuffer(Header, 4);
    for I := 0 to 3 do
      Require(Header[I] = Expected[I + 1], 'Audio asset header: ' + Path);
  finally
    Stream.Free;
  end;
end;

procedure Run;
const
  FloorCases: array[0..12] of Integer = (0, 1, 10, 11, 20, 21, 30, 31, 40, 41, 49, 50, 51);
  TrackCases: array[0..12] of Integer = (21, 5, 5, 6, 6, 17, 17, 8, 8, 9, 9, 10, 99);
  EffectCases: array[0..7] of Integer = (1, 2, 3, 4, 7, 8, 9, 10);
  BossFloors: array[0..3] of Integer = (20, 25, 40, 49);
  BossTracks: array[0..3] of Integer = (16, 7, 18, 19);
  WaveNames: array[0..7] of string[11] =
      ('open.wav', 'get.wav', 'taisen.wav', 'zeno.wav', '3f.wav', '20f.wav', 'kai.wav', 'kai2.wav');
var
  Form: TTSW10;
  I, Cell, WaveDevices, MidiDevices, Device: Integer;
  Failed: Boolean;
begin
  Require(ParamCount = 1, 'AudioSmoke requires assets directory');
  Application.Initialize;
  LoadGameContent;
  Form := TTSW10.Create(nil);
  MainForm := Form;
  try
    Require(not Form.Visible, 'Audio fixture form must stay hidden');
    AssetDirectory := ParamStr(1);
    Form.Memo12.Lines.Clear;
    Form.Memo12.Lines.Add('.');
    Form.Memo12.Lines.Add(AssetDirectory);
    Form.Memo12.Lines.Add('');
    for I := 0 to 7 do
      CheckHeader(AssetDirectory + '\wav\' + WaveNames[I], 'RIFF');
    for I := 5 to 21 do
      CheckHeader(AssetDirectory + '\midi\' + MusicFileName(I), 'MThd');
    InitializeAudio(Form);
    WaveDevices := 0;
    MidiDevices := 0;
    Hero.effects_muted := 0;
    EffectRequests := 0;
    for I := 0 to 7 do
    begin
      PlayEffect(Form, EffectCases[I]);
      Require(LastEffect = EffectCases[I], 'effect queue routing');
      if I < 4 then
        Device := TMediaPlayer(Form.FindComponent('MediaPlayer' + IntToStr(I + 1))).DeviceID
      else
        Device := Form.MediaPlayer6.DeviceID;
      if Device <> 0 then
        Inc(WaveDevices);
    end;
    Require(EffectRequests = 8, 'All effect requests dispatched');
    Form.wavon1Click(nil);
    Require(
        (Hero.effects_muted = 1) and not Form.wavon1.Checked and (GameOptions[7] = 1),
        'Wave mute option'
    );
    PlayEffect(Form, 1);
    Require(EffectRequests = 8, 'Muted wave effects are suppressed');
    Form.wavon1Click(nil);
    Require((Hero.effects_muted = 0) and Form.wavon1.Checked, 'Wave unmute option');
    for I := 0 to 12 do
    begin
      Hero.floor := FloorCases[I];
      Hero.music_track := 99;
      Form.soundcheck;
      Require(Hero.music_track = TrackCases[I], 'floor music routing');
    end;
    Require(MusicFileName(15) = 'a_005xgw.mid', 'Track 15 filename');
    Require(MusicFileName(17) = 'b_110xgw.mid', 'Track 17 filename');
    Require(MusicFileName(18) = 'a_023xgw.mid', 'Track 18 filename');
    Form.BGMON1.Checked := True;
    for I := 5 to 21 do
    begin
      Hero.music_track := I;
      Form.soundplay;
      Require(
          (Form.MediaPlayer5.DeviceType = dtSequencer)
              and (Form.MediaPlayer5.FileName = AssetDirectory + '\midi\' + MusicFileName(I)),
          'sequencer track routing'
      );
      if Form.MediaPlayer5.DeviceID <> 0 then
        Inc(MidiDevices);
    end;
    Require(MidiDevices = 17, 'All MIDI tracks opened');
    Hero.music_track := 5;
    SendMessage(
        Form.MediaPlayer5.Handle,
        MM_MCINOTIFY,
        MCI_NOTIFY_ABORTED,
        Form.MediaPlayer5.DeviceID
    );
    Require(
        Form.MediaPlayer5.FileName = AssetDirectory + '\midi\' + MusicFileName(21),
        'Aborted MIDI notification must not restart'
    );
    if Form.MediaPlayer5.DeviceID <> 0 then
    begin
      SendMessage(
          Form.MediaPlayer5.Handle,
          MM_MCINOTIFY,
          MCI_NOTIFY_SUCCESSFUL,
          Form.MediaPlayer5.DeviceID
      );
      Require(
          (Form.MediaPlayer5.FileName = AssetDirectory + '\midi\' + MusicFileName(5))
              and (Form.MediaPlayer5.DeviceID <> 0),
          'Successful MIDI notification reopens the selected track'
      );
    end;
    Form.BGMON1Click(nil);
    Require(
        (Hero.music_track = 0)
            and not Form.BGMON1.Checked
            and (GameOptions[6] = 0)
            and (Form.MediaPlayer5.DeviceID = 0),
        'Music off closes sequencer'
    );
    Hero.floor := 20;
    Form.BGMON1Click(nil);
    Require(
        (Hero.music_track = 6) and Form.BGMON1.Checked and (GameOptions[6] = 1),
        'Music on resumes floor track'
    );
    Form.MediaPlayer5.Close;
    { Scene entry must start the boss track immediately. Keep these checks
      in the optional audio suite so ordinary builds do not play music. }
    Form.Memo12.Lines.Clear;
    Form.Memo12.Lines.Add('.');
    Form.Memo12.Lines.Add(AssetDirectory);
    Form.Memo12.Lines.Add('');
    Form.syokidata0;
    Form.Timer4.Enabled := False;
    for I := 0 to 3 do
    begin
      InitializeCycle;
      Hero.floor := BossFloors[I];
      Hero.x := 5;
      Hero.y := 5;
      Hero.facing := 1;
      Hero.effects_muted := 1;
      Hero.music_track := 5;
      for Cell := 2 to 122 do
        Maps[Hero.floor, Cell] := 6;
      EventCursor := 0;
      ContactIndex := 82;
      Form.mevent;
      Require(
          (Hero.music_track = BossTracks[I])
              and (Form.MediaPlayer5.FileName
                  = AssetDirectory + '\midi\' + MusicFileName(BossTracks[I]))
              and (Form.MediaPlayer5.DeviceID <> 0),
          'Scene starts boss music immediately on floor ' + IntToStr(BossFloors[I])
      );
      Form.MediaPlayer5.Close;
      Form.Timer2.Enabled := False;
    end;
    { The thank-you frame opens its literal MIDI path without changing the
      current floor-track word or routing through soundplay. }
    EventCursor := 1;
    EventStack[0].A := 7;
    EventStack[1].B := 0;
    Hero.music_track := 5;
    Form.openning9;
    Require(
        (Hero.music_track = 5)
            and (Form.MediaPlayer5.FileName = AssetDirectory + '\midi\b_014xgw.mid')
            and Form.Image23.ShowHint,
        'Thank-you picture starts its original MIDI file and enables the hint'
    );
    Form.MediaPlayer5.Close;
    AssetDirectory := ParamStr(1) + '\missing-audio-fixture';
    Form.Memo12.Lines[1] := AssetDirectory;
    Hero.music_track := 5;
    Failed := False;
    try
      Form.soundplay;
    except
      on E: EMCIDeviceError do
        Failed := True;
    end;
    Require(
        (Form.MediaPlayer5.DeviceID = 0) and Failed,
        'Missing MIDI asset retains the original MCI error'
    );
    Writeln(
        '{"audio":"passed","wave_requests":8,"midi_tracks":17,"wave_devices":',
        WaveDevices,
        ',"midi_devices":',
        MidiDevices,
        ',"device_or_asset_failures":',
        AudioFailures,
        '}'
    );
  finally
    Form.MediaPlayer5.Close;
    ReleaseGraphics;
    MainForm := nil;
    Form.Free;
  end;
end;

begin
  try
    Run;
  except
    on E: Exception do
    begin
      Writeln(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
