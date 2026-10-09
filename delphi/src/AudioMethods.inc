procedure InitializeAudio(Form: TTSW10);
var
  I: Integer;
  Player: TMediaPlayer;
  Name: string;
begin
  for I := 1 to 4 do
  begin
    Player := TMediaPlayer(Form.FindComponent('MediaPlayer' + IntToStr(I)));
    Player.DeviceType := dtWaveAudio;
    case I of
      1: Name := 'open.wav';
      2: Name := 'get.wav';
      3: Name := 'taisen.wav';
      4: Name := 'zeno.wav';
    end;
    Name := AssetDirectory + '\wav\' + Name;
    try
      Player.Close;
      Player.FileName := Name;
      if FileExists(Name) then
        Player.Open;
    except
      on E: EMCIDeviceError do
      begin
        Inc(AudioFailures);
        Player.Close;
      end;
    end;
  end;
  Form.MediaPlayer6.DeviceType := dtWaveAudio;
end;

procedure PlayEffect(Form: TTSW10; Index: Integer);
var
  Player: TMediaPlayer;
  Name: string;
begin
  if Hero.effects_muted <> 0 then
    Exit;
  Inc(EffectRequests);
  LastEffect := Index;
  if (Index >= 1) and (Index <= 4) then
    Player := TMediaPlayer(Form.FindComponent('MediaPlayer' + IntToStr(Index)))
  else if (Index >= 7) and (Index <= 10) then
  begin
    { Player 6 is shared by the four scene effects; close before changing files. }
    Player := Form.MediaPlayer6;
    case Index of
      7: Name := '3f.wav';
      8: Name := '20f.wav';
      9: Name := 'kai.wav';
      10: Name := 'kai2.wav';
    end;
    Name := AssetDirectory + '\wav\' + Name;
    if not FileExists(Name) then
    begin
      Inc(AudioFailures);
      Exit;
    end;
    Player.Close;
    Player.FileName := Name;
    try
      Player.Open;
    except
      on E: EMCIDeviceError do
      begin
        Inc(AudioFailures);
        Player.Close;
        Exit;
      end;
    end;
  end
  else
    Exit;
  if Player.DeviceID = 0 then
  begin
    Inc(AudioFailures);
    Exit;
  end;
  try
    Player.Notify := False;
    Player.Rewind;
    { Effects do not need a completion callback. }
    Player.Notify := False;
    Player.Play;
    if Player.Error <> 0 then
    begin
      Inc(AudioFailures);
      Player.Close;
    end;
  except
    on E: EMCIDeviceError do
    begin
      Inc(AudioFailures);
      Player.Close;
    end;
  end;
end;

procedure TTSW10.soundcheck; { $0047C8F8 }
var
  Track: Integer;
begin
  Track := MusicTrackForFloor(Hero.floor);
  if Track <> 0 then
    Hero.music_track := Track;
end;

procedure TTSW10.soundplay; { $0047C2BC }
var
  Name: string;
begin
  { Close/reopen also resets playback to the beginning for the loop callback. }
  MediaPlayer5.Close;
  MediaPlayer5.DeviceType := dtSequencer;
  Name := MusicFileName(Hero.music_track);
  if Name = '' then
    Exit;
  Inc(MusicRequests);
  LastMusic := Hero.music_track;
  MediaPlayer5.FileName := AssetDirectory + '\midi\' + Name;
  if not FileExists(MediaPlayer5.FileName) then
  begin
    Inc(AudioFailures);
    Exit;
  end;
  try
    MediaPlayer5.Open;
    MediaPlayer5.Notify := True;
    MediaPlayer5.Wait := False;
    MediaPlayer5.Play;
    if MediaPlayer5.Error <> 0 then
    begin
      Inc(AudioFailures);
      MediaPlayer5.Close;
    end;
  except
    on E: EMCIDeviceError do
    begin
      Inc(AudioFailures);
      MediaPlayer5.Close;
    end;
  end;
end;

procedure TTSW10.wavon1Click(Sender: TObject); { $0047C20C }
begin
  if Hero.effects_muted = 0 then
    Hero.effects_muted := 1
  else
    Hero.effects_muted := 0;
  GameOptions[7] := Hero.effects_muted;
  wavon1.Checked := Hero.effects_muted = 0;
end;

procedure TTSW10.BGMON1Click(Sender: TObject); { $0047C258 }
begin
  if Hero.music_track <> 0 then
  begin
    MediaPlayer5.Close;
    Hero.music_track := 0;
    GameOptions[6] := 0;
    BGMON1.Checked := False;
  end
  else
  begin
    BGMON1.Checked := True;
    if not Timer4.Enabled then
    begin
      soundcheck;
      soundplay;
    end;
    GameOptions[6] := 1;
  end;
end;

procedure TTSW10.mediaplayer5onnotify(Sender: TObject); { $00482A80 }
begin
  { Close or a replaced command also notifies; only completion should loop. }
  if (MediaPlayer5.NotifyValue = nvSuccessful) and (Hero.music_track <> 0) and BGMON1.Checked then
    soundplay;
end;
