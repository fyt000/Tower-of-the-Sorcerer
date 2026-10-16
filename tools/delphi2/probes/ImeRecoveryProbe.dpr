library ImeRecoveryProbe;

{ PE bytes are read in Unicorn only. Never load this DLL into a native process. }
{$O+,R-,Q-,S-}

uses RecoveredIme;

exports
  RecoveredEnableIme,
  RecoveredSetImeStatus;

begin
end.
