program FormSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Forms,
  TypInfo,
  Graphics,
  Controls,
  GameForms,
  GameState,
  GameCore,
  GameContent;
{$R ..\GameResources.res}

var
  FieldChecks, BindingChecks, MethodChecks: Integer;
  GateChecks: Integer;

type
  TItemWords = array[0..14] of Longint;
  PItemWords = ^TItemWords;

procedure Require(Value: Boolean; const Message: string);
begin
  if not Value then
    raise Exception.Create(Message);
end;

procedure CheckField(Form: TForm; const Name: string; ExpectedOffset: Longint);
var
  Address: Pointer;
begin
  Address := Form.FieldAddress(Name);
  Require(Address <> nil, 'Missing published field ' + Name);
  Require(Longint(Address) - Longint(Form) = ExpectedOffset, 'Field layout ' + Name);
  Require(Pointer(Address^) = Pointer(Form.FindComponent(Name)), 'Streamed field object ' + Name);
  Inc(FieldChecks);
end;

procedure CheckPublishedMethod(Form: TForm; const Name: string);
begin
  Require(Form.MethodAddress(Name) <> nil, 'Missing published method ' + Name);
  Inc(MethodChecks);
end;

procedure CheckBinding(Form: TForm; const ComponentName, EventName, MethodName: string);
var
  Component: TComponent;
  Prop: PPropInfo;
  Method: TMethod;
begin
  if ComponentName = Form.Name then
    Component := Form
  else
    Component := Form.FindComponent(ComponentName);
  Require(Component <> nil, 'Missing event component ' + ComponentName);
  Prop := GetPropInfo(Component.ClassInfo, EventName);
  Require(Prop <> nil, 'Missing event property ' + EventName);
  Method := GetMethodProp(Component, Prop);
  Require(
      Method.Code = Form.MethodAddress(MethodName),
      'Wrong event target ' + ComponentName + '.' + EventName
  );
  Require(Method.Data = Pointer(Form), 'Wrong event self ' + ComponentName + '.' + EventName);
  Inc(BindingChecks);
end;

procedure CheckFormBindings(Form: TForm);
begin
  {$I FormChecks.inc}
end;

function Bit(Value: Boolean): string;
begin
  if Value then
    Result := '1'
  else
    Result := '0';
end;

function ControlBits(Control: TControl): string;
begin
  Result := Bit(Control.Enabled) + Bit(Control.Visible);
end;

function GateBits(Form: TTSW10): string;
begin
  Result :=
      ControlBits(Form.BitBtn1)
          + ControlBits(Form.BitBtn2)
          + ControlBits(Form.BitBtn3)
          + ControlBits(Form.BitBtn4)
          + ControlBits(Form.Image4)
          + ControlBits(Form.Image5)
          + ControlBits(Form.Image6)
          + ControlBits(Form.Image7)
          + ControlBits(Form.Image8)
          + ControlBits(Form.Image9)
          + ControlBits(Form.Image10)
          + ControlBits(Form.Image11)
          + ControlBits(Form.Image12)
          + ControlBits(Form.Image13)
          + ControlBits(Form.Image14)
          + ControlBits(Form.Image15)
          + ControlBits(Form.Image16)
          + ControlBits(Form.Image17)
          + ControlBits(Form.Image18)
          + Bit(Form.HighScore1.Enabled)
          + Bit(Form.GameLoad1.Enabled)
          + Bit(Form.GameSave1.Enabled)
          + Bit(Form.Option1.Enabled)
          + Bit(Form.KeyPreview)
          + Bit(InputEnabled <> 0);
end;

procedure TestGates(Form: TTSW10);
var
  Orb, MouseMode, KeyboardMode, Ending, Mask, I: Integer;
  Seed, Before, After: string;
  Control: TControl;
begin
  for Orb := 0 to 2 do
    for MouseMode := 0 to 1 do
      for KeyboardMode := 0 to 1 do
        for Ending := 0 to 1 do
          for Mask := 0 to 15 do
          begin
            for I := 0 to Form.ComponentCount - 1 do
              if Form.Components[I] is TControl then
              begin
                Control := TControl(Form.Components[I]);
                Control.Enabled := (Mask and 2) = 0;
                Control.Visible := (Mask and 1) = 0;
              end;
            Form.MouseControl1.Checked := MouseMode <> 0;
            Form.KeyboardControl1.Checked := KeyboardMode <> 0;
            Form.Timer4.Enabled := Ending <> 0;
            Form.HighScore1.Enabled := True;
            Form.GameLoad1.Enabled := True;
            Form.GameSave1.Enabled := True;
            Form.Option1.Enabled := True;
            Form.KeyPreview := (Mask and 4) <> 0;
            InputEnabled := 1;
            for I := 0 to 14 do
            begin
              PItemWords(@Hero.hero_orb)^[I] := (Mask shr (I mod 4)) and 1;
              if Mask >= 8 then
                PItemWords(@Hero.hero_orb)^[I] := PItemWords(@Hero.hero_orb)^[I] * 2;
            end;
            if Mask >= 4 then
              Hero.warp_staff := Hero.warp_staff * 3;
            Hero.hero_orb := Orb;
            Seed := GateBits(Form);
            Form.itemdel;
            Before := GateBits(Form);
            Require(not Form.GameSave1.Enabled and not Form.GameLoad1.Enabled, 'Modal file gate');
            Form.itemlive;
            After := GateBits(Form);
            Inc(GateChecks);
            Write(
                '{"gate_case":[',
                Orb,
                ',',
                MouseMode,
                ',',
                KeyboardMode,
                ',',
                Ending,
                ',',
                Mask,
                '],"inventory":['
            );
            for I := 0 to 14 do
            begin
              if I > 0 then
                Write(',');
              Write(PItemWords(@Hero.hero_orb)^[I]);
            end;
            WriteLn('],"seed":"', Seed, '","disabled":"', Before, '","restored":"', After, '"}');
          end;
  Form.Timer4.Enabled := False;
end;

procedure Inspect(FormClass: TFormClass; Expected: Integer);
var
  Form: TForm;
begin
  Form := FormClass.Create(nil);
  try
    Require(Form.ComponentCount = Expected, Form.ClassName + ' component count');
    Require(not Form.Visible, 'Smoke form must remain hidden');
    CheckFormBindings(Form);
    WriteLn(
        '{"form":"',
        Form.ClassName,
        '","components":',
        Form.ComponentCount,
        ',"hidden":true,"passed":true}'
    );
    if Form is TTSW10 then
    begin
      MainForm := TTSW10(Form);
      TestGates(TTSW10(Form));
      Require(TTSW10(Form).Image21.Picture.Bitmap.Width = 640, 'Ending story width');
      Require(TTSW10(Form).Image33.Picture.Bitmap.Height = 400, 'Ending card height');
      Require(Assigned(TTSW10(Form).Button8.OnClick), 'Flight up binding');
      Require(Assigned(TTSW10(Form).Button9.OnClick), 'Flight down binding');
      Require(Assigned(TTSW10(Form).Button10.OnClick), 'Flight confirmation binding');
      EventCursor := 0;
      EventPaused := 1;
      TTSW10(Form).Timer2.Enabled := True;
      TTSW10(Form).timer2timer(nil);
      Require(
          (EventCursor = 0) and (EventPaused = 1) and not TTSW10(Form).Timer2.Enabled,
          'Empty timer preserves paused dialogue'
      );
      WriteLn('{"empty_timer_safe":true,"passed":true}');
    end;
  finally
    Form.Free;
    MainForm := nil;
  end;
end;

begin
  try
    Application.Initialize;
    Require(SizeOf(Hero) = 684, 'hero layout');
    Require(SizeOf(Maps) = 6273, 'floor layout');
    Require(SizeOf(Monsters) = 528, 'monster layout');
    LoadGameContent;
    InitializeCycle;
    Require((Hero.hp = 1000) and (Hero.attack = 100) and (Hero.defense = 100), 'First cycle stats');
    Require((Hero.floor = 1) and (Hero.x = 5) and (Hero.y = 10), 'First cycle position');
    Require(Maps[1, 117] = 6, 'First cycle landing tile');
    Hero.cycle_factor_minus_one := 43;
    Hero.later_cycle := 1;
    Hero.hp := 50000;
    Hero.hero_orb := 1;
    InitializeCycle;
    Require((Hero.hp = 50000) and (Hero.hero_orb = 1), 'Later cycle preserves carried stats/items');
    WriteLn('{"core_initialization":true,"passed":true}');
    Inspect(TTSW10, 184);
    Inspect(TAboutBox, 11);
    Inspect(TForm2, 75);
    Inspect(TForm4, 9);
    Inspect(TOKBottomDlg, 3);
    Require(BindingChecks = 130, 'All serialized events checked');
    Require(MethodChecks = 230, 'All published methods checked');
    Require(FieldChecks = 279, 'All form fields checked');
    WriteLn(
        '{"serialized_bindings_verified":',
        BindingChecks,
        ',"published_fields_verified":',
        FieldChecks,
        ',"published_methods_verified":',
        MethodChecks,
        ',"modal_gate_cases":',
        GateChecks,
        ',"passed":true}'
    );
  except
    on E: Exception do
    begin
      WriteLn(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
