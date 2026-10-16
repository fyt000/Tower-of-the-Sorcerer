procedure TTSW10.formactivate(Sender: TObject); { $0044280C }
begin
  Hero.Word628 := -4;
  Hero.cycle_factor_minus_one := 0;
  Hero.later_cycle := 0;
  Hero.save_version := 12;
  MainForm.Caption := 'Tower of the Sorcerer Ver1.2';
  AssetDirectory := GetCurrentDir;
  SetLength(WindowsDirectory, 255);
  GetWindowsDirectory(PChar(WindowsDirectory), 255);
  SetLength(WindowsDirectory, StrLen(PChar(WindowsDirectory)));
  Memo12.Lines.Clear;
  IOPath := WindowsDirectory + '\TSW12.INI';
  try
    Memo12.Lines.LoadFromFile(IOPath);
    SaveDirectory := Memo12.Lines[0];
    AssetDirectory := Memo12.Lines[1];
    PlayerName := Memo12.Lines[2];
    Image1.Picture.LoadFromFile(Memo12.Lines[1] + '\data\center.bmp');
  except
    { Missing settings or artwork resets paths to the working directory. }
    Memo12.Lines.Clear;
    AssetDirectory := GetCurrentDir;
    SaveDirectory := AssetDirectory + '\savedat';
    PlayerName := '';
    Memo12.Lines.Add(SaveDirectory);
    Memo12.Lines.Add(AssetDirectory);
    Memo12.Lines.Add(PlayerName);
    Memo12.Lines.SaveToFile(IOPath);
  end;
  IOPath := Memo12.Lines[0] + '\option.dat';
  AssignFile(SettingsFile, IOPath);
  Reset(SettingsFile, 1);
  BlockRead(SettingsFile, GameOptions, 10);
  CloseFile(SettingsFile);
  syokidata0;
  if K5.Checked = True then
  begin
    Timer4.Enabled := True;
    optionl1;
    StrikeCount := 0;
    Timer1.Enabled := False;
  end
  else
    optionl1;
  syokidata;
  syokidata2;
  if K5.Checked = False then
    itemlive;
end;

procedure TTSW10.PortableActivate(Sender: TObject);
begin
  ActivatePortableInstallation(Self);
end;

{ Installation paths, saved options and initial gameplay state. }

procedure ConfigurePaths(const Assets, Saves: string);
var
  Settings: TStringList;
  SettingsPath: string;
begin
  AssetDirectory := ExpandFileName(Assets);
  if Saves = '' then
  begin
    SaveDirectory := ExtractFilePath(ParamStr(0)) + 'savedat';
    SettingsPath := ExtractFilePath(ParamStr(0)) + 'TSW12.INI';
    if FileExists(SettingsPath) then
    begin
      Settings := TStringList.Create;
      try
        Settings.LoadFromFile(SettingsPath);
        { TSW12.INI stores the save directory on line 0 and player name on line 2. }
        if (Settings.Count > 0) and (Settings[0] <> '') then
          SaveDirectory := ExpandFileName(Settings[0]);
        if Settings.Count > 2 then
          PlayerName := Settings[2];
      finally
        Settings.Free;
      end;
    end;
  end
  else
    SaveDirectory := ExpandFileName(Saves);
  if not DirectoryExists(AssetDirectory) then
    raise Exception.Create('Game asset directory does not exist: ' + AssetDirectory);
  ForceDirectories(SaveDirectory);
  PortableInstallation := True;
end;

procedure ActivatePortableInstallation(Form: TTSW10);
var
  BytesRead: Integer;
begin
  with Form do
  begin
    { Save validation requires this format sentinel. }
    Hero.Word628 := -4;
    Hero.cycle_factor_minus_one := 0;
    Hero.later_cycle := 0;
    Hero.save_version := 12;
    Caption := 'Tower of the Sorcerer Ver1.2';
    Memo12.WordWrap := False;
    Memo12.Lines.Clear;
    { Legacy handlers read save path, asset path and player name from these lines. }
    Memo12.Lines.Add(SaveDirectory);
    Memo12.Lines.Add(AssetDirectory);
    Memo12.Lines.Add(PlayerName);
    IOPath := SaveDirectory + '\option.dat';
    if FileExists(IOPath) then
    begin
      AssignFile(SettingsFile, IOPath);
      Reset(SettingsFile, 1);
      try
        BlockRead(SettingsFile, GameOptions, 10, BytesRead);
      finally
        CloseFile(SettingsFile);
      end;
    end;
    if SkipIntroduction then
      GameOptions[optionIntroduction] := 0;
    syokidata0;
    K5.Checked := GameOptions[optionIntroduction] = 1;
    Timer4.Enabled := K5.Checked;
    optionl1;
    StrikeCount := 0;
    Timer1.Enabled := not Timer4.Enabled;
    syokidata;
    syokidata2;
    if not Timer4.Enabled then
      itemlive;
  end;
end;

procedure TTSW10.syokidata2; { $00454DE8 }
begin
  {$I StartupHidden.inc}
  if Hero.cycle_factor_minus_one = 0 then
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp')
  else
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
  if Hero.cycle_factor_minus_one = 0 then
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp')
  else
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');
  TargetRect := Rect(0, 0, Image2.Width, Image2.Height);
  FrameBitmap.Canvas.CopyRect(TargetRect, Image2.Canvas, TargetRect);
  TargetRect := Rect(Image2.Width, 0, Image2.Width + Image1.Width, Image1.Height);
  SourceRect := Rect(0, 0, Image1.Width, Image1.Height);
  Image23.Width := Image1.Width;
  Image23.Height := Image1.Height;
  if Hero.cycle_factor_minus_one = 0 then
    Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05.bmp')
  else
    Image23.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\title05R.bmp');
  FrameBitmap.Canvas.CopyRect(TargetRect, Image23.Canvas, SourceRect);
  TargetRect :=
      Rect(
          Image2.Width + Image1.Width,
          0,
          Image2.Width + Image1.Width + Image3.Width,
          Image3.Height
      );
  SourceRect := Rect(0, 0, Image3.Width, Image3.Height);
  FrameBitmap.Canvas.CopyRect(TargetRect, Image3.Canvas, SourceRect);
  MediaPlayer1.DeviceType := dtWaveAudio;
  MediaPlayer1.FileName := Memo12.Lines[1] + '\wav\open.wav';
  MediaPlayer1.Open;
  MediaPlayer2.DeviceType := dtWaveAudio;
  MediaPlayer2.FileName := Memo12.Lines[1] + '\wav\get.wav';
  MediaPlayer2.Open;
  MediaPlayer3.DeviceType := dtWaveAudio;
  MediaPlayer3.FileName := Memo12.Lines[1] + '\wav\taisen.wav';
  MediaPlayer3.Open;
  MediaPlayer4.DeviceType := dtWaveAudio;
  MediaPlayer4.FileName := Memo12.Lines[1] + '\wav\zeno.wav';
  MediaPlayer4.Open;
  MediaPlayer6.DeviceType := dtWaveAudio;
  KeysPainted := 0;
  DrawIndex := 1;
  AnimationFrame := True;
  PreviousCell := 0;
  FlightCell := Hero.y * BoardWidth + Hero.x;
  TileClass := 0;
  FacingRequest := Ord(moveUp);
  DialogueStage := stageNone;
  EventCursor := 0;
  if Timer4.Enabled = False then
    mhyouji;
  if Timer4.Enabled = False then
  begin
    Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
    Image1.Visible := True;
    Image2.Visible := True;
    Image3.Visible := True;
    Image19.Visible := True;
    Image20.Visible := True;
    Memo1.Visible := True;
    Memo2.Visible := True;
    Memo3.Visible := True;
    Memo4.Visible := True;
    Memo5.Visible := True;
    Memo6.Visible := True;
    Memo7.Visible := True;
    Memo8.Visible := True;
    Memo9.Visible := True;
    Memo10.Visible := True;
    Memo11.Visible := True;
  end;
  Edit8.Visible := True;
  MapBitmap1.Height := Image6.Height * BoardWidth;
  MapBitmap1.Width := Image6.Width * BoardWidth;
  MapBitmap2.Height := MapBitmap1.Height;
  MapBitmap2.Width := MapBitmap1.Width;
  WorkBitmap1.Height := Image6.Height * 5;
  WorkBitmap1.Width := WorkBitmap1.Width * 3;
  WorkBitmap2.Height := Image6.Height * 2;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  if not Timer4.Enabled then
  begin
    MonsterIndex := -1;
    monshyouji;
    keydisplay;
    itemdisp;
    Image4.Visible := True;
    if Hero.flight_orb = 1 then
      Image4.Enabled := True;
    Image5.Visible := True;
    if Hero.wisdom_orb = 1 then
      Image5.Enabled := True;
    Image6.Visible := True;
    if Hero.hero_orb = 1 then
      Image6.Enabled := True;
    Image7.Visible := True;
    Image8.Visible := True;
    if Hero.elixir = 1 then
      Image8.Enabled := True;
    Image9.Visible := True;
    if Hero.mattock = 1 then
      Image9.Enabled := True;
    Image10.Visible := True;
    if Hero.bomb = 1 then
      Image10.Enabled := True;
    Image11.Visible := True;
    if Hero.warp_staff >= 1 then
      Image11.Enabled := True;
    Image12.Visible := True;
    if Hero.ascent_wing = 1 then
      Image12.Enabled := True;
    Image13.Visible := True;
    if Hero.descent_wing = 1 then
      Image13.Enabled := True;
    Image14.Visible := True;
    Image15.Visible := True;
    if Hero.snow_crystal = 1 then
      Image15.Enabled := True;
    Image16.Visible := True;
    if Hero.magic_key = 1 then
      Image16.Enabled := True;
    Image17.Visible := True;
    if Hero.super_mattock = 1 then
      Image17.Enabled := True;
    Image18.Visible := True;
    disp;
  end;
  if Hero.effects_muted = 0 then
    wavon1.Checked := True;
  if Hero.music_track <> 0 then
  begin
    BGMON1.Checked := True;
    GameOptions[6] := 1;
  end;
  if (Hero.music_track <> 0) and not Timer4.Enabled then
    soundplay;
  DrawX := ((Hero.y * BoardWidth + Hero.x) * Image6.Width) mod (Image6.Width * BoardWidth);
  { Startup divides by tile height; the hero renderer recomputes final coordinates. }
  DrawY := ((Hero.y * BoardWidth + Hero.x) div (Image6.Height * BoardWidth)) * Image6.Height;
  if not Timer4.Enabled then
    yusyahyouji1;
  case Hero.zeno_sealed of
    0:
    begin
      Monsters[15].HP := 8000;
      Monsters[15].Attack := 5000;
      Monsters[15].Defense := 1000;
    end;
    1:
    begin
      { Sealed Zeno uses one-tenth stats multiplied by the current cycle factor. }
      Monsters[15].HP := (Hero.cycle_factor_minus_one + 1) * 800;
      Monsters[15].Attack := (Hero.cycle_factor_minus_one + 1) * 500;
      Monsters[15].Defense := (Hero.cycle_factor_minus_one + 1) * 100;
    end;
  end;
end;
