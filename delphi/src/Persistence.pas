unit Persistence;

{ Save layout: 6273 map bytes (51 * 123), then 684 hero bytes
  (171 little-endian Longints), for a total of 6957 bytes. }
{$A+,R-,Q-}
interface
uses
  SysUtils,
  Classes,
  FileCtrl,
  GameState;

type
  { Rows 0..9: score, HP, attack, defense, sum, alternating sum.
    Rows 10 and 11: column sums and alternating column sums.
    The final word holds the version/category marker. Names are saved
    separately as ten text lines. The binary table is exactly 288 bytes. }
  TRankingTable = array[0..11, 0..5] of Longint;
  TRankingNames = array[0..9] of string;
  ESaveError = class(Exception);

function SaveSlotPath(Slot: Integer): string;
function SaveDataPath(const Name: string): string;
procedure WriteSave(const Path: string; Checkpoint: Boolean);
procedure ReadSave(const Path: string; Checkpoint: Boolean);
procedure WriteSaveRecords(
    const Path: string;
    const SavedMaps: TFloorMaps;
    const SavedHero: THeroState
);
procedure ReadSaveRecords(
    const Path: string;
    Checkpoint: Boolean;
    var SavedMaps: TFloorMaps;
    var SavedHero: THeroState
);
procedure SaveChecksums(var SavedHero: THeroState);
function SaveChecksumsValid(const SavedHero: THeroState): Boolean;
procedure DefaultRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    var Names: TRankingNames
);
procedure RankingChecksums(Category: Integer; Version: Longint; var Ranking: TRankingTable);
function RankingChecksumsValid(
    Category: Integer;
    Version: Longint;
    const Ranking: TRankingTable
): Boolean;
procedure WriteRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    const Names: TRankingNames
);
function ReadRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    var Names: TRankingNames
): Boolean;

implementation
uses
  Windows;

type
  THeroWords = array[0..170] of Longint;
  PHeroWords = ^THeroWords;

const
  DefaultNames: array[1..5, 0..9] of string[20] = (
      (
          'Skeleton A',
          'Priest',
          'Skeleton B',
          'Gate-Keeper C',
          'Skeleton C',
          'Bat',
          'Red Slime',
          'Green Slime',
          'Iron Sword',
          'Iron Shield'
      ),
      (
          'Vampire',
          'Superion Priest',
          'Zombie Knight',
          'Gate-Keeper B',
          'Rock',
          'Big Octopus',
          'Zombie',
          'Big Bat',
          'Big Slime',
          'Blue Crystal'
      ),
      (
          'Magic Master',
          'Thief',
          'Fairy',
          'Merchant',
          'Princess',
          'Old Man',
          'Brave Man',
          'Mattock',
          'Cross',
          'Lucky Gold'
      ),
      (
          'Golden Knight',
          'Knight',
          'Fancer',
          'Soldier',
          'Ghost Soldier',
          'Dragon',
          'Swordsman',
          'Slime Man',
          'Sword of Knight',
          'Shield of Knight'
      ),
      (
          'Zeno',
          'Magician A',
          'Black Knight',
          'Magic Sergeant',
          'Gate-Keeper A',
          'Bloodsucker Bat',
          'Magician B',
          'King Slime',
          'Holy Sword',
          'Holy Shield'
      )
  );

function SaveDataPath(const Name: string): string;
begin
  if SaveDirectory = '' then
    SaveDirectory := GetCurrentDir + '\savedat';
  Result := SaveDirectory + '\' + Name;
end;

function SaveSlotPath(Slot: Integer): string;
begin
  Result := SaveDataPath('save' + IntToStr(Slot) + '.dat');
end;

procedure EnsureSaveDirectory;
begin
  if not DirectoryExists(SaveDirectory) then
    if not CreateDir(SaveDirectory) then
      raise ESaveError.Create('Cannot create save directory: ' + SaveDirectory);
end;

procedure HeroSums(const SavedHero: THeroState; var Sum, Alternating: Longint);
var
  I: Integer;
  Words: PHeroWords;
begin
  Sum := 0;
  Alternating := 0;
  Words := PHeroWords(@SavedHero);
  { Exclude the checksum words at offsets 656 and 660. Arithmetic wraps
    at 32 bits with overflow checking disabled by Q-. }
  for I := 0 to 163 do
  begin
    Inc(Sum, Words^[I]);
    if I mod 2 = 0 then
      Inc(Alternating, Words^[I])
    else
      Dec(Alternating, Words^[I]);
  end;
end;

procedure SaveChecksums(var SavedHero: THeroState);
begin
  HeroSums(SavedHero, SavedHero.Word656, SavedHero.Word660);
end;

function SaveChecksumsValid(const SavedHero: THeroState): Boolean;
var
  Sum, Alternating: Longint;
begin
  HeroSums(SavedHero, Sum, Alternating);
  Result :=
      (SavedHero.Word628 = -4) and (SavedHero.Word656 = Sum) and (SavedHero.Word660 = Alternating);
end;

procedure ReadSaveRecords(
    const Path: string;
    Checkpoint: Boolean;
    var SavedMaps: TFloorMaps;
    var SavedHero: THeroState
);
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(Path, fmOpenRead or fmShareDenyWrite);
  try
    if Stream.Size <> SizeOf(SavedMaps) + SizeOf(SavedHero) then
      raise ESaveError.Create('Save must contain exactly 6957 bytes.');
    Stream.ReadBuffer(SavedMaps, SizeOf(SavedMaps));
    Stream.ReadBuffer(SavedHero, SizeOf(SavedHero));
  finally
    Stream.Free;
  end;
  if not Checkpoint and not SaveChecksumsValid(SavedHero) then
    raise ESaveError.Create('Do not use this save data: checksum mismatch.');
  if (SavedHero.floor < 0)
      or (SavedHero.floor > 50)
      or (SavedHero.x < 0)
      or (SavedHero.x > 10)
      or (SavedHero.y < 0)
      or (SavedHero.y > 10) then
    raise ESaveError.Create('Save data contains an invalid hero position.');
end;

procedure WriteSaveRecords(
    const Path: string;
    const SavedMaps: TFloorMaps;
    const SavedHero: THeroState
);
var
  Stream: TFileStream;
begin
  EnsureSaveDirectory;
  Stream := TFileStream.Create(Path, fmCreate);
  try
    Stream.WriteBuffer(SavedMaps, SizeOf(SavedMaps));
    Stream.WriteBuffer(SavedHero, SizeOf(SavedHero));
  finally
    Stream.Free;
  end;
end;

procedure WriteSave(const Path: string; Checkpoint: Boolean);
begin
  { Fairy checkpoints store the raw hero record, including stale checksums. }
  if not Checkpoint then
    SaveChecksums(Hero);
  WriteSaveRecords(Path, Maps, Hero);
end;

procedure ReadSave(const Path: string; Checkpoint: Boolean);
var
  SavedMaps: TFloorMaps;
  SavedHero: THeroState;
begin
  { Commit only after the complete record passes validation. }
  ReadSaveRecords(Path, Checkpoint, SavedMaps, SavedHero);
  Maps := SavedMaps;
  Hero := SavedHero;
end;

procedure RankingChecksums(Category: Integer; Version: Longint; var Ranking: TRankingTable);
var
  Row, Column: Integer;
begin
  for Row := 0 to 9 do
  begin
    Ranking[Row, 4] := Ranking[Row, 0] + Ranking[Row, 1] + Ranking[Row, 2] + Ranking[Row, 3];
    Ranking[Row, 5] :=
        Ranking[Row, 0] - Ranking[Row, 1] + Ranking[Row, 2] - Ranking[Row, 3] + Ranking[Row, 4];
  end;
  for Column := 0 to 5 do
  begin
    Ranking[10, Column] := 0;
    Ranking[11, Column] := 0;
    for Row := 0 to 9 do
    begin
      Inc(Ranking[10, Column], Ranking[Row, Column]);
      if Row mod 2 = 0 then
        Inc(Ranking[11, Column], Ranking[Row, Column])
      else
        Dec(Ranking[11, Column], Ranking[Row, Column]);
    end;
    { The column sum is the eleventh, positive term of this checksum. }
    Inc(Ranking[11, Column], Ranking[10, Column]);
  end;
  Ranking[11, 5] := Version * 100 - Category;
end;

function RankingChecksumsValid(
    Category: Integer;
    Version: Longint;
    const Ranking: TRankingTable
): Boolean;
var
  Expected: TRankingTable;
  Row, Column: Integer;
begin
  Expected := Ranking;
  RankingChecksums(Category, Version, Expected);
  Result := True;
  for Row := 0 to 11 do
    for Column := 0 to 5 do
      if Ranking[Row, Column] <> Expected[Row, Column] then
        Result := False;
end;

procedure DefaultRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    var Names: TRankingNames
);
var
  Row, Level: Integer;
begin
  if (Category < 1) or (Category > 5) then
    Category := 1;
  FillChar(Ranking, SizeOf(Ranking), 0);
  for Row := 0 to 9 do
  begin
    Level := 10 - Row;
    Ranking[Row, 0] := Level * 10;
    case Category of
      1:
      begin
        Ranking[Row, 1] := Level * 50;
        Ranking[Row, 2] := 15 + Level;
      end;
      2:
      begin
        Ranking[Row, 1] := Level * 100;
        Ranking[Row, 2] := Level * 5;
      end;
      3, 5:
      begin
        Ranking[Row, 1] := Level * 1000;
        Ranking[Row, 2] := Level * 50;
      end;
      4:
      begin
        Ranking[Row, 1] := Level * 500;
        Ranking[Row, 2] := 100 + Level * 10;
      end;
    end;
    Ranking[Row, 3] := Ranking[Row, 2];
    Names[Row] := DefaultNames[Category, Row];
  end;
  RankingChecksums(Category, Version, Ranking);
end;

procedure WriteRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    const Names: TRankingNames
);
var
  Stream: TFileStream;
  Lines: TStringList;
  Row: Integer;
begin
  RankingChecksums(Category, Version, Ranking);
  EnsureSaveDirectory;
  Stream := TFileStream.Create(SaveDataPath('option' + IntToStr(Category) + '.dat'), fmCreate);
  try
    Stream.WriteBuffer(Ranking, SizeOf(Ranking));
  finally
    Stream.Free;
  end;
  Lines := TStringList.Create;
  try
    for Row := 0 to 9 do
      Lines.Add(Names[Row]);
    Lines.SaveToFile(SaveDataPath('option' + IntToStr(Category) + '1.dat'));
  finally
    Lines.Free;
  end;
end;

function ReadRanking(
    Category: Integer;
    Version: Longint;
    var Ranking: TRankingTable;
    var Names: TRankingNames
): Boolean;
var
  Stream: TFileStream;
  Lines: TStringList;
  Row: Integer;
begin
  Result := False;
  DefaultRanking(Category, Version, Ranking, Names);
  try
    Stream :=
        TFileStream.Create(
            SaveDataPath('option' + IntToStr(Category) + '.dat'),
            fmOpenRead or fmShareDenyWrite
        );
    try
      if Stream.Size <> SizeOf(Ranking) then
        Exit;
      Stream.ReadBuffer(Ranking, SizeOf(Ranking));
    finally
      Stream.Free;
    end;
    if not RankingChecksumsValid(Category, Version, Ranking) then
    begin
      DefaultRanking(Category, Version, Ranking, Names);
      Exit;
    end;
    Lines := TStringList.Create;
    try
      Lines.LoadFromFile(SaveDataPath('option' + IntToStr(Category) + '1.dat'));
      if Lines.Count <> 10 then
      begin
        DefaultRanking(Category, Version, Ranking, Names);
        Exit;
      end;
      for Row := 0 to 9 do
        Names[Row] := Lines[Row];
    finally
      Lines.Free;
    end;
    Result := True;
  except
    DefaultRanking(Category, Version, Ranking, Names);
  end;
end;

end.
