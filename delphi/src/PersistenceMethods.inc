var
  RankingCategory: Integer;
  RankingPath: string;
  RankingFile: file;
  RankingOptions: array[0..9] of Byte;
  RankingRows: array[1..12, 1..6] of Longint;
  RankingHero: THeroState;
  RankingMaps: TFloorMaps;

procedure TAboutBox.copyrightonclick(Sender: TObject); { $004345A4 }
begin
  ShellExecute(Handle, 'open', 'http://plaza.across.or.jp/~furano/index.html', '', '', SW_SHOW);
end;

procedure TTSW10.savework; { $0047EADC }
type
  THeroSaveWords = array[0..170] of Longint;
var
  I, Sum, Alternating: Longint;
begin
  Sum := 0;
  Alternating := 0;
  for I := 0 to 163 do
  begin
    Sum := Sum + THeroSaveWords(Hero)[I];
    if I mod 2 = 0 then
      Alternating := Alternating + THeroSaveWords(Hero)[I]
    else
      Alternating := Alternating - THeroSaveWords(Hero)[I];
  end;
  Hero.Word656 := Sum;
  Hero.Word660 := Alternating;
  try
    AssignFile(SettingsFile, IOPath);
    Reset(SettingsFile, 1);
    CloseFile(SettingsFile);
    if MessageDlg('Overwrite. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
    begin
      AssignFile(SettingsFile, IOPath);
      Rewrite(SettingsFile, 1);
      BlockWrite(SettingsFile, Maps, SizeOf(Maps));
      BlockWrite(SettingsFile, Hero, SizeOf(Hero));
      CloseFile(SettingsFile);
      TileClass := 134;
      disp;
    end;
  except
    AssignFile(SettingsFile, IOPath);
    Rewrite(SettingsFile, 1);
    BlockWrite(SettingsFile, Maps, SizeOf(Maps));
    BlockWrite(SettingsFile, Hero, SizeOf(Hero));
    CloseFile(SettingsFile);
    TileClass := 134;
    disp;
  end;
end;

procedure TTSW10.loadwork; { $0047E7D4 }
type
  THeroSaveWords = array[0..170] of Longint;
var
  I, Sum, Alternating: Longint;
begin
  if BGMON1.Checked = True then
    MediaPlayer5.Close;
  AssignFile(SettingsFile, IOPath);
  try
    Reset(SettingsFile, 1);
    BlockRead(SettingsFile, Maps, SizeOf(Maps));
    BlockRead(SettingsFile, Hero, SizeOf(Hero));
    CloseFile(SettingsFile);
    if Hero.Word628 = -4 then
    begin
      Sum := 0;
      Alternating := 0;
      for I := 0 to 163 do
      begin
        Sum := Sum + THeroSaveWords(Hero)[I];
        if I mod 2 = 0 then
          Alternating := Alternating + THeroSaveWords(Hero)[I]
        else
          Alternating := Alternating - THeroSaveWords(Hero)[I];
      end;
      if (Sum = Hero.Word656) and (Alternating = Hero.Word660) then
      begin
        syokidata2;
        TileClass := 133;
        disp;
      end
      else
      begin
        IOPath := Memo12.Lines[0] + '\save0.dat';
        AssignFile(SettingsFile, IOPath);
        Reset(SettingsFile, 1);
        BlockRead(SettingsFile, Maps, SizeOf(Maps));
        BlockRead(SettingsFile, Hero, SizeOf(Hero));
        CloseFile(SettingsFile);
        ShowMessage('Donot use this save data.');
      end;
    end
    else
    begin
      IOPath := Memo12.Lines[0] + '\save0.dat';
      AssignFile(SettingsFile, IOPath);
      Reset(SettingsFile, 1);
      BlockRead(SettingsFile, Maps, SizeOf(Maps));
      BlockRead(SettingsFile, Hero, SizeOf(Hero));
      CloseFile(SettingsFile);
      ShowMessage('Donot use this save data.');
    end;
  except
    TileClass := 115;
    disp;
  end;
  if BGMON1.Checked = True then
  begin
    soundcheck;
    soundplay;
  end;
end;

procedure UpdateFairyRanking(Form: TTSW10; Category: Longint);
var
  Ranking: TRankingTable;
  Names: TRankingNames;
  Row: Integer;
begin
  Hero.Word344 := 0;
  Hero.Word348 := Category;
  if (Category < 1) or (Category > 5) then
    Exit;
  ReadRanking(Category, Hero.Word628, Ranking, Names);
  { The final tie-break deliberately compares attack + defense - row HP
    with row attack, matching the saved ranking rules. }
  for Row := 0 to 9 do
    if (Hero.Word340 > Ranking[Row, 0])
        or ((Hero.Word340 = Ranking[Row, 0])
            and ((Hero.hp > Ranking[Row, 1])
                or ((Hero.hp = Ranking[Row, 1])
                    and (Hero.attack + Hero.defense - Ranking[Row, 1] > Ranking[Row, 2])))) then
    begin
      Hero.Word344 := Row + 1;
      Break;
    end;
  WriteSave(SaveSlotPath(0), True);
end;

procedure TTSW10.Load11Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save1.dat';
  Load11.Checked := True;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load21Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save2.dat';
  Load11.Checked := False;
  Load21.Checked := True;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load31Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save3.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := True;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load41Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save4.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := True;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load51Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save5.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := True;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load61Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save6.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := True;
  Load71.Checked := False;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load71Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save7.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := True;
  Load81.Checked := False;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Load81Click(Sender: TObject);
begin
  if Timer4.Enabled = True then
    Timer4.Enabled := False;
  itemdel;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  IOPath := Memo12.Lines[0] + '\save8.dat';
  Load11.Checked := False;
  Load21.Checked := False;
  Load31.Checked := False;
  Load41.Checked := False;
  Load51.Checked := False;
  Load61.Checked := False;
  Load71.Checked := False;
  Load81.Checked := True;
  loadwork;
  itemlive;
  if Timer1.Enabled = False then
    Timer1.Enabled := True;
end;
procedure TTSW10.Save11Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save1.dat';
  Save11.Checked := True;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save21Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save2.dat';
  Save11.Checked := False;
  Save21.Checked := True;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save31Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save3.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := True;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save41Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save4.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := True;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save51Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save5.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := True;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save61Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save6.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := True;
  Save71.Checked := False;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save71Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save7.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := True;
  Save81.Checked := False;
  savework;
  itemlive;
end;
procedure TTSW10.Save81Click(Sender: TObject);
begin
  itemdel;
  IOPath := Memo12.Lines[0] + '\save8.dat';
  Save11.Checked := False;
  Save21.Checked := False;
  Save31.Checked := False;
  Save41.Checked := False;
  Save51.Checked := False;
  Save61.Checked := False;
  Save71.Checked := False;
  Save81.Checked := True;
  savework;
  itemlive;
end;

procedure TTSW10.OptionSave1Click(Sender: TObject); { $0047D324 }
begin
  if MessageDlg('Save options. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
  begin
    GameOptions[0] := Memo1.Font.Size;
    GameOptions[1] := Edit8.Font.Size;
    GameOptions[2] := 0;
    GameOptions[3] := 2;
    if High1.Checked = True then
      GameOptions[3] := 1;
    if Low1.Checked = True then
      GameOptions[3] := 3;
    IOPath := Memo12.Lines[0] + '\option.dat';
    AssignFile(SettingsFile, IOPath);
    Rewrite(SettingsFile, 1);
    BlockWrite(SettingsFile, GameOptions, 10);
    CloseFile(SettingsFile);
    ShowMessage('Done.');
  end;
end;

procedure TForm2.loadwork; { $0043A3FC }
begin
  RankingPath := MainForm.Memo12.Lines[0] + '\save0.dat';
  AssignFile(RankingFile, RankingPath);
  try
    Reset(RankingFile, 1);
    BlockRead(RankingFile, RankingMaps, SizeOf(RankingMaps));
    BlockRead(RankingFile, RankingHero, SizeOf(RankingHero));
    CloseFile(RankingFile);
  except
  end;
end;

procedure TForm2.scoreload(Category: Byte);
var
  Column, Row, Sum, Invalid: Longint;
begin
  case Category of
    1: RankingPath := MainForm.Memo12.Lines[0] + '\option1.dat';
    2: RankingPath := MainForm.Memo12.Lines[0] + '\option2.dat';
    3: RankingPath := MainForm.Memo12.Lines[0] + '\option3.dat';
    4: RankingPath := MainForm.Memo12.Lines[0] + '\option4.dat';
    5: RankingPath := MainForm.Memo12.Lines[0] + '\option5.dat';
  end;
  try
    AssignFile(RankingFile, RankingPath);
    Reset(RankingFile, 1);
    BlockRead(RankingFile, RankingRows, SizeOf(RankingRows));
    CloseFile(RankingFile);
    Invalid := 0;
    for Row := 1 to 10 do
    begin
      Sum := 0;
      for Column := 1 to 4 do
        Sum := Sum + RankingRows[Row, Column];
      if Sum <> RankingRows[Row, 5] then
        Invalid := 1;
      Sum := 0;
      for Column := 1 to 5 do
        case Column of
          1, 3, 5: Sum := Sum + RankingRows[Row, Column];
          2, 4: Sum := Sum - RankingRows[Row, Column];
        end;
      if Sum <> RankingRows[Row, 6] then
        Invalid := 1;
    end;
    for Row := 1 to 6 do
    begin
      Sum := 0;
      for Column := 1 to 10 do
        Sum := Sum + RankingRows[Column, Row];
      if Sum <> RankingRows[11, Row] then
        Invalid := 1;
      Sum := 0;
      for Column := 1 to 11 do
        case Column of
          1, 3, 5, 7, 9, 11: Sum := Sum + RankingRows[Column, Row];
          2, 4, 6, 8, 10: Sum := Sum - RankingRows[Column, Row];
        end;
      if (Row <> 6) and (Sum <> RankingRows[12, Row]) then
        Invalid := 1;
    end;
    if (Invalid = 0) and (RankingRows[12, 6] div 100 <> RankingHero.Word628) then
      Invalid := 2;
    if (Invalid = 0) and (RankingHero.Word628 * (-100) + RankingRows[12, 6] <> (-1) * Category) then
      Invalid := 2;
    if (Invalid = 1) or (Invalid = 2) then
    begin
      case Invalid of
        1: ShowMessage('Ranking data is abnormal. Use a temporary Ranking.');
        2: ShowMessage('Version of Ranking data is abnormal. Use a temporary Ranking.');
      end;
      case Category of
        1:
        begin
          RankingRows[1, 1] := 100;
          RankingRows[1, 2] := 500;
          RankingRows[1, 3] := 25;
          RankingRows[1, 4] := 25;
          RankingRows[1, 5] := 0;
          RankingRows[1, 6] := 0;
          RankingRows[2, 1] := 90;
          RankingRows[2, 2] := 450;
          RankingRows[2, 3] := 24;
          RankingRows[2, 4] := 24;
          RankingRows[2, 5] := 0;
          RankingRows[2, 6] := 0;
          RankingRows[3, 1] := 80;
          RankingRows[3, 2] := 400;
          RankingRows[3, 3] := 23;
          RankingRows[3, 4] := 23;
          RankingRows[3, 5] := 0;
          RankingRows[3, 6] := 0;
          RankingRows[4, 1] := 70;
          RankingRows[4, 2] := 350;
          RankingRows[4, 3] := 22;
          RankingRows[4, 4] := 22;
          RankingRows[4, 5] := 0;
          RankingRows[4, 6] := 0;
          RankingRows[5, 1] := 60;
          RankingRows[5, 2] := 300;
          RankingRows[5, 3] := 21;
          RankingRows[5, 4] := 21;
          RankingRows[5, 5] := 0;
          RankingRows[5, 6] := 0;
          RankingRows[6, 1] := 50;
          RankingRows[6, 2] := 250;
          RankingRows[6, 3] := 20;
          RankingRows[6, 4] := 20;
          RankingRows[6, 5] := 0;
          RankingRows[6, 6] := 0;
          RankingRows[7, 1] := 40;
          RankingRows[7, 2] := 200;
          RankingRows[7, 3] := 19;
          RankingRows[7, 4] := 19;
          RankingRows[7, 5] := 0;
          RankingRows[7, 6] := 0;
          RankingRows[8, 1] := 30;
          RankingRows[8, 2] := 150;
          RankingRows[8, 3] := 18;
          RankingRows[8, 4] := 18;
          RankingRows[8, 5] := 0;
          RankingRows[8, 6] := 0;
          RankingRows[9, 1] := 20;
          RankingRows[9, 2] := 100;
          RankingRows[9, 3] := 17;
          RankingRows[9, 4] := 17;
          RankingRows[9, 5] := 0;
          RankingRows[9, 6] := 0;
          RankingRows[10, 1] := 10;
          RankingRows[10, 2] := 50;
          RankingRows[10, 3] := 16;
          RankingRows[10, 4] := 16;
          RankingRows[10, 5] := 0;
          RankingRows[10, 6] := 0;
          RankingRows[11, 1] := 0;
          RankingRows[11, 2] := 0;
          RankingRows[11, 3] := 0;
          RankingRows[11, 4] := 0;
          RankingRows[11, 5] := 0;
          RankingRows[11, 6] := 0;
          RankingRows[12, 1] := 0;
          RankingRows[12, 2] := 0;
          RankingRows[12, 3] := 0;
          RankingRows[12, 4] := 0;
          RankingRows[12, 5] := 0;
          RankingRows[12, 6] := 0;
        end;
        2:
        begin
          RankingRows[1, 1] := 100;
          RankingRows[1, 2] := 1000;
          RankingRows[1, 3] := 50;
          RankingRows[1, 4] := 50;
          RankingRows[1, 5] := 0;
          RankingRows[1, 6] := 0;
          RankingRows[2, 1] := 90;
          RankingRows[2, 2] := 900;
          RankingRows[2, 3] := 45;
          RankingRows[2, 4] := 45;
          RankingRows[2, 5] := 0;
          RankingRows[2, 6] := 0;
          RankingRows[3, 1] := 80;
          RankingRows[3, 2] := 800;
          RankingRows[3, 3] := 40;
          RankingRows[3, 4] := 40;
          RankingRows[3, 5] := 0;
          RankingRows[3, 6] := 0;
          RankingRows[4, 1] := 70;
          RankingRows[4, 2] := 700;
          RankingRows[4, 3] := 35;
          RankingRows[4, 4] := 35;
          RankingRows[4, 5] := 0;
          RankingRows[4, 6] := 0;
          RankingRows[5, 1] := 60;
          RankingRows[5, 2] := 600;
          RankingRows[5, 3] := 30;
          RankingRows[5, 4] := 30;
          RankingRows[5, 5] := 0;
          RankingRows[5, 6] := 0;
          RankingRows[6, 1] := 50;
          RankingRows[6, 2] := 500;
          RankingRows[6, 3] := 25;
          RankingRows[6, 4] := 25;
          RankingRows[6, 5] := 0;
          RankingRows[6, 6] := 0;
          RankingRows[7, 1] := 40;
          RankingRows[7, 2] := 400;
          RankingRows[7, 3] := 20;
          RankingRows[7, 4] := 20;
          RankingRows[7, 5] := 0;
          RankingRows[7, 6] := 0;
          RankingRows[8, 1] := 30;
          RankingRows[8, 2] := 300;
          RankingRows[8, 3] := 15;
          RankingRows[8, 4] := 15;
          RankingRows[8, 5] := 0;
          RankingRows[8, 6] := 0;
          RankingRows[9, 1] := 20;
          RankingRows[9, 2] := 200;
          RankingRows[9, 3] := 10;
          RankingRows[9, 4] := 10;
          RankingRows[9, 5] := 0;
          RankingRows[9, 6] := 0;
          RankingRows[10, 1] := 10;
          RankingRows[10, 2] := 100;
          RankingRows[10, 3] := 5;
          RankingRows[10, 4] := 5;
          RankingRows[10, 5] := 0;
          RankingRows[10, 6] := 0;
          RankingRows[11, 1] := 0;
          RankingRows[11, 2] := 0;
          RankingRows[11, 3] := 0;
          RankingRows[11, 4] := 0;
          RankingRows[11, 5] := 0;
          RankingRows[11, 6] := 0;
          RankingRows[12, 1] := 0;
          RankingRows[12, 2] := 0;
          RankingRows[12, 3] := 0;
          RankingRows[12, 4] := 0;
          RankingRows[12, 5] := 0;
          RankingRows[12, 6] := 0;
        end;
        3, 5:
        begin
          RankingRows[1, 1] := 100;
          RankingRows[1, 2] := 10000;
          RankingRows[1, 3] := 500;
          RankingRows[1, 4] := 500;
          RankingRows[1, 5] := 0;
          RankingRows[1, 6] := 0;
          RankingRows[2, 1] := 90;
          RankingRows[2, 2] := 9000;
          RankingRows[2, 3] := 450;
          RankingRows[2, 4] := 450;
          RankingRows[2, 5] := 0;
          RankingRows[2, 6] := 0;
          RankingRows[3, 1] := 80;
          RankingRows[3, 2] := 8000;
          RankingRows[3, 3] := 400;
          RankingRows[3, 4] := 400;
          RankingRows[3, 5] := 0;
          RankingRows[3, 6] := 0;
          RankingRows[4, 1] := 70;
          RankingRows[4, 2] := 7000;
          RankingRows[4, 3] := 350;
          RankingRows[4, 4] := 350;
          RankingRows[4, 5] := 0;
          RankingRows[4, 6] := 0;
          RankingRows[5, 1] := 60;
          RankingRows[5, 2] := 6000;
          RankingRows[5, 3] := 300;
          RankingRows[5, 4] := 300;
          RankingRows[5, 5] := 0;
          RankingRows[5, 6] := 0;
          RankingRows[6, 1] := 50;
          RankingRows[6, 2] := 5000;
          RankingRows[6, 3] := 250;
          RankingRows[6, 4] := 250;
          RankingRows[6, 5] := 0;
          RankingRows[6, 6] := 0;
          RankingRows[7, 1] := 40;
          RankingRows[7, 2] := 4000;
          RankingRows[7, 3] := 200;
          RankingRows[7, 4] := 200;
          RankingRows[7, 5] := 0;
          RankingRows[7, 6] := 0;
          RankingRows[8, 1] := 30;
          RankingRows[8, 2] := 3000;
          RankingRows[8, 3] := 150;
          RankingRows[8, 4] := 150;
          RankingRows[8, 5] := 0;
          RankingRows[8, 6] := 0;
          RankingRows[9, 1] := 20;
          RankingRows[9, 2] := 2000;
          RankingRows[9, 3] := 100;
          RankingRows[9, 4] := 100;
          RankingRows[9, 5] := 0;
          RankingRows[9, 6] := 0;
          RankingRows[10, 1] := 10;
          RankingRows[10, 2] := 1000;
          RankingRows[10, 3] := 50;
          RankingRows[10, 4] := 50;
          RankingRows[10, 5] := 0;
          RankingRows[10, 6] := 0;
          RankingRows[11, 1] := 0;
          RankingRows[11, 2] := 0;
          RankingRows[11, 3] := 0;
          RankingRows[11, 4] := 0;
          RankingRows[11, 5] := 0;
          RankingRows[11, 6] := 0;
          RankingRows[12, 1] := 0;
          RankingRows[12, 2] := 0;
          RankingRows[12, 3] := 0;
          RankingRows[12, 4] := 0;
          RankingRows[12, 5] := 0;
          RankingRows[12, 6] := 0;
        end;
        4:
        begin
          RankingRows[1, 1] := 100;
          RankingRows[1, 2] := 5000;
          RankingRows[1, 3] := 200;
          RankingRows[1, 4] := 200;
          RankingRows[1, 5] := 0;
          RankingRows[1, 6] := 0;
          RankingRows[2, 1] := 90;
          RankingRows[2, 2] := 4500;
          RankingRows[2, 3] := 190;
          RankingRows[2, 4] := 190;
          RankingRows[2, 5] := 0;
          RankingRows[2, 6] := 0;
          RankingRows[3, 1] := 80;
          RankingRows[3, 2] := 4000;
          RankingRows[3, 3] := 180;
          RankingRows[3, 4] := 180;
          RankingRows[3, 5] := 0;
          RankingRows[3, 6] := 0;
          RankingRows[4, 1] := 70;
          RankingRows[4, 2] := 3500;
          RankingRows[4, 3] := 170;
          RankingRows[4, 4] := 170;
          RankingRows[4, 5] := 0;
          RankingRows[4, 6] := 0;
          RankingRows[5, 1] := 60;
          RankingRows[5, 2] := 3000;
          RankingRows[5, 3] := 160;
          RankingRows[5, 4] := 160;
          RankingRows[5, 5] := 0;
          RankingRows[5, 6] := 0;
          RankingRows[6, 1] := 50;
          RankingRows[6, 2] := 2500;
          RankingRows[6, 3] := 150;
          RankingRows[6, 4] := 150;
          RankingRows[6, 5] := 0;
          RankingRows[6, 6] := 0;
          RankingRows[7, 1] := 40;
          RankingRows[7, 2] := 2000;
          RankingRows[7, 3] := 140;
          RankingRows[7, 4] := 140;
          RankingRows[7, 5] := 0;
          RankingRows[7, 6] := 0;
          RankingRows[8, 1] := 30;
          RankingRows[8, 2] := 1500;
          RankingRows[8, 3] := 130;
          RankingRows[8, 4] := 130;
          RankingRows[8, 5] := 0;
          RankingRows[8, 6] := 0;
          RankingRows[9, 1] := 20;
          RankingRows[9, 2] := 1000;
          RankingRows[9, 3] := 120;
          RankingRows[9, 4] := 120;
          RankingRows[9, 5] := 0;
          RankingRows[9, 6] := 0;
          RankingRows[10, 1] := 10;
          RankingRows[10, 2] := 500;
          RankingRows[10, 3] := 110;
          RankingRows[10, 4] := 110;
          RankingRows[10, 5] := 0;
          RankingRows[10, 6] := 0;
          RankingRows[11, 1] := 0;
          RankingRows[11, 2] := 0;
          RankingRows[11, 3] := 0;
          RankingRows[11, 4] := 0;
          RankingRows[11, 5] := 0;
          RankingRows[11, 6] := 0;
          RankingRows[12, 1] := 0;
          RankingRows[12, 2] := 0;
          RankingRows[12, 3] := 0;
          RankingRows[12, 4] := 0;
          RankingRows[12, 5] := 0;
          RankingRows[12, 6] := 0;
        end;
      end;
    end;
  except
    ShowMessage('Version of Ranking data is old. Use a temporary Ranking.');
    case Category of
      1:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 500;
        RankingRows[1, 3] := 25;
        RankingRows[1, 4] := 25;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 450;
        RankingRows[2, 3] := 24;
        RankingRows[2, 4] := 24;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 400;
        RankingRows[3, 3] := 23;
        RankingRows[3, 4] := 23;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 350;
        RankingRows[4, 3] := 22;
        RankingRows[4, 4] := 22;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 300;
        RankingRows[5, 3] := 21;
        RankingRows[5, 4] := 21;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 250;
        RankingRows[6, 3] := 20;
        RankingRows[6, 4] := 20;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 200;
        RankingRows[7, 3] := 19;
        RankingRows[7, 4] := 19;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 150;
        RankingRows[8, 3] := 18;
        RankingRows[8, 4] := 18;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 100;
        RankingRows[9, 3] := 17;
        RankingRows[9, 4] := 17;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 50;
        RankingRows[10, 3] := 16;
        RankingRows[10, 4] := 16;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      2:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 1000;
        RankingRows[1, 3] := 50;
        RankingRows[1, 4] := 50;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 900;
        RankingRows[2, 3] := 45;
        RankingRows[2, 4] := 45;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 800;
        RankingRows[3, 3] := 40;
        RankingRows[3, 4] := 40;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 700;
        RankingRows[4, 3] := 35;
        RankingRows[4, 4] := 35;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 600;
        RankingRows[5, 3] := 30;
        RankingRows[5, 4] := 30;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 500;
        RankingRows[6, 3] := 25;
        RankingRows[6, 4] := 25;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 400;
        RankingRows[7, 3] := 20;
        RankingRows[7, 4] := 20;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 300;
        RankingRows[8, 3] := 15;
        RankingRows[8, 4] := 15;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 200;
        RankingRows[9, 3] := 10;
        RankingRows[9, 4] := 10;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 100;
        RankingRows[10, 3] := 5;
        RankingRows[10, 4] := 5;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      3, 5:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 10000;
        RankingRows[1, 3] := 500;
        RankingRows[1, 4] := 500;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 9000;
        RankingRows[2, 3] := 450;
        RankingRows[2, 4] := 450;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 8000;
        RankingRows[3, 3] := 400;
        RankingRows[3, 4] := 400;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 7000;
        RankingRows[4, 3] := 350;
        RankingRows[4, 4] := 350;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 6000;
        RankingRows[5, 3] := 300;
        RankingRows[5, 4] := 300;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 5000;
        RankingRows[6, 3] := 250;
        RankingRows[6, 4] := 250;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 4000;
        RankingRows[7, 3] := 200;
        RankingRows[7, 4] := 200;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 3000;
        RankingRows[8, 3] := 150;
        RankingRows[8, 4] := 150;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 2000;
        RankingRows[9, 3] := 100;
        RankingRows[9, 4] := 100;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 1000;
        RankingRows[10, 3] := 50;
        RankingRows[10, 4] := 50;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      4:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 5000;
        RankingRows[1, 3] := 200;
        RankingRows[1, 4] := 200;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 4500;
        RankingRows[2, 3] := 190;
        RankingRows[2, 4] := 190;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 4000;
        RankingRows[3, 3] := 180;
        RankingRows[3, 4] := 180;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 3500;
        RankingRows[4, 3] := 170;
        RankingRows[4, 4] := 170;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 3000;
        RankingRows[5, 3] := 160;
        RankingRows[5, 4] := 160;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 2500;
        RankingRows[6, 3] := 150;
        RankingRows[6, 4] := 150;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 2000;
        RankingRows[7, 3] := 140;
        RankingRows[7, 4] := 140;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 1500;
        RankingRows[8, 3] := 130;
        RankingRows[8, 4] := 130;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 1000;
        RankingRows[9, 3] := 120;
        RankingRows[9, 4] := 120;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 500;
        RankingRows[10, 3] := 110;
        RankingRows[10, 4] := 110;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
    end;
  end;
  case Category of
    1: RankingPath := MainForm.Memo12.Lines[0] + '\option11.dat';
    2: RankingPath := MainForm.Memo12.Lines[0] + '\option21.dat';
    3: RankingPath := MainForm.Memo12.Lines[0] + '\option31.dat';
    4: RankingPath := MainForm.Memo12.Lines[0] + '\option41.dat';
    5: RankingPath := MainForm.Memo12.Lines[0] + '\option51.dat';
  end;
  Memo62.Lines.LoadFromFile(RankingPath);
  Memo21.Lines.Clear;
  Memo22.Lines.Clear;
  Memo23.Lines.Clear;
  Memo24.Lines.Clear;
  Memo25.Lines.Clear;
  Memo26.Lines.Clear;
  Memo27.Lines.Clear;
  Memo28.Lines.Clear;
  Memo29.Lines.Clear;
  Memo30.Lines.Clear;
  Memo21.Lines[0] := Memo62.Lines[0];
  Memo22.Lines[0] := Memo62.Lines[1];
  Memo23.Lines[0] := Memo62.Lines[2];
  Memo24.Lines[0] := Memo62.Lines[3];
  Memo25.Lines[0] := Memo62.Lines[4];
  Memo26.Lines[0] := Memo62.Lines[5];
  Memo27.Lines[0] := Memo62.Lines[6];
  Memo28.Lines[0] := Memo62.Lines[7];
  Memo29.Lines[0] := Memo62.Lines[8];
  Memo30.Lines[0] := Memo62.Lines[9];
  case Category of
    1: BitBtn1.SetFocus;
    2: BitBtn2.SetFocus;
    3: BitBtn3.SetFocus;
    4: BitBtn4.SetFocus;
    5: BitBtn5.SetFocus;
  end;
end;

procedure TForm2.scoresave; { $00439CE0 }
var
  Column, Row: Longint;
begin
  { Rows carry two checksums; the final two rows check each column. }
  for Row := 1 to 10 do
  begin
    RankingRows[Row, 5] := 0;
    for Column := 1 to 4 do
      RankingRows[Row, 5] := RankingRows[Row, 5] + RankingRows[Row, Column];
    RankingRows[Row, 6] := 0;
    for Column := 1 to 5 do
      case Column of
        1, 3, 5: RankingRows[Row, 6] := RankingRows[Row, 6] + RankingRows[Row, Column];
        2, 4: RankingRows[Row, 6] := RankingRows[Row, 6] - RankingRows[Row, Column];
      end;
  end;
  for Row := 1 to 6 do
  begin
    RankingRows[11, Row] := 0;
    for Column := 1 to 10 do
      RankingRows[11, Row] := RankingRows[11, Row] + RankingRows[Column, Row];
    RankingRows[12, Row] := 0;
    for Column := 1 to 11 do
      case Column of
        1, 3, 5, 7, 9, 11: RankingRows[12, Row] := RankingRows[12, Row] + RankingRows[Column, Row];
        2, 4, 6, 8, 10: RankingRows[12, Row] := RankingRows[12, Row] - RankingRows[Column, Row];
      end;
  end;
  RankingRows[12, 6] := RankingHero.Word628 * 100 + (-1) * RankingHero.Word348;
  case RankingHero.Word348 of
    1: RankingPath := MainForm.Memo12.Lines[0] + '\option1.dat';
    2: RankingPath := MainForm.Memo12.Lines[0] + '\option2.dat';
    3: RankingPath := MainForm.Memo12.Lines[0] + '\option3.dat';
    4: RankingPath := MainForm.Memo12.Lines[0] + '\option4.dat';
    5: RankingPath := MainForm.Memo12.Lines[0] + '\option5.dat';
  end;
  AssignFile(RankingFile, RankingPath);
  Rewrite(RankingFile, 1);
  BlockWrite(RankingFile, RankingRows, SizeOf(RankingRows));
  CloseFile(RankingFile);
  case RankingHero.Word348 of
    1: RankingPath := MainForm.Memo12.Lines[0] + '\option11.dat';
    2: RankingPath := MainForm.Memo12.Lines[0] + '\option21.dat';
    3: RankingPath := MainForm.Memo12.Lines[0] + '\option31.dat';
    4: RankingPath := MainForm.Memo12.Lines[0] + '\option41.dat';
    5: RankingPath := MainForm.Memo12.Lines[0] + '\option51.dat';
  end;
  Memo62.Lines.Clear;
  Memo62.Lines.AddStrings(Memo21.Lines);
  Memo62.Lines.AddStrings(Memo22.Lines);
  Memo62.Lines.AddStrings(Memo23.Lines);
  Memo62.Lines.AddStrings(Memo24.Lines);
  Memo62.Lines.AddStrings(Memo25.Lines);
  Memo62.Lines.AddStrings(Memo26.Lines);
  Memo62.Lines.AddStrings(Memo27.Lines);
  Memo62.Lines.AddStrings(Memo28.Lines);
  Memo62.Lines.AddStrings(Memo29.Lines);
  Memo62.Lines.AddStrings(Memo30.Lines);
  Memo62.Lines.SaveToFile(RankingPath);
  if RankingHero.Word340 <> 0 then
    RankingHero.Word340 := 0;
  if RankingHero.Word344 <> 0 then
    RankingHero.Word344 := 0;
  if RankingHero.Word348 <> 0 then
    RankingHero.Word348 := 0;
  RankingPath := MainForm.Memo12.Lines[0] + '\save0.dat';
  AssignFile(RankingFile, RankingPath);
  Rewrite(RankingFile, 1);
  BlockWrite(RankingFile, RankingMaps, SizeOf(RankingMaps));
  BlockWrite(RankingFile, RankingHero, SizeOf(RankingHero));
  CloseFile(RankingFile);
end;

procedure TForm2.hyouji(Category: Byte);
var
  Row, Column: Byte;
begin
  case Category of
    1: scoreload(1);
    2: scoreload(2);
    3: scoreload(3);
    4: scoreload(4);
    5: scoreload(5);
  end;
  if RankingHero.Word344 > 0 then
  begin
    RankingPath := '';
    if InputQuery('Input your name', 'Please input within 18 words', RankingPath) = True then
    begin
      { Shift names in the same nested order as the original ranking form. }
      if (RankingHero.Word344 < 10) and (RankingPath <> '') then
      begin
        Memo30.Lines.Clear;
        Memo30.Lines[0] := Memo29.Lines[0];
        if RankingHero.Word344 < 9 then
        begin
          Memo29.Lines.Clear;
          Memo29.Lines[0] := Memo28.Lines[0];
          if RankingHero.Word344 < 8 then
          begin
            Memo28.Lines.Clear;
            Memo28.Lines[0] := Memo27.Lines[0];
            if RankingHero.Word344 < 7 then
            begin
              Memo27.Lines.Clear;
              Memo27.Lines[0] := Memo26.Lines[0];
              if RankingHero.Word344 < 6 then
              begin
                Memo26.Lines.Clear;
                Memo26.Lines[0] := Memo25.Lines[0];
                if RankingHero.Word344 < 5 then
                begin
                  Memo25.Lines.Clear;
                  Memo25.Lines[0] := Memo24.Lines[0];
                  if RankingHero.Word344 < 4 then
                  begin
                    Memo24.Lines.Clear;
                    Memo24.Lines[0] := Memo23.Lines[0];
                    if RankingHero.Word344 < 3 then
                    begin
                      Memo23.Lines.Clear;
                      Memo23.Lines[0] := Memo22.Lines[0];
                      if RankingHero.Word344 < 2 then
                      begin
                        Memo22.Lines.Clear;
                        Memo22.Lines[0] := Memo21.Lines[0];
                      end;
                    end;
                  end;
                end;
              end;
            end;
          end;
        end;
      end
      else if RankingPath = '' then
        RankingHero.Word344 := 0;
      case RankingHero.Word344 of
        1: Memo21.Lines[0] := RankingPath;
        2: Memo22.Lines[0] := RankingPath;
        3: Memo23.Lines[0] := RankingPath;
        4: Memo24.Lines[0] := RankingPath;
        5: Memo25.Lines[0] := RankingPath;
        6: Memo26.Lines[0] := RankingPath;
        7: Memo27.Lines[0] := RankingPath;
        8: Memo28.Lines[0] := RankingPath;
        9: Memo29.Lines[0] := RankingPath;
        10: Memo30.Lines[0] := RankingPath;
      end;
      if RankingHero.Word344 > 0 then
      begin
        if RankingHero.Word344 < 10 then
          for Row := 9 downto RankingHero.Word344 do
            for Column := 1 to 4 do
              RankingRows[Row + 1, Column] := RankingRows[Row, Column];
        RankingRows[RankingHero.Word344, 1] := RankingHero.Word340;
        RankingRows[RankingHero.Word344, 2] := RankingHero.hp;
        RankingRows[RankingHero.Word344, 3] := RankingHero.attack;
        RankingRows[RankingHero.Word344, 4] := RankingHero.defense;
      end;
    end;
  end;
  Memo11.Text := IntToStr(RankingRows[1, 1]);
  Memo12.Text := IntToStr(RankingRows[2, 1]);
  Memo13.Text := IntToStr(RankingRows[3, 1]);
  Memo14.Text := IntToStr(RankingRows[4, 1]);
  Memo15.Text := IntToStr(RankingRows[5, 1]);
  Memo16.Text := IntToStr(RankingRows[6, 1]);
  Memo17.Text := IntToStr(RankingRows[7, 1]);
  Memo18.Text := IntToStr(RankingRows[8, 1]);
  Memo19.Text := IntToStr(RankingRows[9, 1]);
  Memo20.Text := IntToStr(RankingRows[10, 1]);
  Memo31.Text := IntToStr(RankingRows[1, 2]);
  Memo32.Text := IntToStr(RankingRows[2, 2]);
  Memo33.Text := IntToStr(RankingRows[3, 2]);
  Memo34.Text := IntToStr(RankingRows[4, 2]);
  Memo35.Text := IntToStr(RankingRows[5, 2]);
  Memo36.Text := IntToStr(RankingRows[6, 2]);
  Memo37.Text := IntToStr(RankingRows[7, 2]);
  Memo38.Text := IntToStr(RankingRows[8, 2]);
  Memo39.Text := IntToStr(RankingRows[9, 2]);
  Memo40.Text := IntToStr(RankingRows[10, 2]);
  Memo41.Text := IntToStr(RankingRows[1, 3]);
  Memo42.Text := IntToStr(RankingRows[2, 3]);
  Memo43.Text := IntToStr(RankingRows[3, 3]);
  Memo44.Text := IntToStr(RankingRows[4, 3]);
  Memo45.Text := IntToStr(RankingRows[5, 3]);
  Memo46.Text := IntToStr(RankingRows[6, 3]);
  Memo47.Text := IntToStr(RankingRows[7, 3]);
  Memo48.Text := IntToStr(RankingRows[8, 3]);
  Memo49.Text := IntToStr(RankingRows[9, 3]);
  Memo50.Text := IntToStr(RankingRows[10, 3]);
  Memo51.Text := IntToStr(RankingRows[1, 4]);
  Memo52.Text := IntToStr(RankingRows[2, 4]);
  Memo53.Text := IntToStr(RankingRows[3, 4]);
  Memo54.Text := IntToStr(RankingRows[4, 4]);
  Memo55.Text := IntToStr(RankingRows[5, 4]);
  Memo56.Text := IntToStr(RankingRows[6, 4]);
  Memo57.Text := IntToStr(RankingRows[7, 4]);
  Memo58.Text := IntToStr(RankingRows[8, 4]);
  Memo59.Text := IntToStr(RankingRows[9, 4]);
  Memo60.Text := IntToStr(RankingRows[10, 4]);
  if RankingHero.Word344 > 0 then
    scoresave;
end;

procedure TForm2.optionload; { $004375D8 }
begin
  RankingPath := MainForm.Memo12.Lines[0] + '\option.dat';
  AssignFile(RankingFile, RankingPath);
  Reset(RankingFile, 1);
  BlockRead(RankingFile, RankingOptions, 10);
  CloseFile(RankingFile);
  Memo1.Font.Size := 10;
  Memo61.Font.Size := 12;
  if MainForm.Large1.Checked = True then
  begin
    Memo1.Font.Size := 12;
    Memo61.Font.Size := 14;
  end;
  if MainForm.Small1.Checked = True then
  begin
    Memo1.Font.Size := 9;
    Memo61.Font.Size := 11;
  end;
  if MainForm.tiny1.Checked = True then
  begin
    Memo1.Font.Size := 8;
    Memo61.Font.Size := 10;
  end;
  Memo2.Font.Size := Memo1.Font.Size;
  Memo3.Font.Size := Memo1.Font.Size;
  Memo4.Font.Size := Memo1.Font.Size;
  Memo5.Font.Size := Memo1.Font.Size;
  Memo6.Font.Size := Memo1.Font.Size;
  Memo7.Font.Size := Memo1.Font.Size;
  Memo8.Font.Size := Memo1.Font.Size;
  Memo9.Font.Size := Memo1.Font.Size;
  Memo10.Font.Size := Memo1.Font.Size;
  Memo11.Font.Size := Memo1.Font.Size;
  Memo12.Font.Size := Memo1.Font.Size;
  Memo13.Font.Size := Memo1.Font.Size;
  Memo14.Font.Size := Memo1.Font.Size;
  Memo15.Font.Size := Memo1.Font.Size;
  Memo16.Font.Size := Memo1.Font.Size;
  Memo17.Font.Size := Memo1.Font.Size;
  Memo18.Font.Size := Memo1.Font.Size;
  Memo19.Font.Size := Memo1.Font.Size;
  Memo20.Font.Size := Memo1.Font.Size;
  Memo21.Font.Size := Memo1.Font.Size;
  Memo22.Font.Size := Memo1.Font.Size;
  Memo23.Font.Size := Memo1.Font.Size;
  Memo24.Font.Size := Memo1.Font.Size;
  Memo25.Font.Size := Memo1.Font.Size;
  Memo26.Font.Size := Memo1.Font.Size;
  Memo27.Font.Size := Memo1.Font.Size;
  Memo28.Font.Size := Memo1.Font.Size;
  Memo29.Font.Size := Memo1.Font.Size;
  Memo30.Font.Size := Memo1.Font.Size;
  Memo31.Font.Size := Memo1.Font.Size;
  Memo32.Font.Size := Memo1.Font.Size;
  Memo33.Font.Size := Memo1.Font.Size;
  Memo34.Font.Size := Memo1.Font.Size;
  Memo35.Font.Size := Memo1.Font.Size;
  Memo36.Font.Size := Memo1.Font.Size;
  Memo37.Font.Size := Memo1.Font.Size;
  Memo38.Font.Size := Memo1.Font.Size;
  Memo39.Font.Size := Memo1.Font.Size;
  Memo40.Font.Size := Memo1.Font.Size;
  Memo41.Font.Size := Memo1.Font.Size;
  Memo42.Font.Size := Memo1.Font.Size;
  Memo43.Font.Size := Memo1.Font.Size;
  Memo44.Font.Size := Memo1.Font.Size;
  Memo45.Font.Size := Memo1.Font.Size;
  Memo46.Font.Size := Memo1.Font.Size;
  Memo47.Font.Size := Memo1.Font.Size;
  Memo48.Font.Size := Memo1.Font.Size;
  Memo49.Font.Size := Memo1.Font.Size;
  Memo50.Font.Size := Memo1.Font.Size;
  Memo51.Font.Size := Memo1.Font.Size;
  Memo52.Font.Size := Memo1.Font.Size;
  Memo53.Font.Size := Memo1.Font.Size;
  Memo54.Font.Size := Memo1.Font.Size;
  Memo55.Font.Size := Memo1.Font.Size;
  Memo56.Font.Size := Memo1.Font.Size;
  Memo57.Font.Size := Memo1.Font.Size;
  Memo58.Font.Size := Memo1.Font.Size;
  Memo59.Font.Size := Memo1.Font.Size;
  Memo60.Font.Size := Memo1.Font.Size;
  Button1.Font.Size := Memo1.Font.Size;
  Button6.Font.Size := Memo1.Font.Size;
  BitBtn1.Font.Size := Memo1.Font.Size;
  BitBtn2.Font.Size := Memo1.Font.Size;
  BitBtn3.Font.Size := Memo1.Font.Size;
  BitBtn4.Font.Size := Memo1.Font.Size;
  BitBtn5.Font.Size := Memo1.Font.Size;
end;

procedure TForm2.formactivate(Sender: TObject); { $00434BC4 }
begin
  { Lay out the ranking columns and category buttons. }
  RankingForm.Width := $1E0;
  RankingForm.Height := $1BC;
  RankingCategory := 0;
  Memo61.Top := 8;
  Memo61.Left := $10;
  Memo61.Height := $1C;
  Memo61.Width := RankingForm.ClientWidth - $20;
  BitBtn3.Height := $38;
  BitBtn3.Width := $38;
  BitBtn3.Top := Memo61.Top + Memo61.Height + 8;
  BitBtn3.Left := RankingForm.ClientWidth div 2 - BitBtn3.Width div 2;
  BitBtn2.Height := BitBtn3.Height;
  BitBtn2.Width := BitBtn3.Width;
  BitBtn1.Height := BitBtn3.Height;
  BitBtn1.Width := BitBtn3.Width;
  BitBtn4.Height := BitBtn3.Height;
  BitBtn4.Width := BitBtn3.Width;
  BitBtn5.Height := BitBtn3.Height;
  BitBtn5.Width := BitBtn3.Width;
  BitBtn2.Top := BitBtn3.Top;
  BitBtn2.Left := (BitBtn3.Left - BitBtn2.Width) - $18;
  BitBtn4.Top := BitBtn3.Top;
  BitBtn4.Left := BitBtn3.Left + BitBtn3.Width + $18;
  BitBtn1.Top := BitBtn3.Top;
  BitBtn1.Left := (BitBtn2.Left - BitBtn1.Width) - $18;
  BitBtn5.Top := BitBtn3.Top;
  BitBtn5.Left := BitBtn4.Left + BitBtn4.Width + $18;
  Label1.Top := BitBtn3.Top + BitBtn3.Height + 8;
  Label1.Left := Memo61.Left;
  Label1.Height := $10;
  Label1.Width := $28;
  Label2.Top := Label1.Top;
  Label2.Left := Label1.Left + Label1.Width + 8;
  Label2.Height := Label1.Height;
  Label2.Width := $37;
  Label3.Top := Label1.Top;
  Label3.Left := Label2.Left + Label2.Width + 8;
  Label3.Height := Label1.Height;
  Label3.Width := $98;
  Label4.Top := Label1.Top;
  Label4.Left := Label3.Left + Label3.Width;
  Label4.Height := Label1.Height;
  Label4.Width := $46;
  Label5.Top := Label1.Top;
  Label5.Left := Label4.Left + Label4.Width;
  Label5.Height := Label1.Height;
  Label5.Width := $37;
  Label6.Top := Label1.Top;
  Label6.Left := Label5.Left + Label5.Width;
  Label6.Height := Label1.Height;
  Label6.Width := Label5.Width;
  Memo1.Top := Label1.Top + Label1.Height + 2;
  Memo1.Left := Label1.Left;
  Memo1.Height := $19;
  Memo1.Width := Label1.Width;
  Memo2.Top := Memo1.Top + Memo1.Height;
  Memo2.Left := Memo1.Left;
  Memo2.Height := Memo1.Height;
  Memo2.Width := Memo1.Width;
  Memo3.Top := Memo2.Top + Memo2.Height;
  Memo3.Left := Memo1.Left;
  Memo3.Height := Memo1.Height;
  Memo3.Width := Memo1.Width;
  Memo4.Top := Memo3.Top + Memo3.Height;
  Memo4.Left := Memo1.Left;
  Memo4.Height := Memo1.Height;
  Memo4.Width := Memo1.Width;
  Memo5.Top := Memo4.Top + Memo4.Height;
  Memo5.Left := Memo1.Left;
  Memo5.Height := Memo1.Height;
  Memo5.Width := Memo1.Width;
  Memo6.Top := Memo5.Top + Memo5.Height;
  Memo6.Left := Memo1.Left;
  Memo6.Height := Memo1.Height;
  Memo6.Width := Memo1.Width;
  Memo7.Top := Memo6.Top + Memo6.Height;
  Memo7.Left := Memo1.Left;
  Memo7.Height := Memo1.Height;
  Memo7.Width := Memo1.Width;
  Memo8.Top := Memo7.Top + Memo7.Height;
  Memo8.Left := Memo1.Left;
  Memo8.Height := Memo1.Height;
  Memo8.Width := Memo1.Width;
  Memo9.Top := Memo8.Top + Memo8.Height;
  Memo9.Left := Memo1.Left;
  Memo9.Height := Memo1.Height;
  Memo9.Width := Memo1.Width;
  Memo10.Top := Memo9.Top + Memo9.Height;
  Memo10.Left := Memo1.Left;
  Memo10.Height := Memo1.Height;
  Memo10.Width := Memo1.Width;
  Memo11.Top := Memo1.Top;
  Memo11.Left := Label2.Left;
  Memo11.Height := Memo1.Height;
  Memo11.Width := Label2.Width;
  Memo12.Top := Memo2.Top;
  Memo12.Left := Memo11.Left;
  Memo12.Height := Memo2.Height;
  Memo12.Width := Memo11.Width;
  Memo13.Top := Memo3.Top;
  Memo13.Left := Memo11.Left;
  Memo13.Height := Memo3.Height;
  Memo13.Width := Memo11.Width;
  Memo14.Top := Memo4.Top;
  Memo14.Left := Memo11.Left;
  Memo14.Height := Memo4.Height;
  Memo14.Width := Memo11.Width;
  Memo15.Top := Memo5.Top;
  Memo15.Left := Memo11.Left;
  Memo15.Height := Memo5.Height;
  Memo15.Width := Memo11.Width;
  Memo16.Top := Memo6.Top;
  Memo16.Left := Memo11.Left;
  Memo16.Height := Memo6.Height;
  Memo16.Width := Memo11.Width;
  Memo17.Top := Memo7.Top;
  Memo17.Left := Memo11.Left;
  Memo17.Height := Memo7.Height;
  Memo17.Width := Memo11.Width;
  Memo18.Top := Memo8.Top;
  Memo18.Left := Memo11.Left;
  Memo18.Height := Memo8.Height;
  Memo18.Width := Memo11.Width;
  Memo19.Top := Memo9.Top;
  Memo19.Left := Memo11.Left;
  Memo19.Height := Memo9.Height;
  Memo19.Width := Memo11.Width;
  Memo20.Top := Memo10.Top;
  Memo20.Left := Memo11.Left;
  Memo20.Height := Memo10.Height;
  Memo20.Width := Memo11.Width;
  Memo21.Top := Memo1.Top;
  Memo21.Left := Label3.Left;
  Memo21.Height := Memo1.Height;
  Memo21.Width := Label3.Width;
  Memo22.Top := Memo2.Top;
  Memo22.Left := Memo21.Left;
  Memo22.Height := Memo2.Height;
  Memo22.Width := Memo21.Width;
  Memo23.Top := Memo3.Top;
  Memo23.Left := Memo21.Left;
  Memo23.Height := Memo3.Height;
  Memo23.Width := Memo21.Width;
  Memo24.Top := Memo4.Top;
  Memo24.Left := Memo21.Left;
  Memo24.Height := Memo4.Height;
  Memo24.Width := Memo21.Width;
  Memo25.Top := Memo5.Top;
  Memo25.Left := Memo21.Left;
  Memo25.Height := Memo5.Height;
  Memo25.Width := Memo21.Width;
  Memo26.Top := Memo6.Top;
  Memo26.Left := Memo21.Left;
  Memo26.Height := Memo6.Height;
  Memo26.Width := Memo21.Width;
  Memo27.Top := Memo7.Top;
  Memo27.Left := Memo21.Left;
  Memo27.Height := Memo7.Height;
  Memo27.Width := Memo21.Width;
  Memo28.Top := Memo8.Top;
  Memo28.Left := Memo21.Left;
  Memo28.Height := Memo8.Height;
  Memo28.Width := Memo21.Width;
  Memo29.Top := Memo9.Top;
  Memo29.Left := Memo21.Left;
  Memo29.Height := Memo9.Height;
  Memo29.Width := Memo21.Width;
  Memo30.Top := Memo10.Top;
  Memo30.Left := Memo21.Left;
  Memo30.Height := Memo10.Height;
  Memo30.Width := Memo21.Width;
  Memo31.Top := Memo1.Top;
  Memo31.Left := Label4.Left;
  Memo31.Height := Memo1.Height;
  Memo31.Width := Label4.Width;
  Memo32.Top := Memo2.Top;
  Memo32.Left := Memo31.Left;
  Memo32.Height := Memo1.Height;
  Memo32.Width := Memo31.Width;
  Memo33.Top := Memo3.Top;
  Memo33.Left := Memo31.Left;
  Memo33.Height := Memo1.Height;
  Memo33.Width := Memo31.Width;
  Memo34.Top := Memo4.Top;
  Memo34.Left := Memo31.Left;
  Memo34.Height := Memo1.Height;
  Memo34.Width := Memo31.Width;
  Memo35.Top := Memo5.Top;
  Memo35.Left := Memo31.Left;
  Memo35.Height := Memo1.Height;
  Memo35.Width := Memo31.Width;
  Memo36.Top := Memo6.Top;
  Memo36.Left := Memo31.Left;
  Memo36.Height := Memo1.Height;
  Memo36.Width := Memo31.Width;
  Memo37.Top := Memo7.Top;
  Memo37.Left := Memo31.Left;
  Memo37.Height := Memo1.Height;
  Memo37.Width := Memo31.Width;
  Memo38.Top := Memo8.Top;
  Memo38.Left := Memo31.Left;
  Memo38.Height := Memo1.Height;
  Memo38.Width := Memo31.Width;
  Memo39.Top := Memo9.Top;
  Memo39.Left := Memo31.Left;
  Memo39.Height := Memo1.Height;
  Memo39.Width := Memo31.Width;
  Memo40.Top := Memo10.Top;
  Memo40.Left := Memo31.Left;
  Memo40.Height := Memo1.Height;
  Memo40.Width := Memo31.Width;
  Memo41.Top := Memo1.Top;
  Memo41.Left := Label5.Left;
  Memo41.Height := Memo1.Height;
  Memo41.Width := Label5.Width;
  Memo42.Top := Memo2.Top;
  Memo42.Left := Memo41.Left;
  Memo42.Height := Memo1.Height;
  Memo42.Width := Memo41.Width;
  Memo43.Top := Memo3.Top;
  Memo43.Left := Memo41.Left;
  Memo43.Height := Memo1.Height;
  Memo43.Width := Memo41.Width;
  Memo44.Top := Memo4.Top;
  Memo44.Left := Memo41.Left;
  Memo44.Height := Memo1.Height;
  Memo44.Width := Memo41.Width;
  Memo45.Top := Memo5.Top;
  Memo45.Left := Memo41.Left;
  Memo45.Height := Memo1.Height;
  Memo45.Width := Memo41.Width;
  Memo46.Top := Memo6.Top;
  Memo46.Left := Memo41.Left;
  Memo46.Height := Memo1.Height;
  Memo46.Width := Memo41.Width;
  Memo47.Top := Memo7.Top;
  Memo47.Left := Memo41.Left;
  Memo47.Height := Memo1.Height;
  Memo47.Width := Memo41.Width;
  Memo48.Top := Memo8.Top;
  Memo48.Left := Memo41.Left;
  Memo48.Height := Memo1.Height;
  Memo48.Width := Memo41.Width;
  Memo49.Top := Memo9.Top;
  Memo49.Left := Memo41.Left;
  Memo49.Height := Memo1.Height;
  Memo49.Width := Memo41.Width;
  Memo50.Top := Memo10.Top;
  Memo50.Left := Memo41.Left;
  Memo50.Height := Memo1.Height;
  Memo50.Width := Memo41.Width;
  Memo51.Top := Memo1.Top;
  Memo51.Left := Label6.Left;
  Memo51.Height := Memo1.Height;
  Memo51.Width := Label6.Width;
  Memo52.Top := Memo2.Top;
  Memo52.Left := Memo51.Left;
  Memo52.Height := Memo1.Height;
  Memo52.Width := Memo41.Width;
  Memo53.Top := Memo3.Top;
  Memo53.Left := Memo51.Left;
  Memo53.Height := Memo1.Height;
  Memo53.Width := Memo41.Width;
  Memo54.Top := Memo4.Top;
  Memo54.Left := Memo51.Left;
  Memo54.Height := Memo1.Height;
  Memo54.Width := Memo41.Width;
  Memo55.Top := Memo5.Top;
  Memo55.Left := Memo51.Left;
  Memo55.Height := Memo1.Height;
  Memo55.Width := Memo41.Width;
  Memo56.Top := Memo6.Top;
  Memo56.Left := Memo51.Left;
  Memo56.Height := Memo1.Height;
  Memo56.Width := Memo41.Width;
  Memo57.Top := Memo7.Top;
  Memo57.Left := Memo51.Left;
  Memo57.Height := Memo1.Height;
  Memo57.Width := Memo41.Width;
  Memo58.Top := Memo8.Top;
  Memo58.Left := Memo51.Left;
  Memo58.Height := Memo1.Height;
  Memo58.Width := Memo41.Width;
  Memo59.Top := Memo9.Top;
  Memo59.Left := Memo51.Left;
  Memo59.Height := Memo1.Height;
  Memo59.Width := Memo41.Width;
  Memo60.Top := Memo10.Top;
  Memo60.Left := Memo51.Left;
  Memo60.Height := Memo1.Height;
  Memo60.Width := Memo41.Width;
  Button6.Height := Memo1.Height;
  Button6.Width := $60;
  Button1.Height := Button6.Height;
  Button1.Width := Button6.Width;
  Button6.Top := Memo10.Top + Memo10.Height + 8;
  Button6.Left := RankingForm.Width div 2 - Button6.Width - $10;
  Button1.Top := Button6.Top;
  Button1.Left := Button6.Left + Button6.Width + $20;
  Memo1.Text := '1';
  Memo2.Text := '2';
  Memo3.Text := '3';
  Memo4.Text := '4';
  Memo5.Text := '5';
  Memo6.Text := '6';
  Memo7.Text := '7';
  Memo8.Text := '8';
  Memo9.Text := '9';
  Memo10.Text := '10';
  Memo11.Text := '';
  Memo12.Text := '';
  Memo13.Text := '';
  Memo14.Text := '';
  Memo15.Text := '';
  Memo16.Text := '';
  Memo17.Text := '';
  Memo18.Text := '';
  Memo19.Text := '';
  Memo20.Text := '';
  Memo21.Text := '';
  Memo22.Text := '';
  Memo23.Text := '';
  Memo24.Text := '';
  Memo25.Text := '';
  Memo26.Text := '';
  Memo27.Text := '';
  Memo28.Text := '';
  Memo29.Text := '';
  Memo30.Text := '';
  Memo31.Text := '';
  Memo32.Text := '';
  Memo33.Text := '';
  Memo34.Text := '';
  Memo35.Text := '';
  Memo36.Text := '';
  Memo37.Text := '';
  Memo38.Text := '';
  Memo39.Text := '';
  Memo40.Text := '';
  Memo41.Text := '';
  Memo42.Text := '';
  Memo43.Text := '';
  Memo44.Text := '';
  Memo45.Text := '';
  Memo46.Text := '';
  Memo47.Text := '';
  Memo48.Text := '';
  Memo49.Text := '';
  Memo50.Text := '';
  Memo51.Text := '';
  Memo52.Text := '';
  Memo53.Text := '';
  Memo54.Text := '';
  Memo55.Text := '';
  Memo56.Text := '';
  Memo57.Text := '';
  Memo58.Text := '';
  Memo59.Text := '';
  Memo60.Text := '';
  Memo61.Text := 'RANKING of Top 10';
  optionload;
  loadwork;
  Label1.Visible := True;
  Label2.Visible := True;
  Label3.Visible := True;
  Label4.Visible := True;
  Label5.Visible := True;
  Label6.Visible := True;
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
  Memo12.Visible := True;
  Memo13.Visible := True;
  Memo14.Visible := True;
  Memo15.Visible := True;
  Memo16.Visible := True;
  Memo17.Visible := True;
  Memo18.Visible := True;
  Memo19.Visible := True;
  Memo20.Visible := True;
  Memo21.Visible := True;
  Memo22.Visible := True;
  Memo23.Visible := True;
  Memo24.Visible := True;
  Memo25.Visible := True;
  Memo26.Visible := True;
  Memo27.Visible := True;
  Memo28.Visible := True;
  Memo29.Visible := True;
  Memo30.Visible := True;
  Memo31.Visible := True;
  Memo32.Visible := True;
  Memo33.Visible := True;
  Memo34.Visible := True;
  Memo35.Visible := True;
  Memo36.Visible := True;
  Memo37.Visible := True;
  Memo38.Visible := True;
  Memo39.Visible := True;
  Memo40.Visible := True;
  Memo41.Visible := True;
  Memo42.Visible := True;
  Memo43.Visible := True;
  Memo44.Visible := True;
  Memo45.Visible := True;
  Memo46.Visible := True;
  Memo47.Visible := True;
  Memo48.Visible := True;
  Memo49.Visible := True;
  Memo50.Visible := True;
  Memo51.Visible := True;
  Memo52.Visible := True;
  Memo53.Visible := True;
  Memo54.Visible := True;
  Memo55.Visible := True;
  Memo56.Visible := True;
  Memo57.Visible := True;
  Memo58.Visible := True;
  Memo59.Visible := True;
  Memo60.Visible := True;
  Memo61.Visible := True;
  Button1.Visible := True;
  Button1.Enabled := False;
  Button6.Visible := True;
  BitBtn1.Visible := True;
  BitBtn2.Visible := True;
  BitBtn3.Visible := True;
  BitBtn4.Visible := True;
  Button6.SetFocus;
  case RankingHero.Word348 of
    1:
    begin
      RankingCategory := 1;
      hyouji(1);
      Button1.Enabled := True;
    end;
    2:
    begin
      RankingCategory := 2;
      hyouji(2);
      Button1.Enabled := True;
    end;
    3:
    begin
      RankingCategory := 3;
      hyouji(3);
      Button1.Enabled := True;
    end;
    4:
    begin
      RankingCategory := 4;
      hyouji(4);
      Button1.Enabled := True;
    end;
    5:
    begin
      RankingCategory := 5;
      hyouji(5);
      Button1.Enabled := True;
    end;
  end;
end;

procedure TForm2.Button6Click(Sender: TObject); { $00436BF0 }
begin
  MainForm.Timer2.Enabled := True;
  RankingForm.ModalResult := mrOk;
end;
procedure TForm2.form2onclose(Sender: TObject; var Action: TCloseAction); { $0043A504 }
begin
  MainForm.Timer2.Enabled := True;
  RankingForm.ModalResult := mrOk;
end;
procedure TForm2.BitBtn1Click(Sender: TObject);
begin
  RankingCategory := 1;
  Button1.Enabled := True;
  hyouji(1);
end;
procedure TForm2.BitBtn2Click(Sender: TObject);
begin
  RankingCategory := 2;
  Button1.Enabled := True;
  hyouji(2);
end;
procedure TForm2.BitBtn3Click(Sender: TObject);
begin
  RankingCategory := 3;
  Button1.Enabled := True;
  hyouji(3);
end;
procedure TForm2.BitBtn4Click(Sender: TObject);
begin
  RankingCategory := 4;
  Button1.Enabled := True;
  hyouji(4);
end;
procedure TForm2.BitBtn5Click(Sender: TObject);
begin
  RankingCategory := 5;
  Button1.Enabled := True;
  hyouji(5);
end;
procedure TForm2.Button1Click(Sender: TObject); { $0043A5F0 }
var
  Column, Row: Longint;
begin
  if MessageDlg('Initialize this data. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
  begin
    RankingHero.Word348 := RankingCategory;
    case RankingCategory of
      1:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 500;
        RankingRows[1, 3] := 25;
        RankingRows[1, 4] := 25;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 450;
        RankingRows[2, 3] := 24;
        RankingRows[2, 4] := 24;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 400;
        RankingRows[3, 3] := 23;
        RankingRows[3, 4] := 23;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 350;
        RankingRows[4, 3] := 22;
        RankingRows[4, 4] := 22;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 300;
        RankingRows[5, 3] := 21;
        RankingRows[5, 4] := 21;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 250;
        RankingRows[6, 3] := 20;
        RankingRows[6, 4] := 20;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 200;
        RankingRows[7, 3] := 19;
        RankingRows[7, 4] := 19;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 150;
        RankingRows[8, 3] := 18;
        RankingRows[8, 4] := 18;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 100;
        RankingRows[9, 3] := 17;
        RankingRows[9, 4] := 17;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 50;
        RankingRows[10, 3] := 16;
        RankingRows[10, 4] := 16;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      2:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 1000;
        RankingRows[1, 3] := 50;
        RankingRows[1, 4] := 50;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 900;
        RankingRows[2, 3] := 45;
        RankingRows[2, 4] := 45;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 800;
        RankingRows[3, 3] := 40;
        RankingRows[3, 4] := 40;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 700;
        RankingRows[4, 3] := 35;
        RankingRows[4, 4] := 35;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 600;
        RankingRows[5, 3] := 30;
        RankingRows[5, 4] := 30;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 500;
        RankingRows[6, 3] := 25;
        RankingRows[6, 4] := 25;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 400;
        RankingRows[7, 3] := 20;
        RankingRows[7, 4] := 20;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 300;
        RankingRows[8, 3] := 15;
        RankingRows[8, 4] := 15;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 200;
        RankingRows[9, 3] := 10;
        RankingRows[9, 4] := 10;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 100;
        RankingRows[10, 3] := 5;
        RankingRows[10, 4] := 5;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      3, 5:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 10000;
        RankingRows[1, 3] := 500;
        RankingRows[1, 4] := 500;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 9000;
        RankingRows[2, 3] := 450;
        RankingRows[2, 4] := 450;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 8000;
        RankingRows[3, 3] := 400;
        RankingRows[3, 4] := 400;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 7000;
        RankingRows[4, 3] := 350;
        RankingRows[4, 4] := 350;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 6000;
        RankingRows[5, 3] := 300;
        RankingRows[5, 4] := 300;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 5000;
        RankingRows[6, 3] := 250;
        RankingRows[6, 4] := 250;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 4000;
        RankingRows[7, 3] := 200;
        RankingRows[7, 4] := 200;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 3000;
        RankingRows[8, 3] := 150;
        RankingRows[8, 4] := 150;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 2000;
        RankingRows[9, 3] := 100;
        RankingRows[9, 4] := 100;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 1000;
        RankingRows[10, 3] := 50;
        RankingRows[10, 4] := 50;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
      4:
      begin
        RankingRows[1, 1] := 100;
        RankingRows[1, 2] := 5000;
        RankingRows[1, 3] := 200;
        RankingRows[1, 4] := 200;
        RankingRows[1, 5] := 0;
        RankingRows[1, 6] := 0;
        RankingRows[2, 1] := 90;
        RankingRows[2, 2] := 4500;
        RankingRows[2, 3] := 190;
        RankingRows[2, 4] := 190;
        RankingRows[2, 5] := 0;
        RankingRows[2, 6] := 0;
        RankingRows[3, 1] := 80;
        RankingRows[3, 2] := 4000;
        RankingRows[3, 3] := 180;
        RankingRows[3, 4] := 180;
        RankingRows[3, 5] := 0;
        RankingRows[3, 6] := 0;
        RankingRows[4, 1] := 70;
        RankingRows[4, 2] := 3500;
        RankingRows[4, 3] := 170;
        RankingRows[4, 4] := 170;
        RankingRows[4, 5] := 0;
        RankingRows[4, 6] := 0;
        RankingRows[5, 1] := 60;
        RankingRows[5, 2] := 3000;
        RankingRows[5, 3] := 160;
        RankingRows[5, 4] := 160;
        RankingRows[5, 5] := 0;
        RankingRows[5, 6] := 0;
        RankingRows[6, 1] := 50;
        RankingRows[6, 2] := 2500;
        RankingRows[6, 3] := 150;
        RankingRows[6, 4] := 150;
        RankingRows[6, 5] := 0;
        RankingRows[6, 6] := 0;
        RankingRows[7, 1] := 40;
        RankingRows[7, 2] := 2000;
        RankingRows[7, 3] := 140;
        RankingRows[7, 4] := 140;
        RankingRows[7, 5] := 0;
        RankingRows[7, 6] := 0;
        RankingRows[8, 1] := 30;
        RankingRows[8, 2] := 1500;
        RankingRows[8, 3] := 130;
        RankingRows[8, 4] := 130;
        RankingRows[8, 5] := 0;
        RankingRows[8, 6] := 0;
        RankingRows[9, 1] := 20;
        RankingRows[9, 2] := 1000;
        RankingRows[9, 3] := 120;
        RankingRows[9, 4] := 120;
        RankingRows[9, 5] := 0;
        RankingRows[9, 6] := 0;
        RankingRows[10, 1] := 10;
        RankingRows[10, 2] := 500;
        RankingRows[10, 3] := 110;
        RankingRows[10, 4] := 110;
        RankingRows[10, 5] := 0;
        RankingRows[10, 6] := 0;
        RankingRows[11, 1] := 0;
        RankingRows[11, 2] := 0;
        RankingRows[11, 3] := 0;
        RankingRows[11, 4] := 0;
        RankingRows[11, 5] := 0;
        RankingRows[11, 6] := 0;
        RankingRows[12, 1] := 0;
        RankingRows[12, 2] := 0;
        RankingRows[12, 3] := 0;
        RankingRows[12, 4] := 0;
        RankingRows[12, 5] := 0;
        RankingRows[12, 6] := 0;
      end;
    end;
    Memo21.Lines.Clear;
    Memo22.Lines.Clear;
    Memo23.Lines.Clear;
    Memo24.Lines.Clear;
    Memo25.Lines.Clear;
    Memo26.Lines.Clear;
    Memo27.Lines.Clear;
    Memo28.Lines.Clear;
    Memo29.Lines.Clear;
    Memo30.Lines.Clear;
    case RankingCategory of
      1:
      begin
        Memo21.Lines[0] := 'Skeleton A';
        Memo22.Lines[0] := 'Priest';
        Memo23.Lines[0] := 'Skeleton B';
        Memo24.Lines[0] := 'Gate-Keeper C';
        Memo25.Lines[0] := 'Skeleton C';
        Memo26.Lines[0] := 'Bat';
        Memo27.Lines[0] := 'Red Slime';
        Memo28.Lines[0] := 'Green Slime';
        Memo29.Lines[0] := 'Iron Sword';
        Memo30.Lines[0] := 'Iron Shield';
      end;
      2:
      begin
        Memo21.Lines[0] := 'Vampire';
        Memo22.Lines[0] := 'Superion Priest';
        Memo23.Lines[0] := 'Zombie Knight';
        Memo24.Lines[0] := 'Gate-Keeper B';
        Memo25.Lines[0] := 'Rock';
        Memo26.Lines[0] := 'Big Octopus';
        Memo27.Lines[0] := 'Zombie';
        Memo28.Lines[0] := 'Big Bat';
        Memo29.Lines[0] := 'Big Slime';
        Memo30.Lines[0] := 'Blue Crystal';
      end;
      3:
      begin
        Memo21.Lines[0] := 'Magic Master';
        Memo22.Lines[0] := 'Thief';
        Memo23.Lines[0] := 'Fairy';
        Memo24.Lines[0] := 'Merchant';
        Memo25.Lines[0] := 'Princess';
        Memo26.Lines[0] := 'Old Man';
        Memo27.Lines[0] := 'Brave Man';
        Memo28.Lines[0] := 'Mattock';
        Memo29.Lines[0] := 'Cross';
        Memo30.Lines[0] := 'Lucky Gold';
      end;
      4:
      begin
        Memo21.Lines[0] := 'Golden Knight';
        Memo22.Lines[0] := 'Knight';
        Memo23.Lines[0] := 'Fancer';
        Memo24.Lines[0] := 'Soldier';
        Memo25.Lines[0] := 'Ghost Soldier';
        Memo26.Lines[0] := 'Dragon';
        Memo27.Lines[0] := 'Swordsman';
        Memo28.Lines[0] := 'Slime Man';
        Memo29.Lines[0] := 'Sword of Knight';
        Memo30.Lines[0] := 'Shield of Knight';
      end;
      5:
      begin
        Memo21.Lines[0] := 'Zeno';
        Memo22.Lines[0] := 'Magician A';
        Memo23.Lines[0] := 'Black Knight';
        Memo24.Lines[0] := 'Magic Sergeant';
        Memo25.Lines[0] := 'Gate-Keeper A';
        Memo26.Lines[0] := 'Bloodsucker Bat';
        Memo27.Lines[0] := 'Magician B';
        Memo28.Lines[0] := 'King Slime';
        Memo29.Lines[0] := 'Holy Sword';
        Memo30.Lines[0] := 'Holy Shield';
      end;
    end;
    { Rows carry two checksums; the final two rows check each column. }
    for Row := 1 to 10 do
    begin
      RankingRows[Row, 5] := 0;
      for Column := 1 to 4 do
        RankingRows[Row, 5] := RankingRows[Row, 5] + RankingRows[Row, Column];
      RankingRows[Row, 6] := 0;
      for Column := 1 to 5 do
        case Column of
          1, 3, 5: RankingRows[Row, 6] := RankingRows[Row, 6] + RankingRows[Row, Column];
          2, 4: RankingRows[Row, 6] := RankingRows[Row, 6] - RankingRows[Row, Column];
        end;
    end;
    for Row := 1 to 6 do
    begin
      RankingRows[11, Row] := 0;
      for Column := 1 to 10 do
        RankingRows[11, Row] := RankingRows[11, Row] + RankingRows[Column, Row];
      RankingRows[12, Row] := 0;
      for Column := 1 to 11 do
        case Column of
          1, 3, 5, 7, 9, 11:
            RankingRows[12, Row] := RankingRows[12, Row] + RankingRows[Column, Row];
          2, 4, 6, 8, 10: RankingRows[12, Row] := RankingRows[12, Row] - RankingRows[Column, Row];
        end;
    end;
    RankingRows[12, 6] := RankingHero.Word628 * 100 + (-1) * RankingHero.Word348;
    case RankingCategory of
      1: RankingPath := MainForm.Memo12.Lines[0] + '\option1.dat';
      2: RankingPath := MainForm.Memo12.Lines[0] + '\option2.dat';
      3: RankingPath := MainForm.Memo12.Lines[0] + '\option3.dat';
      4: RankingPath := MainForm.Memo12.Lines[0] + '\option4.dat';
      5: RankingPath := MainForm.Memo12.Lines[0] + '\option5.dat';
    end;
    AssignFile(RankingFile, RankingPath);
    Rewrite(RankingFile, 1);
    BlockWrite(RankingFile, RankingRows, SizeOf(RankingRows));
    CloseFile(RankingFile);
    case RankingCategory of
      1: RankingPath := MainForm.Memo12.Lines[0] + '\option11.dat';
      2: RankingPath := MainForm.Memo12.Lines[0] + '\option21.dat';
      3: RankingPath := MainForm.Memo12.Lines[0] + '\option31.dat';
      4: RankingPath := MainForm.Memo12.Lines[0] + '\option41.dat';
      5: RankingPath := MainForm.Memo12.Lines[0] + '\option51.dat';
    end;
    Memo62.Lines.Clear;
    Memo62.Lines.AddStrings(Memo21.Lines);
    Memo62.Lines.AddStrings(Memo22.Lines);
    Memo62.Lines.AddStrings(Memo23.Lines);
    Memo62.Lines.AddStrings(Memo24.Lines);
    Memo62.Lines.AddStrings(Memo25.Lines);
    Memo62.Lines.AddStrings(Memo26.Lines);
    Memo62.Lines.AddStrings(Memo27.Lines);
    Memo62.Lines.AddStrings(Memo28.Lines);
    Memo62.Lines.AddStrings(Memo29.Lines);
    Memo62.Lines.AddStrings(Memo30.Lines);
    Memo62.Lines.SaveToFile(RankingPath);
    hyouji(RankingCategory);
  end;
end;

procedure TForm4.Button1Click(Sender: TObject); { $004402E8 }
var
  Stream: TMemoryStream;
  WindowPath, OldName, OldAssets: string;
begin
  Stream := TMemoryStream.Create;
  SetLength(WindowPath, 255);
  GetWindowsDirectory(PChar(WindowPath), 255);
  SetLength(WindowPath, StrLen(PChar(WindowPath)));
  MainForm.Memo12.Lines.LoadFromFile(WindowPath + '\TSW12.INI');
  OldName := MainForm.Memo12.Lines[2];
  OldAssets := MainForm.Memo12.Lines[1];
  { Copy option and ranking files as binary streams. }
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option.dat');
  Stream.SaveToFile(memo1.Text + '\option.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option1.dat');
  Stream.SaveToFile(memo1.Text + '\option1.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option11.dat');
  Stream.SaveToFile(memo1.Text + '\option11.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option2.dat');
  Stream.SaveToFile(memo1.Text + '\option2.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option21.dat');
  Stream.SaveToFile(memo1.Text + '\option21.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option3.dat');
  Stream.SaveToFile(memo1.Text + '\option3.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option31.dat');
  Stream.SaveToFile(memo1.Text + '\option31.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option4.dat');
  Stream.SaveToFile(memo1.Text + '\option4.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option41.dat');
  Stream.SaveToFile(memo1.Text + '\option41.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option5.dat');
  Stream.SaveToFile(memo1.Text + '\option5.dat');
  Stream.LoadFromFile(MainForm.Memo12.Lines[0] + '\option51.dat');
  Stream.SaveToFile(memo1.Text + '\option51.dat');
  Stream.Free;
  MainForm.Memo12.Lines.Clear;
  MainForm.Memo12.Lines.Add(memo1.Text);
  MainForm.Memo12.Lines.Add(OldAssets);
  MainForm.Memo12.Lines.Add(OldName);
  MainForm.Memo12.Lines.SaveToFile(WindowPath + '\TSW12.INI');
  DataHolderForm.ModalResult := mrOk;
end;

procedure TForm4.SelectPortableFolder(Sender: TObject);
var
  Destination, Source, SettingsPath: string;
  I: Integer;
  Lines: TStringList;
begin
  Destination := DirectoryListBox1.Directory;
  if not DirectoryExists(Destination) then
    Exit;
  Lines := TStringList.Create;
  try
    for I := 0 to 5 do
    begin
      if I = 0 then
        Source := 'option.dat'
      else
        Source := 'option' + IntToStr(I) + '.dat';
      if FileExists(SaveDataPath(Source))
          and (CompareText(
                  ExpandFileName(SaveDataPath(Source)),
                  ExpandFileName(Destination + '\' + Source))
              <> 0) then
        if not CopyFile(PChar(SaveDataPath(Source)), PChar(Destination + '\' + Source), False) then
          raise Exception.Create('Cannot copy ' + Source);
      if I > 0 then
      begin
        Source := 'option' + IntToStr(I) + '1.dat';
        if FileExists(SaveDataPath(Source))
            and (CompareText(
                    ExpandFileName(SaveDataPath(Source)),
                    ExpandFileName(Destination + '\' + Source))
                <> 0) then
          if not CopyFile(
              PChar(SaveDataPath(Source)),
              PChar(Destination + '\' + Source),
              False) then
            raise Exception.Create('Cannot copy ' + Source);
      end;
    end;
    SaveDirectory := Destination;
    Lines.Add(SaveDirectory);
    Lines.Add(AssetDirectory);
    Lines.Add(PlayerName);
    MainForm.Memo12.Lines.Assign(Lines);
    SettingsPath := ExtractFilePath(ParamStr(0)) + 'TSW12.INI';
    Lines.SaveToFile(SettingsPath);
    ModalResult := mrOk;
  finally
    Lines.Free;
  end;
end;

procedure TForm4.Button3Click(Sender: TObject); { $00440984 }
var
  Path: string;
begin
  Path := memo1.Text + '\';
  if InputQuery('Make holder', 'Please, input the name of holder', Path) = True then
    if CreateDir(Path) = True then
    begin
      memo1.Text := Path;
      DriveComboBox1.Drive := Path[1];
      DirectoryListBox1.Directory := Path;
    end;
end;
