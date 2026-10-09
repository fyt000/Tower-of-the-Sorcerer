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
  ApplyFontLayout(Self);
  High1.Checked := False;
  Middle1.Checked := False;
  Low1.Checked := False;
  case GameOptions[3] of
    1: High1.Checked := True;
    2: Middle1.Checked := True;
    3: Low1.Checked := True;
  end;
  timerin;
  if GameOptions[4] = 0 then
  begin
    MouseControl1.Checked := True;
    KeyboardControl1.Checked := False;
    itemdel;
    MainForm.KeyPreview := False;
    itemlive;
  end
  else if GameOptions[4] = 1 then
  begin
    MouseControl1.Checked := False;
    KeyboardControl1.Checked := True;
    itemdel;
    MainForm.KeyPreview := True;
    itemlive;
  end;
  if GameOptions[5] = 0 then
    K5.Checked := False
  else if GameOptions[5] = 1 then
    K5.Checked := True;
  if GameOptions[6] = 0 then
  begin
    if MediaPlayer5.DeviceID <> 0 then
      MediaPlayer5.Stop;
    Hero.music_track := 0;
    BGMON1.Checked := False;
  end
  else if GameOptions[6] = 1 then
  begin
    BGMON1.Checked := True;
    soundcheck;
    soundplay;
  end;
  if GameOptions[7] = 0 then
  begin
    Hero.effects_muted := 0;
    wavon1.Checked := True;
  end
  else if GameOptions[7] = 1 then
  begin
    Hero.effects_muted := 1;
    wavon1.Checked := False;
  end;
  if GameOptions[8] = 0 then
  begin
    N800x5001.Checked := False;
    N640x4001.Checked := True;
  end
  else if GameOptions[8] = 1 then
  begin
    N800x5001.Checked := True;
    N640x4001.Checked := False;
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

procedure RebuildLayout(Form: TTSW10);
begin
  with Form do
  begin
    { Tile atlases and working bitmaps depend on the selected window size. }
    ImageList1.Clear;
    ImageList2.Clear;
    ImageList3.Clear;
    ReleaseGraphics;
    syokidata0;
    optionl1;
    syokidata2;
    itemlive;
  end;
end;

procedure TTSW10.N800x5001Click(Sender: TObject); { $00484CAC }
begin
  if (GameOptions[8] = 0) and (Screen.Width > 799) then
  begin
    N800x5001.Checked := True;
    N640x4001.Checked := False;
    GameOptions[8] := 1;
    RebuildLayout(Self);
    Exit;
  end;
  if Screen.Width < 800 then
    ShowMessage('Cannot. Need display size 800x600.');
end;

procedure TTSW10.N640x4001Click(Sender: TObject); { $00484D74 }
begin
  if GameOptions[8] = 1 then
  begin
    N800x5001.Checked := False;
    N640x4001.Checked := True;
    GameOptions[8] := 0;
    RebuildLayout(Self);
  end;
end;

procedure TTSW10.NormalOption1Click(Sender: TObject); { $0047F5E8 }
var
  WasLarge: Boolean;
begin
  if MessageDlg('Initialize options. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
    Exit;
  WasLarge := GameOptions[8] = 1;
  GameOptions[0] := 10;
  GameOptions[1] := 12;
  GameOptions[2] := 0;
  GameOptions[3] := 2;
  GameOptions[4] := 0;
  GameOptions[5] := 1;
  GameOptions[6] := 0;
  GameOptions[7] := 0;
  GameOptions[9] := 0;
  if WasLarge then
  begin
    GameOptions[8] := 0;
    RebuildLayout(Self);
  end
  else
    optionl1;
end;

procedure TTSW10.buttonfocus; { $00442D50 }
begin
  case FacingRequest of
    1:
      if BitBtn1.Enabled then
        BitBtn1.SetFocus;
    2:
      if BitBtn2.Enabled then
        BitBtn2.SetFocus;
    3:
      if BitBtn3.Enabled then
        BitBtn3.SetFocus;
    4:
      if BitBtn4.Enabled then
        BitBtn4.SetFocus;
  end;
end;

procedure TTSW10.GameStart1Click(Sender: TObject); { $004637E8 }
begin
  if not Timer4.Enabled then
    if MessageDlg('This game is over. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
      Exit;
  Timer4.Enabled := False;
  Hero.cycle_factor_minus_one := 0;
  Hero.later_cycle := 0;
  gameover;
end;

procedure TTSW10.GameQuit1Click(Sender: TObject); { $00463874 }
begin
  if MessageDlg('This game is over. Is it true?', mtConfirmation, [mbYes, mbNo], 0) <> mrYes then
    Exit;
  if BGMON1.Checked and (MediaPlayer5.DeviceID <> 0) then
    MediaPlayer5.Stop;
  ReleaseGraphics;
  Application.Terminate;
end;

procedure TTSW10.Exit1Click(Sender: TObject); { $0046391C }
begin
  if BGMON1.Checked and (MediaPlayer5.DeviceID <> 0) then
    MediaPlayer5.Stop;
  ReleaseGraphics;
  Application.Terminate;
end;

procedure TTSW10.TSW10close(Sender: TObject; var Action: TCloseAction); { $00484B14 }
begin
  ReleaseGraphics;
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
var
  Directory: string;
begin
  Directory := Memo12.Lines[0];
  DataHolderForm.memo1.Text := Directory;
  SaveDirectory := Directory;
  DataHolderForm.DriveComboBox1.Drive := Directory[1];
  DataHolderForm.DirectoryListBox1.Directory := Directory;
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
  WriteSave(IOPath, True);
  RankingForm.ShowModal;
end;
