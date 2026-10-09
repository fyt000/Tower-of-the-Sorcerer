program StartupIOSmoke;
{$APPTYPE CONSOLE}
uses Windows, SysUtils, Classes, Forms, OriginalForms, OriginalState;
{$R ..\OriginalResources.res}

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then raise Exception.Create(Message);
end;

function IMin(A, B: Integer): Integer;
begin
  if A < B then Result := A else Result := B;
end;

procedure Run;
var
  Form: TTSW10;
  Lines: TStringList;
  Directory, Path, Text: string;
  NameBuffer: string[255];
  ShortName: string[10];
  Expected: array[0..9] of Byte;
  Input: file;
  I, N, LineIndex, TotalNameBytes: Integer;
  Failed: Boolean;
begin
  Require(ParamCount = 1, 'StartupIOSmoke requires an isolated fixture directory');
  Directory := ParamStr(1);
  Require((GetFileAttributes(PChar(Directory)) <> $FFFFFFFF) and
    ((GetFileAttributes(PChar(Directory)) and FILE_ATTRIBUTE_DIRECTORY) <> 0),
    'Startup fixture directory missing');
  Application.Initialize;
  Form := TTSW10.Create(nil);
  Lines := TStringList.Create;
  try
    Require(not Form.Visible, 'Startup boundary form must stay hidden');
    for N := 0 to 6 do
    begin
      case N of
        0: I := 0;
        1: I := 4;
        2: I := 10;
        3: I := 11;
        4: I := 255;
        5: I := 256;
      else I := 300; end;
      SetLength(Text, I);
      if I > 0 then FillChar(Text[1], I, Ord('A'));
      Lines.Clear;
      Lines.Add('X:\saves');
      Lines.Add('X:\original');
      Lines.Add(Text);
      Path := Directory + '\input.ini';
      Lines.SaveToFile(Path);
      Form.Memo12.Lines.Clear;
      Form.Memo12.Lines.LoadFromFile(Path);
      Require(Form.Memo12.Lines[0] = Lines[0], 'Memo save directory');
      Require(Form.Memo12.Lines[1] = Lines[1], 'Memo asset directory');
      { A native memo enumerates physical lines. Retain actual wrapping as
        observer input; never assume one file line is one memo line. }
      Require(Form.Memo12.Lines[2] = Copy(Text, 1, Length(Form.Memo12.Lines[2])),
        'Memo player-name prefix');
      if I <= 11 then Require(Form.Memo12.Lines[2] = Text, 'Short memo name line');
      Require(Form.Memo12.Lines[Form.Memo12.Lines.Count] = '', 'Absent memo line must be empty');
      FillChar(ShortName, SizeOf(ShortName), $A5);
      NameBuffer := Form.Memo12.Lines[2];
      ShortName := NameBuffer;
      Require(Length(ShortName) = IMin(I, 10), 'Ten-byte name truncation');
      Write('{"native_memo_name_bytes":', I, ',"short_name_bytes":', Length(ShortName),
        ',"physical_line_lengths":[');
      TotalNameBytes := 0;
      for LineIndex := 0 to Form.Memo12.Lines.Count - 1 do
      begin
        if LineIndex >= 2 then
        begin
          Require(Form.Memo12.Lines[LineIndex] = Copy(Text, 1,
            Length(Form.Memo12.Lines[LineIndex])), 'Wrapped name line content');
          Inc(TotalNameBytes, Length(Form.Memo12.Lines[LineIndex]));
        end;
        if LineIndex > 0 then Write(',');
        Write(Length(Form.Memo12.Lines[LineIndex]));
      end;
      Require(TotalNameBytes = I, 'Wrapped name preserves every input byte');
      WriteLn('],"passed":true}');
    end;
    Form.Memo12.Lines.Clear;
    Form.Memo12.Lines.Add('X:\original\savedat');
    Form.Memo12.Lines.Add('X:\original');
    Form.Memo12.Lines.Add('');
    Path := Directory + '\fallback.ini';
    Form.Memo12.Lines.SaveToFile(Path);
    Lines.LoadFromFile(Path);
    Require((Lines.Count = 3) and (Lines[0] = 'X:\original\savedat') and
      (Lines[1] = 'X:\original') and (Lines[2] = ''), 'Fallback memo roundtrip');
    Failed := False;
    try Form.Memo12.Lines.LoadFromFile(Directory + '\missing.ini');
    except on E: EFOpenError do Failed := True; end;
    Require(Failed, 'Missing INI must fail');
    Failed := False;
    try Form.Memo12.Lines.SaveToFile(Directory + '\nonexistent\failed.ini');
    except on E: EFCreateError do Failed := True; end;
    Require(Failed, 'Missing save directory must fail');
    for I := 0 to 9 do Expected[I] := I * 17;
    Path := Directory + '\option.dat';
    AssignFile(Input, Path);
    Rewrite(Input, 1);
    BlockWrite(Input, Expected, 10);
    CloseFile(Input);
    AssignFile(SettingsFile, Path);
    Reset(SettingsFile, 1);
    FillChar(OriginalOptions, SizeOf(OriginalOptions), $A5);
    BlockRead(SettingsFile, OriginalOptions, 10);
    CloseFile(SettingsFile);
    for I := 0 to 9 do Require(OriginalOptions[I] = Expected[I], 'Option byte read');
    AssignFile(Input, Path);
    Rewrite(Input, 1);
    BlockWrite(Input, Expected, 3);
    CloseFile(Input);
    AssignFile(SettingsFile, Path);
    Reset(SettingsFile, 1);
    FillChar(OriginalOptions, SizeOf(OriginalOptions), $A5);
    Failed := False;
    try BlockRead(SettingsFile, OriginalOptions, 10);
    except on E: EInOutError do Failed := E.ErrorCode = 100; end;
    CloseFile(SettingsFile);
    Require(Failed, 'Short option record must raise error 100');
    for I := 0 to 2 do Require(OriginalOptions[I] = Expected[I], 'Short option read bytes');
    for I := 3 to 9 do Require(OriginalOptions[I] = $A5, 'Short read preserves unread bytes');
    Require(not Form.Visible, 'Startup boundary form became visible');
    WriteLn('{"native_startup_io_boundary_passed":true,"native_activation_executed":false}');
  finally
    Lines.Free;
    Form.Free;
  end;
end;

begin
  try Run;
  except
    on E: Exception do
    begin WriteLn('Startup I/O boundary failed: ', E.Message); Halt(1); end;
  end;
end.
