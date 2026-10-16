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
begin
  case Hero.floor of
    0: Hero.music_track := 21;
    1..10: Hero.music_track := 5;
    11..20: Hero.music_track := 6;
    21..30: Hero.music_track := 17;
    31..40: Hero.music_track := 8;
    41..49: Hero.music_track := 9;
    50: Hero.music_track := 10;
  end;
end;

procedure TTSW10.soundplay; { $0047C2BC }
begin
  MediaPlayer5.Close;
  MediaPlayer5.DeviceType := dtSequencer;
  case Hero.music_track of
    5: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_067xgw.mid';
    6: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_058xgw.mid';
    7: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_008xgw.mid';
    8: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_118xgw.mid';
    9: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_019xgw.mid';
    10: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_018xgw.mid';
    11: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_050xgw.mid';
    12: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_085xgw.mid';
    13: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_032xgw.mid';
    14: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_046xgw.mid';
    15: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_005xgw.mid';
    16: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_007xgw.mid';
    17: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_110xgw.mid';
    18: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\a_023xgw.mid';
    19: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_117xgw.mid';
    20: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\b_014xgw.mid';
    21: MediaPlayer5.FileName := Memo12.Lines[1] + '\midi\A_027xgw.mid';
  end;
  MediaPlayer5.Open;
  MediaPlayer5.Notify := True;
  MediaPlayer5.Play;
end;

procedure TTSW10.wavon1Click(Sender: TObject); { $0047C20C }
begin
  case Hero.effects_muted of
    0:
    begin
      Hero.effects_muted := 1;
      GameOptions[7] := 1;
      wavon1.Checked := False;
    end;
    1:
    begin
      Hero.effects_muted := 0;
      GameOptions[7] := 0;
      wavon1.Checked := True;
    end;
  end;
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
  if MediaPlayer5.NotifyValue = nvSuccessful then
    soundplay;
end;
