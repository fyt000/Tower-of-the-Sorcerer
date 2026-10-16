library RecoveryProbe;

{$O+,R-,Q-,S-}

uses RecoveredNeighbor;

exports ClassifyNeighbor;

begin
  { Loaded only as PE bytes by the emulator; the exported routine uses
    original absolute game addresses and must not be called natively. }
end.
