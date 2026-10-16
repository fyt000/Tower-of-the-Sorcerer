unit RecoveredIme;

{ Reconstructed from pinned TSW.exe, not copied from VCL implementation source.
  Original entries: $0040EE6C and $0040EE88 (IMECtrl helpers).
  Original RTTI fixes the nine enum values. Absolute API-pointer slots mirror
  the original solely for isolated Unicorn comparisons. Never call natively. }

{$A+,Z-,O+,R-,Q-,S-}

interface

type
  TImeMode = (imDontCare, imDisable, imClose, imOpen, imHira, imKata,
    imAlpha, imSKata, imSAlpha);
  TEnableIme = function(Window: Longint; Enable: Boolean): LongBool; stdcall;
  TGetContext = function(Window: Longint): Longint; stdcall;
  TGetConversion = function(Context: Longint;
    var Conversion, Sentence: Longint): LongBool; stdcall;
  TReleaseContext = function(Window, Context: Longint): LongBool; stdcall;
  TSetOpen = function(Context: Longint; Open: Boolean): LongBool; stdcall;
  TSetConversion = function(Context, Conversion, Sentence: Longint): LongBool; stdcall;

var
  IMM32DLL: Longint absolute $0048A624;
  { Delphi 2 code generation crashes with absolute procedural variables.
    Use pointer slots and typed calls; the original slots are also pointers. }
  EnableImeProc: Pointer absolute $0048A628;
  GetContextProc: Pointer absolute $0048A630;
  GetConversionProc: Pointer absolute $0048A634;
  ReleaseContextProc: Pointer absolute $0048A638;
  SetOpenProc: Pointer absolute $0048A63C;
  SetConversionProc: Pointer absolute $0048A640;

function RecoveredEnableIme(Window: Longint; Enable: Boolean): LongBool;
procedure RecoveredSetImeStatus(Window: Longint; Mode: TImeMode);

implementation

function RecoveredEnableIme(Window: Longint; Enable: Boolean): LongBool;
begin
  Result := True;
  if Assigned(EnableImeProc) then Result := TEnableIme(EnableImeProc)(Window, Enable);
end;

procedure RecoveredSetImeStatus(Window: Longint; Mode: TImeMode);
var
  Context, Conversion, Sentence: Longint;
begin
  if (IMM32DLL <> 0) and (Mode <> imDontCare) then
    if Mode = imDisable then TEnableIme(EnableImeProc)(Window, False)
    else
    begin
      TEnableIme(EnableImeProc)(Window, True);
      Context := TGetContext(GetContextProc)(Window);
      if Context <> 0 then
      begin
        TGetConversion(GetConversionProc)(Context, Conversion, Sentence);
        if Mode = imClose then TSetOpen(SetOpenProc)(Context, False)
        else if Mode = imOpen then TSetOpen(SetOpenProc)(Context, True)
        else
        begin
          TSetOpen(SetOpenProc)(Context, True);
          TGetConversion(GetConversionProc)(Context, Conversion, Sentence);
          Conversion := Conversion and not $B;
          case Mode of
            imAlpha: Conversion := Conversion or $8;
            imKata: Conversion := Conversion or $B;
            imHira: Conversion := Conversion or $9;
            imSAlpha: Conversion := Conversion or $0;
            imSKata: Conversion := Conversion or $3;
          end;
        end;
        TSetConversion(SetConversionProc)(Context, Conversion, Sentence);
      end;
      TReleaseContext(ReleaseContextProc)(Window, Context);
    end;
end;

end.
