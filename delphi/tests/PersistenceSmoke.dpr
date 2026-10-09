program PersistenceSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  GameState,
  Persistence;

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then
    raise Exception.Create(Message);
end;

procedure Run;
var
  ExpectedHero, BeforeHero: THeroState;
  ExpectedMaps: TFloorMaps;
  Rows, ExpectedRows: TRankingTable;
  Names, ExpectedNames: TRankingNames;
  Stream: TFileStream;
  Lines: TStringList;
  I, J: Integer;
  Value: Byte;
  Failed: Boolean;
  Path: string;
begin
  Require(ParamCount = 2, 'PersistenceSmoke requires fixture directory and assets');
  SaveDirectory := ParamStr(1);
  FillChar(Hero, SizeOf(Hero), 0);
  FillChar(Maps, SizeOf(Maps), 0);
  Hero.hp := MaxInt;
  Hero.attack := 250;
  Hero.defense := 320;
  Hero.floor := 49;
  Hero.x := 6;
  Hero.y := 10;
  Hero.Word628 := -4;
  Hero.save_version := 12;
  Hero.Word380 := -12345;
  Hero.cycle_factor_minus_one := 0;
  for I := 0 to 50 do
    for J := 0 to 122 do
      Maps[I, J] := (I * 123 + J) mod 168;
  WriteSave(SaveSlotPath(3), False);
  ExpectedHero := Hero;
  ExpectedMaps := Maps;
  Require(SaveChecksumsValid(Hero), 'Wrapped signed checksum');
  Stream := TFileStream.Create(SaveSlotPath(3), fmOpenRead);
  try
    Require(Stream.Size = 6957, 'save byte length');
  finally
    Stream.Free;
  end;
  FillChar(Hero, SizeOf(Hero), 0);
  FillChar(Maps, SizeOf(Maps), 0);
  ReadSave(SaveSlotPath(3), False);
  Require(
      (Hero.hp = ExpectedHero.hp) and (Hero.Word380 = -12345) and (Hero.save_version = 12),
      'Unknown hero words survive round trip'
  );
  for I := 0 to 50 do
    for J := 0 to 122 do
      Require(Maps[I, J] = ExpectedMaps[I, J], 'Raw map round trip');
  BeforeHero := Hero;
  Stream := TFileStream.Create(SaveSlotPath(3), fmOpenReadWrite);
  try
    Stream.Position := SizeOf(Maps);
    Value := 0;
    Stream.WriteBuffer(Value, 1);
  finally
    Stream.Free;
  end;
  Failed := False;
  try
    ReadSave(SaveSlotPath(3), False);
  except
    on E: Exception do
      Failed := True;
  end;
  Require(Failed and (Hero.hp = BeforeHero.hp), 'Corrupt slot must preserve live hero');
  Hero.Word656 := 1;
  Hero.Word660 := 2;
  WriteSave(SaveSlotPath(0), True);
  Hero.hp := 1;
  ReadSave(SaveSlotPath(0), True);
  Require(
      (Hero.hp = BeforeHero.hp) and (Hero.Word656 = 1) and (Hero.Word660 = 2),
      'fairy checkpoint bypasses stale checksums'
  );
  Stream := TFileStream.Create(SaveSlotPath(8), fmCreate);
  try
    Stream.WriteBuffer(Value, 1);
  finally
    Stream.Free;
  end;
  Failed := False;
  try
    ReadSave(SaveSlotPath(8), True);
  except
    on E: Exception do
      Failed := True;
  end;
  Require(Failed and (Hero.hp = BeforeHero.hp), 'Truncated checkpoint is rejected transactionally');
  for I := 1 to 5 do
  begin
    DefaultRanking(I, -4, ExpectedRows, ExpectedNames);
    Path := ParamStr(2) + '\savedat\option' + IntToStr(I) + '.dat';
    Stream := TFileStream.Create(Path, fmOpenRead);
    try
      Require(Stream.Size = 288, 'ranking byte length');
      Stream.ReadBuffer(Rows, SizeOf(Rows));
    finally
      Stream.Free;
    end;
    for J := 0 to 71 do
      Require(
          PLongint(Longint(@Rows) + J * 4)^ = PLongint(Longint(@ExpectedRows) + J * 4)^,
          'ranking matches shipped bytes'
      );
    Names := ExpectedNames;
    Names[0] := 'Delphi 2';
    Rows[0, 0] := 200;
    WriteRanking(I, -4, Rows, Names);
    Require(ReadRanking(I, -4, Rows, Names), 'ranking checksum round trip');
    Require((Rows[0, 0] = 200) and (Names[0] = 'Delphi 2'), 'Ranking numbers and names round trip');
    Lines := TStringList.Create;
    try
      Lines.Add('Incomplete names');
      Lines.SaveToFile(SaveDataPath('option' + IntToStr(I) + '1.dat'));
    finally
      Lines.Free;
    end;
    Require(not ReadRanking(I, -4, Rows, Names), 'Malformed ranking names are rejected');
    for J := 0 to 71 do
      Require(
          PLongint(Longint(@Rows) + J * 4)^ = PLongint(Longint(@ExpectedRows) + J * 4)^,
          'Malformed names restore complete default ranking'
      );
    for J := 0 to 9 do
      Require(Names[J] = ExpectedNames[J], 'Malformed names restore default name list');
    Rows[2, 3] := Rows[2, 3] + 1;
    Require(not RankingChecksumsValid(I, -4, Rows), 'Ranking row corruption is rejected');
    Rows := ExpectedRows;
    Require(not RankingChecksumsValid(I, -3, Rows), 'Ranking version mismatch is rejected');
  end;
  Writeln('{"persistence":"passed","save_bytes":6957,"ranking_categories":5}');
end;

begin
  try
    Run;
  except
    on E: Exception do
    begin
      Writeln(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
