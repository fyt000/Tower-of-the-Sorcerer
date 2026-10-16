procedure TTSW10.syokidata0; { $00484F48 }
var
  Row, Column: Longint;
begin
  if (Screen.Width < 800) and (GameOptions[8] = 1) then
  begin
    GameOptions[8] := 0;
  end;
  case GameOptions[8] of
    0:
    begin
      if Screen.Width < 800 then
      begin
        k1.Enabled := False;
      end;
      DataDirectory := '\data';
      UiSpan := $90;
      UiStep := $18;
    end;
    1:
    begin
      DataDirectory := '\data3';
      UiSpan := $B4;
      UiStep := $1E;
    end;
  end;
  MainForm.Top := 0;
  case GameOptions[8] of
    0:
    begin
      if Screen.Width <= $280 then
      begin
        MainForm.Left := $FFFFFFFC;
        MainForm.ClientHeight := $1A8;
        MainForm.Width := $288;
      end
      else
      begin
        MainForm.Left := 0;
        MainForm.ClientHeight := $1A8;
        MainForm.Width := $288;
      end;
    end;
    1:
    begin
      if Screen.Width <= $320 then
      begin
        MainForm.Left := $FFFFFFFD;
        MainForm.ClientHeight := $212;
        MainForm.Width := $328;
      end
      else
      begin
        MainForm.Left := 0;
        MainForm.ClientHeight := $212;
        MainForm.Width := $328;
      end;
    end;
  end;
  case GameOptions[8] of
    0:
    begin
      Image1.Height := 400;
      Image1.Width := $186;
      Image1.Top := 0;
      Image1.Left := $7D;
      Image6.Height := $20;
      Image6.Width := Image6.Height;
      Image6.Top := $C0;
      Image6.Left := (Image2.Left + ((Image1.Left) div 2)) - (((Image6.Width * 3)) div 2);
    end;
    1:
    begin
      Image1.Height := 500;
      Image1.Width := $1E8;
      Image1.Top := 0;
      Image1.Left := $9C;
      Image6.Height := $28;
      Image6.Width := Image6.Height;
      Image6.Top := $F0;
      Image6.Left := (Image2.Left + ((Image1.Left) div 2)) - (((Image6.Width * 3)) div 2);
    end;
  end;
  Image2.Height := Image1.Height;
  Image2.Width := Image1.Left;
  Image2.Top := Image1.Top;
  Image2.Left := 0;
  Image3.Height := Image2.Height;
  Image3.Width := Image2.Width;
  Image3.Top := Image1.Top;
  Image3.Left := Image1.Left + Image1.Width;
  Image5.Height := Image6.Height;
  Image5.Width := Image6.Width;
  Image5.Top := Image6.Top;
  Image5.Left := Image6.Left + Image6.Width;
  Image4.Height := Image6.Height;
  Image4.Width := Image6.Width;
  Image4.Top := Image6.Top;
  Image4.Left := Image5.Left + Image5.Width;
  Image7.Height := Image6.Height;
  Image7.Width := Image6.Width;
  Image7.Top := Image6.Top + Image6.Height;
  Image7.Left := Image6.Left;
  Image8.Height := Image6.Height;
  Image8.Width := Image6.Width;
  Image8.Top := Image6.Top + Image6.Height;
  Image8.Left := Image5.Left;
  Image9.Height := Image6.Height;
  Image9.Width := Image6.Width;
  Image9.Top := Image6.Top + Image6.Height;
  Image9.Left := Image4.Left;
  Image10.Height := Image6.Height;
  Image10.Width := Image6.Width;
  Image10.Top := Image7.Top + Image7.Height;
  Image10.Left := Image6.Left;
  Image11.Height := Image6.Height;
  Image11.Width := Image6.Width;
  Image11.Top := Image7.Top + Image7.Height;
  Image11.Left := Image5.Left;
  Image12.Height := Image6.Height;
  Image12.Width := Image6.Width;
  Image12.Top := Image7.Top + Image7.Height;
  Image12.Left := Image4.Left;
  Image13.Height := Image6.Height;
  Image13.Width := Image6.Width;
  Image13.Top := Image10.Top + Image10.Height;
  Image13.Left := Image6.Left;
  Image14.Height := Image6.Height;
  Image14.Width := Image6.Width;
  Image14.Top := Image10.Top + Image10.Height;
  Image14.Left := Image5.Left;
  Image15.Height := Image6.Height;
  Image15.Width := Image6.Width;
  Image15.Top := Image10.Top + Image10.Height;
  Image15.Left := Image4.Left;
  Image16.Height := Image6.Height;
  Image16.Width := Image6.Width;
  Image16.Top := Image13.Top + Image13.Height;
  Image16.Left := Image6.Left;
  Image17.Height := Image6.Height;
  Image17.Width := Image6.Width;
  Image17.Top := Image13.Top + Image13.Height;
  Image17.Left := Image5.Left;
  Image18.Height := Image6.Height;
  Image18.Width := Image6.Width;
  Image18.Top := Image13.Top + Image13.Height;
  Image18.Left := Image4.Left;
  case GameOptions[8] of
    0:
    begin
      Image19.Height := Image6.Height;
      Image19.Width := Image6.Width;
      Image19.Top := $30;
      Image19.Left := Image3.Left + $50;
      Image20.Height := Image6.Height;
      Image20.Width := Image6.Width;
      Image20.Top := $60;
      Image20.Left := Image19.Left;
      Image32.Height := Image6.Height * 2;
      Image32.Width := Image6.Width * 3;
      Image32.Top := $90;
      Image32.Left := (Image3.Left + ((Image3.Width) div 2)) - ((Image32.Width) div 2);
    end;
    1:
    begin
      Image19.Height := Image6.Height;
      Image19.Width := Image6.Width;
      Image19.Top := $3C;
      Image19.Left := Image3.Left + 100;
      Image20.Height := Image6.Height;
      Image20.Width := Image6.Width;
      Image20.Top := $78;
      Image20.Left := Image19.Left;
      Image32.Height := Image6.Height * 2;
      Image32.Width := Image6.Width * 3;
      Image32.Top := $B4;
      Image32.Left := (Image3.Left + ((Image3.Width) div 2)) - ((Image32.Width) div 2);
    end;
  end;
  Image22.Width := Image6.Height;
  Image22.Height := Image6.Width;
  Image23.Width := Image1.Width + Image2.Width + Image3.Width;
  Image23.Height := Image1.Height;
  Image24.Width := Image6.Width;
  Image24.Height := Image6.Height;
  Image25.Width := Image6.Width;
  Image25.Height := Image6.Height;
  Image26.Width := Image6.Width;
  Image26.Height := Image6.Height;
  Image27.Width := Image6.Width;
  Image27.Height := Image6.Height;
  Image28.Width := Image6.Width;
  Image28.Height := Image6.Height;
  Image29.Width := Image6.Width;
  Image29.Height := Image6.Height;
  Image30.Width := Image6.Width;
  Image30.Height := Image6.Height;
  Image31.Height := Image6.Height;
  Image31.Width := Image6.Width;
  case GameOptions[8] of
    0:
    begin
      Image31.Top := $E6;
      Image31.Left := ((Image3.Width) div 2) - $10 + Image3.Left;
      Button1.Height := $19;
      Button1.Width := $4B;
      Button1.Top := $110;
      Button1.Left := $170;
      BitBtn1.Height := $14;
      BitBtn1.Width := Image6.Width;
      BitBtn1.Top := $163;
      BitBtn1.Left := (Image3.Left + ((Image3.Width) div 2)) - ((BitBtn1.Width) div 2);
      Button2.Left := $108;
    end;
    1:
    begin
      Image31.Top := $120;
      Image31.Left := ((Image3.Width) div 2) - $10 + Image3.Left;
      Button1.Height := $1F;
      Button1.Width := $5E;
      Button1.Top := $154;
      Button1.Left := $1CC;
      BitBtn1.Height := $19;
      BitBtn1.Width := Image6.Width;
      BitBtn1.Top := $1BC;
      BitBtn1.Left := (Image3.Left + ((Image3.Width) div 2)) - ((BitBtn1.Width) div 2);
      Button2.Left := $14A;
    end;
  end;
  Button2.Height := Button1.Height;
  Button2.Width := Button1.Width;
  Button2.Top := Button1.Top;
  Button7.Height := Button1.Height;
  Button7.Width := Button1.Width;
  Button7.Top := Button1.Top;
  Button7.Left := Button1.Left;
  BitBtn2.Height := BitBtn1.Height;
  BitBtn2.Width := BitBtn1.Width;
  BitBtn2.Top := BitBtn1.Top + (((BitBtn1.Height)) div 2);
  BitBtn2.Left := (BitBtn1.Left - BitBtn2.Width) - BitBtn1.Height div 10;
  BitBtn3.Height := BitBtn1.Height;
  BitBtn3.Width := BitBtn1.Width;
  BitBtn3.Top := BitBtn2.Top;
  BitBtn3.Left := BitBtn1.Height div 10 + (BitBtn1.Left + BitBtn1.Width);
  BitBtn4.Height := BitBtn1.Height;
  BitBtn4.Width := BitBtn1.Width;
  BitBtn4.Top := BitBtn1.Height div 10 + (BitBtn1.Top + BitBtn1.Height);
  BitBtn4.Left := BitBtn1.Left;
  Button8.Height := ((Image4.Height) div 2);
  Button8.Width := Image4.Width + ((Image4.Width) div 2);
  Button8.Top := Image4.Top + Image4.Height;
  Button8.Left := (Image4.Left + ((Image4.Width) div 2)) - ((Button8.Width) div 2);
  Button9.Height := Button8.Height;
  Button9.Width := Button8.Width;
  Button9.Top := Button8.Top + Button8.Height;
  Button9.Left := Button8.Left;
  Button10.Height := Button8.Height;
  Button10.Width := Button8.Width;
  Button10.Top := Button9.Top + Button9.Height;
  Button10.Left := Button8.Left;
  Button11.Height := ((Image5.Height) div 2);
  Button11.Width := ((Image5.Width) div 2);
  Button11.Top := Image5.Top + Image5.Height;
  Button11.Left := Image5.Left - Image5.Width;
  Button12.Height := Button11.Height;
  Button12.Width := Button11.Width;
  Button12.Top := Button11.Top;
  Button12.Left := Button11.Left + Button11.Width;
  Button13.Height := Button11.Height;
  Button13.Width := Button11.Width;
  Button13.Top := Button11.Top;
  Button13.Left := Button12.Left + Button12.Width;
  Button14.Height := Button11.Height;
  Button14.Width := Button11.Width;
  Button14.Top := Button11.Top;
  Button14.Left := Button13.Left + Button13.Width;
  Button15.Height := Button11.Height;
  Button15.Width := Button11.Width;
  Button15.Top := Button11.Top;
  Button15.Left := Button14.Left + Button14.Width;
  Button16.Height := Button11.Height;
  Button16.Width := Button11.Width;
  Button16.Top := Button11.Top;
  Button16.Left := Button15.Left + Button15.Width;
  Button17.Height := Button11.Height;
  Button17.Width := Button11.Width;
  Button17.Top := Button11.Top + Button11.Height;
  Button17.Left := Button11.Left;
  Button18.Height := Button11.Height;
  Button18.Width := Button11.Width;
  Button18.Top := Button17.Top;
  Button18.Left := Button12.Left;
  Button19.Height := Button11.Height;
  Button19.Width := Button11.Width;
  Button19.Top := Button17.Top;
  Button19.Left := Button13.Left;
  Button20.Height := Button11.Height;
  Button20.Width := Button11.Width;
  Button20.Top := Button17.Top;
  Button20.Left := Button14.Left;
  Button21.Height := Button11.Height;
  Button21.Width := Button11.Width;
  Button21.Top := Button17.Top;
  Button21.Left := Button15.Left;
  Button22.Height := Button11.Height;
  Button22.Width := Button11.Width;
  Button22.Top := Button17.Top;
  Button22.Left := Button16.Left;
  Button23.Height := Button11.Height;
  Button23.Width := Button11.Width;
  Button23.Top := Button17.Top + Button17.Height;
  Button23.Left := Button11.Left;
  Button24.Height := Button11.Height;
  Button24.Width := Button11.Width;
  Button24.Top := Button23.Top;
  Button24.Left := Button12.Left;
  Button25.Height := Button11.Height;
  Button25.Width := Button11.Width;
  Button25.Top := Button23.Top;
  Button25.Left := Button13.Left;
  Button26.Height := Button11.Height;
  Button26.Width := Button11.Width;
  Button26.Top := Button23.Top;
  Button26.Left := Button14.Left;
  Button27.Height := Button11.Height;
  Button27.Width := Button11.Width;
  Button27.Top := Button23.Top;
  Button27.Left := Button15.Left;
  Button28.Height := Button11.Height;
  Button28.Width := Button11.Width;
  Button28.Top := Button23.Top;
  Button28.Left := Button16.Left;
  Button29.Height := Button11.Height;
  Button29.Width := Button11.Width;
  Button29.Top := Button23.Top + Button23.Height;
  Button29.Left := Button11.Left;
  Button30.Height := Button11.Height;
  Button30.Width := Button11.Width;
  Button30.Top := Button29.Top;
  Button30.Left := Button12.Left;
  Button31.Height := Button11.Height;
  Button31.Width := Button11.Width;
  Button31.Top := Button29.Top;
  Button31.Left := Button13.Left;
  Button32.Height := Button11.Height;
  Button32.Width := Button11.Width;
  Button32.Top := Button29.Top;
  Button32.Left := Button14.Left;
  Button33.Height := Button11.Height;
  Button33.Width := Button11.Width;
  Button33.Top := Button29.Top;
  Button33.Left := Button15.Left;
  Button34.Height := Button11.Height;
  Button34.Width := Button11.Width;
  Button34.Top := Button29.Top;
  Button34.Left := Button16.Left;
  Button35.Height := Button11.Height;
  Button35.Width := Image5.Width;
  Button35.Top := Button29.Top + Button29.Height;
  Button35.Left := Button15.Left;
  case GameOptions[8] of
    0:
    begin
      Button36.Height := $14;
      Button36.Width := $40;
      Button36.Top := $16A;
      Button36.Left := 400;
      Button39.Height := $20;
      Button39.Width := $E0;
      Button39.Top := $50;
      Button39.Left := $D0;
    end;
    1:
    begin
      Button36.Height := $19;
      Button36.Width := $50;
      Button36.Top := $1C5;
      Button36.Left := 500;
      Button39.Height := $28;
      Button39.Width := $118;
      Button39.Top := 100;
      Button39.Left := $FF;
    end;
  end;
  Button40.Height := Button39.Height;
  Button40.Width := Button39.Width;
  Button40.Top := Button39.Top + Button39.Height;
  Button40.Left := Button39.Left;
  Button41.Height := Button39.Height;
  Button41.Width := Button39.Width;
  Button41.Top := Button40.Top + Button40.Height;
  Button41.Left := Button39.Left;
  Button42.Height := Button39.Height;
  Button42.Width := Button39.Width;
  Button42.Top := Button41.Top + Button41.Height;
  Button42.Left := Button39.Left;
  Edit8.Height := (MainForm.ClientHeight) - Image1.Height;
  Edit8.Width := MainForm.Width;
  Edit8.Top := Image1.Top + Image1.Height;
  Edit8.Left := Image2.Left;
  case GameOptions[8] of
    0:
    begin
      Memo11.Height := Edit8.Height;
      Memo11.Width := $67;
      Memo11.Top := $2D;
      Memo11.Left := (Image2.Left + ((Image2.Width) div 2)) - ((Memo11.Width) div 2);
      Memo1.Height := $14;
      Memo1.Width := $4C;
      Memo1.Top := $4E;
      Memo1.Left := (Memo11.Left + Memo11.Width) - Memo1.Width;
      Memo9.Height := Memo1.Height;
      Memo9.Width := $44;
      Memo9.Top := $40;
      Memo9.Left := Image3.Left + 9;
      Memo10.Height := Memo1.Height;
      Memo10.Width := Memo9.Width;
      Memo10.Top := $70;
      Memo10.Left := Memo9.Left;
      Memo8.Height := Memo1.Height;
      Memo8.Width := $67;
      Memo8.Top := $10C;
      Memo8.Left := Image3.Left + 9;
      Memo5.Height := Memo1.Height;
      Memo5.Top := Memo8.Top + Memo8.Height;
      Memo5.Left := Image3.Left + $2A;
      Memo5.Width := (Memo8.Left + Memo8.Width) - Memo5.Left;
      Edit13.Height := $14;
      Edit13.Width := $72;
      Edit13.Top := $50;
      Edit13.Left := $B5;
      Edit14.Height := Edit13.Height;
      Edit14.Width := $13E;
      Panel2.Height := $28;
      Panel2.Width := $B8;
    end;
    1:
    begin
      Memo11.Height := Edit8.Height;
      Memo11.Width := $81;
      Memo11.Top := $38;
      Memo11.Left := (Image2.Left + ((Image2.Width) div 2)) - ((Memo11.Width) div 2);
      Memo1.Height := $19;
      Memo1.Width := $5F;
      Memo1.Top := $62;
      Memo1.Left := (Memo11.Left + Memo11.Width) - Memo1.Width;
      Memo9.Height := Memo1.Height;
      Memo9.Width := $55;
      Memo9.Top := $50;
      Memo9.Left := Image3.Left + $B;
      Memo10.Height := Memo1.Height;
      Memo10.Width := Memo9.Width;
      Memo10.Top := $8C;
      Memo10.Left := Memo9.Left;
      Memo8.Height := Memo1.Height;
      Memo8.Width := $81;
      Memo8.Top := $14F;
      Memo8.Left := Image3.Left + $B;
      Memo5.Height := Memo1.Height;
      Memo5.Top := Memo8.Top + Memo8.Height;
      Memo5.Left := Image3.Left + $35;
      Memo5.Width := (Memo8.Left + Memo8.Width) - Memo5.Left;
      Edit13.Height := $19;
      Edit13.Width := $8F;
      Edit13.Top := 100;
      Edit13.Left := $E2;
      Edit14.Height := Edit13.Height;
      Edit14.Width := $18E;
      Panel2.Height := $32;
      Panel2.Width := $E6;
    end;
  end;
  Panel2.Top := (((Self.ClientHeight) - Edit8.Height) - Panel2.Height) - 4;
  Panel2.Left := ((Self.ClientWidth) - Panel2.Width) - 4;
  Image34.Height := Panel2.Height - 4;
  Image34.Width := Panel2.Width - 4;
  Image34.Top := (((Panel2.Height - Image34.Height)) div 2);
  Image34.Left := (((Panel2.Width - Image34.Width)) div 2);
  Memo2.Height := Memo1.Height;
  Memo2.Width := Memo1.Width;
  Memo2.Top := Memo1.Top + Memo11.Height;
  Memo2.Left := Memo1.Left;
  Memo3.Height := Memo1.Height;
  Memo3.Width := Memo1.Width;
  Memo3.Top := Memo2.Top + Memo11.Height;
  Memo3.Left := Memo1.Left;
  Memo4.Height := Memo1.Height;
  Memo4.Width := Memo1.Width;
  Memo4.Top := Memo3.Top + Memo11.Height;
  Memo4.Left := Memo1.Left;
  Memo6.Height := Memo1.Height;
  Memo6.Width := Memo5.Width;
  Memo6.Top := Memo5.Top + Memo5.Height;
  Memo6.Left := Memo5.Left;
  Memo7.Height := Memo1.Height;
  Memo7.Width := Memo5.Width;
  Memo7.Top := Memo6.Top + Memo6.Height;
  Memo7.Left := Memo6.Left;
  Edit14.Top := Edit13.Top + Edit13.Height;
  Edit14.Left := Edit13.Left;
  Edit15.Height := Edit13.Height;
  Edit15.Width := Edit13.Width;
  Edit15.Top := Edit14.Top + Edit14.Height;
  Edit15.Left := Edit13.Left;
  Edit16.Height := Edit13.Height;
  Edit16.Width := Edit14.Width;
  Edit16.Top := Edit15.Top + Edit15.Height;
  Edit16.Left := Edit13.Left;
  Edit17.Height := Edit13.Height;
  Edit17.Width := Edit13.Width;
  Edit17.Top := Edit16.Top + Edit16.Height;
  Edit17.Left := Edit13.Left;
  Edit18.Height := Edit13.Height;
  Edit18.Width := Edit14.Width;
  Edit18.Top := Edit17.Top + Edit17.Height;
  Edit18.Left := Edit13.Left;
  Edit19.Height := Edit13.Height;
  Edit19.Width := Edit13.Width;
  Edit19.Top := Edit18.Top + Edit18.Height;
  Edit19.Left := Edit13.Left;
  Edit20.Height := Edit13.Height;
  Edit20.Width := Edit14.Width;
  Edit20.Top := Edit19.Top + Edit19.Height;
  Edit20.Left := Edit13.Left;
  Edit21.Height := Edit13.Height;
  Edit21.Width := Edit13.Width;
  Edit21.Top := Edit20.Top + Edit20.Height;
  Edit21.Left := Edit13.Left;
  Edit22.Height := Edit13.Height;
  Edit22.Width := Edit14.Width;
  Edit22.Top := Edit21.Top + Edit21.Height;
  Edit22.Left := Edit13.Left;
  Edit23.Height := Edit13.Height;
  Edit23.Width := Edit13.Width;
  Edit23.Top := Edit22.Top + Edit22.Height;
  Edit23.Left := Edit13.Left;
  Edit24.Height := Edit13.Height;
  Edit24.Width := Edit14.Width;
  Edit24.Top := Edit23.Top + Edit23.Height;
  Edit24.Left := Edit13.Left;
  Edit25.Height := Edit13.Height;
  Edit25.Width := Edit13.Width;
  Edit25.Top := Edit24.Top + Edit24.Height;
  Edit25.Left := Edit13.Left;
  Edit26.Height := Edit13.Height;
  Edit26.Width := Edit14.Width;
  Edit26.Top := Edit25.Top + Edit25.Height;
  Edit26.Left := Edit13.Left;
  Edit27.Height := Edit13.Height;
  Edit27.Width := Edit14.Width - Edit13.Width;
  Edit27.Top := Edit13.Top;
  Edit27.Left := Edit13.Left + Edit13.Width;
  Edit28.Height := Edit13.Height;
  Edit28.Width := Edit14.Width - Edit13.Width;
  Edit28.Top := Edit15.Top;
  Edit28.Left := Edit15.Left + Edit15.Width;
  Edit29.Height := Edit13.Height;
  Edit29.Width := Edit14.Width - Edit13.Width;
  Edit29.Top := Edit17.Top;
  Edit29.Left := Edit17.Left + Edit17.Width;
  Edit30.Height := Edit13.Height;
  Edit30.Width := Edit14.Width - Edit13.Width;
  Edit30.Top := Edit19.Top;
  Edit30.Left := Edit19.Left + Edit19.Width;
  Edit31.Height := Edit13.Height;
  Edit31.Width := Edit14.Width - Edit13.Width;
  Edit31.Top := Edit21.Top;
  Edit31.Left := Edit21.Left + Edit21.Width;
  Edit32.Height := Edit13.Height;
  Edit32.Width := Edit14.Width - Edit13.Width;
  Edit32.Top := Edit23.Top;
  Edit32.Left := Edit23.Left + Edit23.Width;
  Edit33.Height := Edit13.Height;
  Edit33.Width := Edit14.Width - Edit13.Width;
  Edit33.Top := Edit25.Top;
  Edit33.Left := Edit25.Left + Edit25.Width;
  case GameOptions[8] of
    0:
    begin
      RichEdit1.Height := 200;
      RichEdit1.Width := $17E;
      RichEdit1.Top := $2D;
      RichEdit1.Left := $81;
    end;
    1:
    begin
      RichEdit1.Height := $FA;
      RichEdit1.Width := $1DE;
      RichEdit1.Top := $38;
      RichEdit1.Left := $A1;
    end;
  end;
  Image1.Visible := False;
  Image2.Visible := False;
  Image3.Visible := False;
  Image1.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\center.bmp');
  if Hero.cycle_factor_minus_one = 0 then
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\left.bmp')
  else
    Image2.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\leftr.bmp');
  if Hero.cycle_factor_minus_one = 0 then
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\right.bmp')
  else
    Image3.Picture.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\rightr.bmp');

  MapBitmap1 := TBitmap.Create;
  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image1.Width + Image2.Width + Image3.Width;
  MapBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\chtable.oz');
  MapBitmap2 := TBitmap.Create;
  MapBitmap2.Width := Image6.Width;
  MapBitmap2.Height := Image6.Height;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  ImageList1.Width := Image6.Width;
  ImageList1.Height := Image6.Height;
  for Row := 0 to 19 do
    for Column := 0 to 10 do
      if (Row <= 18) or ((Row = 19) and (Column < 9)) then
      begin
        SourceRect :=
            Rect(
                Image6.Width * Column,
                Image6.Height * Row,
                (Column + 1) * Image6.Width,
                (Row + 1) * Image6.Height
            );
        MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
        ImageList1.Add(MapBitmap2, nil);
      end;

  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image6.Width * 15;
  MapBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\chtableb.oz');
  ImageList3.Width := Image6.Width;
  ImageList3.Height := Image6.Height;
  { A fresh bitmap supplies the ending sprite atlas. }
  MapBitmap2 := TBitmap.Create;
  MapBitmap2.Width := Image6.Width;
  MapBitmap2.Height := Image6.Height;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  for Row := 0 to 14 do
    for Column := 0 to 10 do
      if (Row <= 13) or ((Row = 14) and (Column <= 4)) then
      begin
        SourceRect :=
            Rect(
                Image6.Width * Column,
                Image6.Height * Row,
                (Column + 1) * Image6.Width,
                (Row + 1) * Image6.Height
            );
        MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
        ImageList3.Add(MapBitmap2, nil);
      end;

  MapBitmap1.Free;
  MapBitmap1 := TBitmap.Create;
  MapBitmap1.Height := Image6.Height;
  MapBitmap1.Width := Image6.Width;
  MapBitmap1.LoadFromFile(Memo12.Lines[1] + DataDirectory + '\key.oz');
  ImageList2.Width := Image6.Width div 2;
  ImageList2.Height := Image6.Height div 2;
  MapBitmap2.Width := Image6.Width div 2;
  MapBitmap2.Height := Image6.Height div 2;
  MapBitmap2.Canvas.CopyMode := $CC0020;
  TargetRect := Rect(0, 0, MapBitmap2.Width, MapBitmap2.Height);
  for Row := 0 to 1 do
    for Column := 0 to 1 do
    begin
      SourceRect :=
          Rect(
              MapBitmap2.Width * Column,
              MapBitmap2.Height * Row,
              (Column + 1) * MapBitmap2.Width,
              (Row + 1) * MapBitmap2.Height
          );
      MapBitmap2.Canvas.CopyRect(TargetRect, MapBitmap1.Canvas, SourceRect);
      ImageList2.Add(MapBitmap2, nil);
    end;

  MapBitmap1.Height := Image6.Height * 11;
  MapBitmap1.Width := Image6.Width * 11;
  MapBitmap2.Height := MapBitmap1.Height;
  MapBitmap2.Width := MapBitmap1.Width;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap1.Height := Image6.Height * 5;
  WorkBitmap1.Width := Image6.Width * 3;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap2.Height := Image6.Height * 2;
  WorkBitmap2.Width := Image6.Width * 3;
  WorkBitmap3 := TBitmap.Create;
  WorkBitmap3.Height := Image6.Height;
  WorkBitmap3.Width := Image6.Width;
  FrameBitmap := TBitmap.Create;
  FrameBitmap.Width := Image1.Width + Image2.Width + Image3.Width;
  FrameBitmap.Height := Image1.Height;
  {$I GraphicsHints.inc}
  Memo11.Font.Color := $FFFFFF;
  DrawFlag1 := 0;
  DrawFlag2 := 0;
end;

procedure TTSW10.mhyouji; { $00442C38 }
var
  I: Longint;
begin
  Hero.Word664 := 0;
  for I := 1 to 121 do
  begin
    DrawIndex := I;
    DrawX := (RenderOrder[DrawIndex - 1] * Image6.Width) mod (Image6.Width * 11);
    DrawY :=
        ((RenderOrder[DrawIndex - 1] * Image6.Height) div (Image6.Height * 11)) * Image6.Height;
    ImageList1.Draw(
        MapBitmap1.Canvas,
        DrawX,
        DrawY,
        Maps[Hero.floor, RenderOrder[DrawIndex - 1] + 2] - 1
    );
    GraphicTile := Maps[Hero.floor, RenderOrder[DrawIndex - 1] + 2];
    imagework;
    ImageList1.Draw(
        MapBitmap2.Canvas,
        DrawX,
        DrawY,
        Maps[Hero.floor, RenderOrder[DrawIndex - 1] + 2] - 1 + DoorOpened
    );
  end;
end;

procedure TTSW10.yusyahyouji; { $00443648 }
begin
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap1.Free;
  WorkBitmap2.Free;
  WorkBitmap3.Free;
  WorkBitmap1 := TBitmap.Create;
  WorkBitmap2 := TBitmap.Create;
  WorkBitmap3 := TBitmap.Create;
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap1.Canvas.CopyMode := $CC0020;
  WorkBitmap2.Canvas.CopyMode := $CC0020;
  WorkBitmap3.Canvas.CopyMode := $CC0020;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2] - 1);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex - $42);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex + 1 - $42);
  SourceRect := TargetRect;
  kasanegaki;
end;

procedure TTSW10.kasanegaki; { $0044439C }
begin
  { OR the sprite into its mask, invert the mask, then combine it with the
    destination using OR and AND. Copy modes must be restored for later blits. }
  WorkBitmap2.Canvas.CopyMode := $EE0086;
  WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap3.Canvas.CopyMode := $330008;
  WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $EE0086;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $8800C6;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $CC0020;
  WorkBitmap2.Canvas.CopyMode := $CC0020;
  WorkBitmap3.Canvas.CopyMode := $CC0020;
end;

procedure TTSW10.yusyahyouji1; { $004433A4 }
begin
  { Each facing retains its original two-frame drawing block. }
  case Hero.facing of
    1:
    begin
      NeighborIndex := Image6.Width * Hero.x;
      NeighborY := Image6.Height * Hero.y;
      ScratchIndex := 250;
      DoorOpened := 1;
      yusyahyouji;
      MapBitmap2.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
      ScratchIndex := 252;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
    end;
    2:
    begin
      NeighborIndex := Image6.Width * Hero.x;
      NeighborY := Image6.Height * Hero.y;
      ScratchIndex := 258;
      DoorOpened := 1;
      yusyahyouji;
      MapBitmap2.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
      ScratchIndex := 260;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
    end;
    3:
    begin
      NeighborIndex := Image6.Width * Hero.x;
      NeighborY := Image6.Height * Hero.y;
      ScratchIndex := 266;
      DoorOpened := 1;
      yusyahyouji;
      MapBitmap2.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
      ScratchIndex := 268;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
    end;
    4:
    begin
      NeighborIndex := Image6.Width * Hero.x;
      NeighborY := Image6.Height * Hero.y;
      ScratchIndex := 274;
      DoorOpened := 1;
      yusyahyouji;
      MapBitmap2.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
      ScratchIndex := 276;
      DoorOpened := 0;
      yusyahyouji;
      MapBitmap1.Canvas.Draw(NeighborIndex, NeighborY, WorkBitmap1);
    end;
  end;
end;
