procedure TTSW10.formactivate(Sender: TObject); { $0044280C }
var
  Path: string;
  NameBuffer: string[255];
begin
  if PortableInstallation then
  begin
    ActivatePortableInstallation(Self);
    Exit;
  end;
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
    NameBuffer := Memo12.Lines[2];
    PlayerName := NameBuffer;
    Path := Memo12.Lines[1] + '\data\center.bmp';
    Image1.Picture.LoadFromFile(Path);
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
  if K5.Checked then
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
  if not K5.Checked then
    itemlive;
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
      GameOptions[5] := 0;
    syokidata0;
    K5.Checked := GameOptions[5] = 1;
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
var
  I, Factor: Longint;
  Items: array[0..14] of TImage;
  ItemValues: array[0..14] of Longint;
begin
  CancelBattle;
  PrepareSceneGraphics(Self);
  InitializeAudio(Self);
  MouseRepeat := 0;
  DrawIndex := 1;
  SceneReady := 1;
  PreviousCell := 0;
  HeroCell := Hero.y * 11 + Hero.x;
  TileClass := 0;
  FacingRequest := 1;
  DialogueStage := 0;
  EventCursor := 0;
  EventPaused := False;
  if not Timer4.Enabled then
  begin
    mhyouji;
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
  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image6.Width * 11;
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
    Items[0] := Image6;
    Items[1] := Image5;
    Items[2] := Image4;
    Items[3] := Image7;
    Items[4] := Image8;
    Items[5] := Image9;
    Items[6] := Image10;
    Items[7] := Image11;
    Items[8] := Image12;
    Items[9] := Image13;
    Items[10] := Image14;
    Items[11] := Image15;
    Items[12] := Image16;
    Items[13] := Image17;
    Items[14] := Image18;
    ItemValues[0] := Hero.hero_orb;
    ItemValues[1] := Hero.wisdom_orb;
    ItemValues[2] := Hero.flight_orb;
    ItemValues[3] := Hero.cross;
    ItemValues[4] := Hero.elixir;
    ItemValues[5] := Hero.mattock;
    ItemValues[6] := Hero.bomb;
    ItemValues[7] := Hero.warp_staff;
    ItemValues[8] := Hero.ascent_wing;
    ItemValues[9] := Hero.descent_wing;
    ItemValues[10] := Hero.dragon_slayer;
    ItemValues[11] := Hero.snow_crystal;
    ItemValues[12] := Hero.magic_key;
    ItemValues[13] := Hero.super_mattock;
    ItemValues[14] := Hero.lucky_gold;
    for I := 0 to 14 do
      Items[I].Visible := True;
    { Cross, Dragon Slayer and Lucky Gold are passive. Warp Staff stores charges. }
    for I := 0 to 14 do
      if not (I in [3, 10, 14]) and ((ItemValues[I] = 1) or ((I = 7) and (ItemValues[I] > 0))) then
        Items[I].Enabled := True;
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
  DrawX := ((Hero.y * 11 + Hero.x) * Image6.Width) mod (Image6.Width * 11);
  { Startup divides by tile height; the hero renderer recomputes final coordinates. }
  DrawY := ((Hero.y * 11 + Hero.x) div (Image6.Height * 11)) * Image6.Height;
  if not Timer4.Enabled then
    yusyahyouji1;
  if Hero.zeno_sealed = 0 then
  begin
    Monsters[15].HP := 8000;
    Monsters[15].Attack := 5000;
    Monsters[15].Defense := 1000;
  end
  else if Hero.zeno_sealed = 1 then
  begin
    { Sealed Zeno uses one-tenth stats multiplied by the current cycle factor. }
    Factor := Hero.cycle_factor_minus_one + 1;
    Monsters[15].HP := Factor * 800;
    Monsters[15].Attack := Factor * 500;
    Monsters[15].Defense := Factor * 100;
  end;
end;
