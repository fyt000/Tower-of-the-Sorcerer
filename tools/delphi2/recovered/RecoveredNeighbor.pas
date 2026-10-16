unit RecoveredNeighbor;

{ Reconstructed from the pinned TSW.exe entry $00451C20 and its assembly.
  This is a candidate Pascal representation, not the author's source file.
  Absolute variables deliberately reproduce original memory addresses for
  isolated emulator comparisons. Do not call this unit in a native process. }

{$O+,R-,Q-,S-}

interface

type
  TOriginalFloor = array[0..122] of Byte;
  TOriginalMaps = array[0..50] of TOriginalFloor;

var
  Floor: Longint absolute $004B8698;
  Maps: TOriginalMaps absolute $004B8934;
  NeighborIndex: Longint absolute $0048C55C;
  TileClass: Longint absolute $0048C58C;
  MonsterIndex: Longint absolute $0048C5B8;

procedure ClassifyNeighbor;

implementation

procedure ClassifyNeighbor;
begin
  TileClass := 0;
  case Maps[Floor][NeighborIndex + 2] of
    8: TileClass := 1;
    61..90, 93..96, 133..144, 147..158:
      begin
        TileClass := 2;
        case Maps[Floor][NeighborIndex + 2] of
          61..96: MonsterIndex := (Maps[Floor][NeighborIndex + 2] - 61) div 2;
          97..114: MonsterIndex := 18;
          115..132: MonsterIndex := 19;
          133..158: MonsterIndex := (Maps[Floor][NeighborIndex + 2] - 133) div 2 + 20;
        end;
      end;
    13: TileClass := 3;
  end;
end;

end.
