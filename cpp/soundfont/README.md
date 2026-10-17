# GeneralUser GS q1 soundfont

`music.sfo` is the single MIDI soundfont packaged by every build. It is a
Vorbis-compressed derivative of GeneralUser GS 2.0.3 by S. Christian Collins.
The original source is commit `684543d5e5efaef08d02be50dcda8d552478fa60`
of [GeneralUser GS](https://github.com/mrbumpy409/GeneralUser-GS); its
`GeneralUser-GS.sf2` SHA-256 is
`9575028c7a1f589f5770fccc8cff2734566af40cd26ed836944e9a5152688cfe`.
The accompanying license is copied without modification from that commit.

To recreate `music.sfo`, build `sfotool` from the TinySoundFont version pinned in
`cpp/CMakeLists.txt`, then run these commands from the repository root. The file
was encoded with FFmpeg 8.0.1 and `libvorbis` quality 1.

```sh
sfotool GeneralUser-GS.sf2 samples.wav
ffmpeg -i samples.wav -c:a libvorbis -q:a 1 samples-q1.ogg
sfotool GeneralUser-GS.sf2 samples-q1.ogg cpp/soundfont/music.sfo
```

The checked-in `.sfo` SHA-256 is
`0509a47616c426f6bb160c9f3740dea4174448749c6771644c1e6c562c05d8af`.
