unit Audio;

{ Track IDs 5..21 select MIDI files; zero disables background music. }
interface
var
  EffectRequests, AudioFailures: Longint;
  LastEffect: Integer;
function MusicFileName(Track: Integer): string;
function MusicTrackForFloor(Floor: Integer): Integer;

implementation

function MusicFileName(Track: Integer): string;
begin
  Result := '';
  case Track of
    5: Result := 'b_067xgw.mid';
    6: Result := 'b_058xgw.mid';
    7: Result := 'a_008xgw.mid';
    8: Result := 'a_118xgw.mid';
    9: Result := 'a_019xgw.mid';
    10: Result := 'b_018xgw.mid';
    11: Result := 'a_050xgw.mid';
    12: Result := 'a_085xgw.mid';
    13: Result := 'a_032xgw.mid';
    14: Result := 'a_046xgw.mid';
    15: Result := 'a_005xgw.mid';
    16: Result := 'a_007xgw.mid';
    17: Result := 'b_110xgw.mid';
    18: Result := 'a_023xgw.mid';
    19: Result := 'b_117xgw.mid';
    20: Result := 'b_014xgw.mid';
    21: Result := 'A_027xgw.mid';
  end;
end;

function MusicTrackForFloor(Floor: Integer): Integer;
begin
  { Zero leaves the current track unchanged for an unmapped floor. }
  Result := 0;
  if Floor = 0 then
    Result := 21
  else if (Floor >= 1) and (Floor <= 10) then
    Result := 5
  else if (Floor >= 11) and (Floor <= 20) then
    Result := 6
  else if (Floor >= 21) and (Floor <= 30) then
    Result := 17
  else if (Floor >= 31) and (Floor <= 40) then
    Result := 8
  else if (Floor >= 41) and (Floor <= 49) then
    Result := 9
  else if Floor = 50 then
    Result := 10;
end;

end.
