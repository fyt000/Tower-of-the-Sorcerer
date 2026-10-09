procedure TTSW10.formactivate(Sender: TObject); { $0044280C }
var
  Path: string;
  NameBuffer: string[255];
begin
  Hero.Word628 := -4;
  Hero.cycle_factor_minus_one := 0;
  Hero.later_cycle := 0;
  Hero.Word680 := 12;
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
    { The Ghidra function export omits this handler. Recovered from original
      instructions $004429E6..$00442A9D, reached through $004429E1. }
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
  BlockRead(SettingsFile, OriginalOptions, 10);
  CloseFile(SettingsFile);
  syokidata0;
  if K5.Checked then
  begin
    Timer4.Enabled := True;
    optionl1;
    StrikeCount := 0;
    Timer1.Enabled := False;
  end
  else optionl1;
  syokidata;
  syokidata2;
  if not K5.Checked then itemlive;
end;
