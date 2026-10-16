{ Synchronize menu choices, saved options and live controls. }

{ Map animation, events and mouse repeat share the selected speed. }

procedure TTSW10.speedhigh; { $0047F47C }
begin
  Timer1.Interval := 150;
  Timer2.Interval := 150;
  Timer3.Interval := 150;
  High1.Checked := True;
  Middle1.Checked := False;
  Low1.Checked := False;
  GameOptions[3] := 1;
end;

procedure TTSW10.speedmiddle; { $0047F4E0 }
begin
  Timer1.Interval := 250;
  Timer2.Interval := 250;
  Timer3.Interval := 250;
  High1.Checked := False;
  Middle1.Checked := True;
  Low1.Checked := False;
  GameOptions[3] := 2;
end;

procedure TTSW10.speedlow; { $0047F544 }
begin
  Timer1.Interval := 350;
  Timer2.Interval := 350;
  Timer3.Interval := 350;
  High1.Checked := False;
  Middle1.Checked := False;
  Low1.Checked := True;
  GameOptions[3] := 3;
end;

procedure TTSW10.timerin; { $0047F5A8 }
begin
  if Middle1.Checked then
    speedmiddle;
  if High1.Checked then
    speedhigh;
  if Low1.Checked then
    speedlow;
end;

procedure TTSW10.optionl1; { $0047D4A4 }
begin
  tiny1.Checked := False;
  Small1.Checked := False;
  Normal1.Checked := False;
  Large1.Checked := False;
  case GameOptions[0] of
    8:
      if GameOptions[1] = 10 then
        tiny1.Checked := True;
    9:
      if GameOptions[1] = 11 then
        Small1.Checked := True;
    10:
      if GameOptions[1] = 12 then
        Normal1.Checked := True;
    12:
      if GameOptions[1] = 14 then
        Large1.Checked := True;
  end;
  Memo1.Font.Size := GameOptions[0];
  Memo2.Font.Size := GameOptions[0];
  Memo3.Font.Size := GameOptions[0];
  Memo4.Font.Size := GameOptions[0];
  Memo9.Font.Size := GameOptions[0];
  Memo10.Font.Size := GameOptions[0];
  Memo8.Font.Size := GameOptions[0];
  Memo5.Font.Size := GameOptions[0];
  Memo6.Font.Size := GameOptions[0];
  Memo7.Font.Size := GameOptions[0];
  Edit13.Font.Size := GameOptions[0];
  Edit14.Font.Size := GameOptions[0];
  Edit15.Font.Size := GameOptions[0];
  Edit16.Font.Size := GameOptions[0];
  Edit17.Font.Size := GameOptions[0];
  Edit18.Font.Size := GameOptions[0];
  Edit19.Font.Size := GameOptions[0];
  Edit20.Font.Size := GameOptions[0];
  Edit21.Font.Size := GameOptions[0];
  Edit22.Font.Size := GameOptions[0];
  Edit23.Font.Size := GameOptions[0];
  Edit24.Font.Size := GameOptions[0];
  Edit25.Font.Size := GameOptions[0];
  Edit26.Font.Size := GameOptions[0];
  Edit27.Font.Size := GameOptions[0];
  Edit28.Font.Size := GameOptions[0];
  Edit29.Font.Size := GameOptions[0];
  Edit30.Font.Size := GameOptions[0];
  Edit31.Font.Size := GameOptions[0];
  Edit32.Font.Size := GameOptions[0];
  Edit33.Font.Size := GameOptions[0];
  Memo11.Font.Size := GameOptions[1];
  Edit8.Font.Size := GameOptions[1];
  RichEdit1.Font.Size := GameOptions[1];
  Button39.Font.Size := GameOptions[1];
  Button40.Font.Size := GameOptions[1];
  Button41.Font.Size := GameOptions[1];
  Button42.Font.Size := GameOptions[1];

  High1.Checked := False;
  Middle1.Checked := False;
  Low1.Checked := False;
  case GameOptions[3] of
    1: High1.Checked := True;
    2: Middle1.Checked := True;
    3: Low1.Checked := True;
  end;
  timerin;
  case GameOptions[4] of
    0:
    begin
      GameOptions[4] := 0;
      MouseControl1.Checked := True;
      KeyboardControl1.Checked := False;
      itemdel;
      MainForm.KeyPreview := False;
      itemlive;
    end;
    1:
    begin
      GameOptions[4] := 1;
      MouseControl1.Checked := False;
      KeyboardControl1.Checked := True;
      itemdel;
      MainForm.KeyPreview := True;
      itemlive;
    end;
  end;
  case GameOptions[5] of
    0: K5.Checked := False;
    1: K5.Checked := True;
  end;
  case GameOptions[6] of
    0:
    begin
      MediaPlayer5.Close;
      Hero.music_track := 0;
      GameOptions[6] := 0;
      BGMON1.Checked := False;
    end;
    1:
    begin
      BGMON1.Checked := True;
      soundcheck;
      GameOptions[6] := 1;
      soundplay;
    end;
  end;
  case GameOptions[7] of
    0:
    begin
      Hero.effects_muted := 0;
      wavon1.Checked := True;
    end;
    1:
    begin
      Hero.effects_muted := 1;
      wavon1.Checked := False;
    end;
  end;
  case GameOptions[8] of
    0:
    begin
      N800x5001.Checked := False;
      N640x4001.Checked := True;
    end;
    1:
    begin
      N800x5001.Checked := True;
      N640x4001.Checked := False;
    end;
  end;
end;

procedure TTSW10.High1Click(Sender: TObject);
begin
  speedhigh;
end;
procedure TTSW10.Middle1Click(Sender: TObject);
begin
  speedmiddle;
end;
procedure TTSW10.Low1Click(Sender: TObject);
begin
  speedlow;
end;

procedure TTSW10.Large1Click(Sender: TObject); { $0047F6CC }
begin
  Large1.Checked := True;
  Small1.Checked := False;
  Normal1.Checked := False;
  tiny1.Checked := False;
  GameOptions[0] := 12;
  GameOptions[1] := 14;
  GameOptions[2] := 0;
  optionl1;
end;
procedure TTSW10.Small1Click(Sender: TObject); { $0047F724 }
begin
  Large1.Checked := False;
  Small1.Checked := True;
  Normal1.Checked := False;
  tiny1.Checked := False;
  GameOptions[0] := 9;
  GameOptions[1] := 11;
  GameOptions[2] := 0;
  optionl1;
end;
procedure TTSW10.Normal1Click(Sender: TObject); { $0047F77C }
begin
  Large1.Checked := False;
  Small1.Checked := False;
  Normal1.Checked := True;
  tiny1.Checked := False;
  GameOptions[0] := 10;
  GameOptions[1] := 12;
  GameOptions[2] := 0;
  optionl1;
end;
procedure TTSW10.tiny1Click(Sender: TObject); { $00480E0C }
begin
  Large1.Checked := False;
  Small1.Checked := False;
  Normal1.Checked := False;
  tiny1.Checked := True;
  GameOptions[0] := 8;
  GameOptions[1] := 10;
  GameOptions[2] := 0;
  optionl1;
end;

procedure TTSW10.KeyboardControl1Click(Sender: TObject); { $00480E64 }
begin
  itemdel;
  BitBtn1.Visible := False;
  BitBtn2.Visible := False;
  BitBtn3.Visible := False;
  BitBtn4.Visible := False;
  GameOptions[4] := 1;
  MouseControl1.Checked := False;
  KeyboardControl1.Checked := True;
  itemdel;
  MainForm.KeyPreview := True;
  itemlive;
end;

procedure TTSW10.MouseControl1Click(Sender: TObject); { $00480EE0 }
begin
  itemdel;
  GameOptions[4] := 0;
  { The introduction keeps movement buttons hidden until gameplay starts. }
  if not Timer4.Enabled then
  begin
    BitBtn1.Visible := True;
    BitBtn2.Visible := True;
    BitBtn3.Visible := True;
    BitBtn4.Visible := True;
  end;
  MouseControl1.Checked := True;
  KeyboardControl1.Checked := False;
  MainForm.KeyPreview := False;
  itemlive;
end;

procedure TTSW10.N800x5001Click(Sender: TObject); { $00484CAC }
begin
  if (GameOptions[8] = 0) and (Screen.Width >= 800) then
  begin
    N800x5001.Checked := True;
    N640x4001.Checked := False;
    GameOptions[8] := 1;
    ImageList1.Clear;
    ImageList2.Clear;
    ImageList3.Clear;
    syokidata0;
    optionl1;
    syokidata2;
    itemlive;
  end
  else if Screen.Width < 800 then
    ShowMessage('Cannot. Need display size 800x600.');
end;

procedure TTSW10.N640x4001Click(Sender: TObject); { $00484D74 }
begin
  if GameOptions[8] = 1 then
  begin
    N800x5001.Checked := False;
    N640x4001.Checked := True;
    GameOptions[8] := 0;
    ImageList1.Clear;
    ImageList2.Clear;
    ImageList3.Clear;
    syokidata0;
    optionl1;
    syokidata2;
    itemlive;
  end;
end;

procedure TTSW10.NormalOption1Click(Sender: TObject); { $0047F5E8 }
begin
  if MessageDlg('Initialize options. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
  begin
    GameOptions[0] := 10;
    GameOptions[1] := 12;
    GameOptions[2] := 0;
    GameOptions[3] := 2;
    GameOptions[4] := 0;
    GameOptions[5] := 1;
    GameOptions[6] := 0;
    GameOptions[7] := 0;
    GameOptions[9] := 0;
    if GameOptions[8] = 1 then
    begin
      GameOptions[8] := 0;
      ImageList1.Clear;
      ImageList2.Clear;
      ImageList3.Clear;
      syokidata0;
      optionl1;
      syokidata2;
      itemlive;
    end
    else
      optionl1;
  end;
end;

procedure TTSW10.buttonfocus; { $00442D50 }
begin
  case FacingRequest of
    1:
      if BitBtn1.Visible = True then
        BitBtn1.SetFocus;
    2:
      if BitBtn2.Visible = True then
        BitBtn2.SetFocus;
    3:
      if BitBtn3.Visible = True then
        BitBtn3.SetFocus;
    4:
      if BitBtn4.Visible = True then
        BitBtn4.SetFocus;
  end;
end;

procedure TTSW10.GameStart1Click(Sender: TObject); { $004637E8 }
begin
  if Timer4.Enabled = False then
  begin
    if MessageDlg('This game is over. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
    begin
      Hero.cycle_factor_minus_one := 0;
      Hero.later_cycle := 0;
      gameover;
    end;
  end
  else
  begin
    Timer4.Enabled := False;
    Hero.cycle_factor_minus_one := 0;
    Hero.later_cycle := 0;
    gameover;
  end;
end;

procedure TTSW10.GameQuit1Click(Sender: TObject); { $00463874 }
begin
  if MessageDlg('This game is over. Is it true?', mtInformation, [mbYes, mbNo], 0) = mrYes then
  begin
    if BGMON1.Checked = True then
      MediaPlayer5.Close;
    MapBitmap1.Free;
    MapBitmap2.Free;
    WorkBitmap1.Free;
    WorkBitmap2.Free;
    WorkBitmap3.Free;
    FrameBitmap.Free;
    Application.Terminate;
  end;
end;

procedure TTSW10.Exit1Click(Sender: TObject); { $0046391C }
begin
  if BGMON1.Checked = True then
    MediaPlayer5.Close;
  MapBitmap1.Free;
  MapBitmap2.Free;
  WorkBitmap1.Free;
  WorkBitmap2.Free;
  WorkBitmap3.Free;
  FrameBitmap.Free;
  Application.Terminate;
end;

procedure TTSW10.TSW10close(Sender: TObject; var Action: TCloseAction); { $00484B14 }
begin
  MapBitmap1.Free;
  MapBitmap2.Free;
  WorkBitmap1.Free;
  WorkBitmap2.Free;
  WorkBitmap3.Free;
  FrameBitmap.Free;
  Application.Terminate;
end;

procedure TTSW10.Help2Click(Sender: TObject); { $0047D2D8 }
begin
  ShellExecute(Handle, 'open', '.\tsw.hlp', '', '', SW_SHOW);
end;

procedure TTSW10.About1Click(Sender: TObject); { $0047D318 }
begin
  AboutBox.ShowModal;
end;

procedure TTSW10.K6Click(Sender: TObject); { $00484A50 }
begin
  DataHolderForm.memo1.Text := Memo12.Lines[0];
  SaveDirectory := Memo12.Lines[0];
  DataHolderForm.DriveComboBox1.Drive := SaveDirectory[1];
  DataHolderForm.DirectoryListBox1.Directory := SaveDirectory;
  DataHolderForm.ShowModal;
end;

procedure TTSW10.image34click(Sender: TObject); { $00484DE0 }
begin
  append;
end;

procedure TTSW10.HighScore1Click(Sender: TObject); { $00482988 }
begin
  Hero.Word344 := 0;
  Hero.Word348 := 0;
  IOPath := Memo12.Lines[0] + '\save0.dat';
  AssignFile(SettingsFile, IOPath);
  Rewrite(SettingsFile, 1);
  BlockWrite(SettingsFile, Maps, SizeOf(Maps));
  BlockWrite(SettingsFile, Hero, SizeOf(Hero));
  CloseFile(SettingsFile);
  RankingForm.ShowModal;
end;
