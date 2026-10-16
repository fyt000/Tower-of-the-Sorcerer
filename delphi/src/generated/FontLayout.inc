  tiny1.Checked := False;
  Small1.Checked := False;
  Normal1.Checked := False;
  Large1.Checked := False;
  if GameOptions[0] = 8 then
  begin
    if GameOptions[1] = 10 then
    begin
      tiny1.Checked := True;
    end;
  end
  else if GameOptions[0] = 9 then
  begin
    if GameOptions[1] = $B then
    begin
      Small1.Checked := True;
    end;
  end
  else if GameOptions[0] = 10 then
  begin
    if GameOptions[1] = $C then
    begin
      Normal1.Checked := True;
    end;
  end
  else if (GameOptions[0] = $C) and (GameOptions[1] = $E) then
  begin
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
  if GameOptions[3] = 1 then
  begin
    High1.Checked := True;
  end
  else if GameOptions[3] = 2 then
  begin
    Middle1.Checked := True;
  end
  else if GameOptions[3] = 3 then
  begin
    Low1.Checked := True;
  end;
