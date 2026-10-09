program RuntimeSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Controls,
  Forms,
  GameForms,
  GameState,
  GameCore,
  GameContent,
  GameGraphics,
  Gameplay,
  Persistence;
{$R ..\GameResources.res}

var
  Checks, Tick: Integer;
  Fixtures: string;
  SavedHero: THeroState;
  SavedMaps: TFloorMaps;
  Key: Word;

procedure Require(Value: Boolean; const Name: string);
begin
  if not Value then
    raise Exception.Create('Runtime assertion failed: ' + Name);
  Inc(Checks);
  WriteLn('{"check":"', Name, '","passed":true}');
end;

procedure Drain;
begin
  Tick := 0;
  while EventCursor > 0 do
  begin
    Inc(Tick);
    if Tick > 20000 then
      raise Exception.Create('Command queue did not finish');
    if EventPaused then
    begin
      MainForm.Button1Click(nil);
      if EventPaused then
        raise Exception.Create('Dialogue did not resume');
      if (EventCursor > 0) and not MainForm.Timer2.Enabled then
        raise Exception.Create('Dialogue left event timer stopped');
    end
    else if MainForm.Panel2.Visible and not MainForm.Timer2.Enabled then
      MainForm.image34click(nil)
    else
      MainForm.timer2timer(nil);
  end;
  MainForm.Timer2.Enabled := False;
end;

procedure Room(Floor: Integer);
var
  I: Integer;
begin
  Hero.cycle_factor_minus_one := 0;
  Hero.later_cycle := 0;
  InitializeCycle;
  Hero.floor := Floor;
  Hero.x := 5;
  Hero.y := 5;
  Hero.highest_floor := 50;
  Hero.facing := 1;
  Hero.effects_muted := 1;
  Hero.music_track := 0;
  for I := 2 to 122 do
    Maps[Floor, I] := 6;
  MainForm.Timer4.Enabled := False;
  MainForm.KeyboardControl1.Checked := True;
  MainForm.MouseControl1.Checked := False;
  MainForm.BitBtn1.Enabled := False;
  MainForm.BitBtn2.Enabled := False;
  MainForm.BitBtn3.Enabled := False;
  MainForm.BitBtn4.Enabled := False;
  MainForm.syokidata2;
  MainForm.itemlive;
  MainForm.Timer1.Enabled := False;
  Require((InputEnabled = 1) and (EventCursor = 0), 'room-input-ready');
end;

procedure MoveUp;
begin
  Key := VK_UP;
  MainForm.formkeydown(nil, Key, []);
  Drain;
end;

procedure PersistenceChecks;
var
  Stream: TFileStream;
  Corrupt: Byte;
  Rejected: Boolean;
begin
  SavedHero := Hero;
  SavedMaps := Maps;
  WriteSave(Fixtures + '\slot.dat', False);
  Stream := TFileStream.Create(Fixtures + '\slot.dat', fmOpenRead);
  try
    Require(Stream.Size = 6957, 'save-size');
  finally
    Stream.Free;
  end;
  Hero.hp := 1;
  Maps[Hero.floor, 62] := 99;
  ReadSave(Fixtures + '\slot.dat', False);
  Require(
      (Hero.hp = SavedHero.hp) and (Maps[Hero.floor, 62] = SavedMaps[Hero.floor, 62]),
      'slot-restores-state'
  );
  Require(SaveChecksumsValid(Hero), 'slot-checksums-valid');
  Stream := TFileStream.Create(Fixtures + '\slot.dat', fmOpenReadWrite);
  try
    Stream.Position := 6273;
    Stream.ReadBuffer(Corrupt, 1);
    Corrupt := Corrupt xor 1;
    Stream.Position := 6273;
    Stream.WriteBuffer(Corrupt, 1);
  finally
    Stream.Free;
  end;
  SavedHero := Hero;
  Rejected := False;
  try
    ReadSave(Fixtures + '\slot.dat', False);
  except
    on ESaveError do
      Rejected := True;
  end;
  Require(Rejected and (Hero.hp = SavedHero.hp), 'corrupt-save-rejected-atomically');
  WriteSave(Fixtures + '\checkpoint.dat', True);
  Hero.hp := 1;
  ReadSave(Fixtures + '\checkpoint.dat', True);
  Require(Hero.hp = SavedHero.hp, 'checkpoint-restores-state');
end;

{$I GameplayChecks.inc}
{$I LargeBattleChecks.inc}

begin
  try
    if ParamCount < 2 then
      raise Exception.Create('Assets and fixture directory required');
    Fixtures := ParamStr(2);
    Application.Initialize;
    LoadGameContent;
    MainForm := TTSW10.Create(Application);
    AboutBox := TAboutBox.Create(Application);
    RankingForm := TForm2.Create(Application);
    DataHolderForm := TForm4.Create(Application);
    MainForm.OnActivate := nil;
    MainForm.OnClose := nil;
    MainForm.Timer1.Enabled := False;
    MainForm.Timer2.Enabled := False;
    MainForm.Timer3.Enabled := False;
    MainForm.Timer4.Enabled := False;
    SkipIntroduction := True;
    ConfigurePaths(ParamStr(1), Fixtures);
    ActivatePortableInstallation(MainForm);
    MainForm.KeyboardControl1Click(nil);
    MainForm.Timer1.Enabled := False;
    Require(
        (Hero.hp = 1000)
            and (Hero.attack = 100)
            and (Hero.floor = 1)
            and (Hero.x = 5)
            and (Hero.y = 10),
        'startup-hero'
    );
    Require(MainForm.ImageList1.Count = 218, 'startup-sprite-atlas');
    Require(InputEnabled = 1, 'startup-input-enabled');
    { Exercise the introduction-to-gameplay transition that skipped-intro
      startup does not reach. The settings memo is never a display control. }
    EventCursor := 2;
    EventStack[1].A := 1;
    EventStack[2].B := 0;
    MainForm.openning9;
    EventStack[2].B := MainForm.Image1.Height;
    MainForm.openning9;
    Require(not MainForm.Memo12.Visible, 'opening-keeps-settings-buffer-hidden');
    EventCursor := 0;
    MainForm.Low1Click(nil);
    Require(
        (MainForm.Timer1.Interval = 350)
            and (MainForm.Timer2.Interval = 350)
            and (MainForm.Timer3.Interval = 350),
        'low-speed-all-timers'
    );
    MainForm.High1Click(nil);
    Require(
        (MainForm.Timer1.Interval = 150) and (MainForm.Timer2.Interval = 150),
        'high-speed-all-timers'
    );
    MainForm.Middle1Click(nil);
    Room(1);
    MoveUp;
    Require((Hero.x = 5) and (Hero.y = 4), 'keyboard-road-movement');
    Key := VK_LEFT;
    MainForm.formkeydown(nil, Key, []);
    Drain;
    Require((Hero.x = 4) and (Hero.y = 4), 'keyboard-left-movement');
    Room(1);
    Maps[1, 51] := 1;
    Hero.yellow_keys := 1;
    MoveUp;
    Require(
        (Hero.y = 5) and (Hero.yellow_keys = 0) and (Maps[1, 51] = 6),
        'yellow-door-opens-without-moving'
    );
    MoveUp;
    Require(Hero.y = 4, 'walk-through-open-door');
    Room(1);
    Maps[1, 51] := 61;
    MoveUp;
    Require((Hero.hp = 1000) and (Hero.gold = 1) and (Maps[1, 51] = 6), 'green-slime-combat');
    Room(12);
    Maps[12, 51] := 32;
    MoveUp;
    Require(Hero.hp = 1100, 'middle-band-red-potion');
    Room(12);
    Maps[12, 51] := 34;
    MoveUp;
    Require(Hero.attack = 102, 'middle-band-red-gem');
    PersistenceChecks;
    Room(1);
    Hero.hp := 2;
    Hero.attack := 1;
    Maps[1, 51] := 63;
    MoveUp;
    Require((Maps[1, 51] = 63) and (Hero.hp = 2), 'unwinnable-enemy-stays');
    Room(1);
    Hero.bomb := 1;
    Maps[1, 61] := 61;
    MainForm.img10work;
    if MainForm.Button38.Visible then
      MainForm.Button38Click(nil);
    Drain;
    Require((Hero.bomb = 0) and (Maps[1, 61] = 6), 'bomb-consumed-and-clears-enemy');
    GameplayChecks;
    LargeBattleChecks;
    Room(49);
    Hero.cycle_factor_minus_one := 0;
    QueueEnding(MainForm);
    Drain;
    Require(Hero.cycle_factor_minus_one = 43, 'ending-starts-backside-cycle');
    Require(Hero.floor = 1, 'backside-starting-floor');
    WriteLn('{"runtime_checks":', Checks, ',"passed":true}');
    ReleaseGraphics;
    DataHolderForm.Free;
    RankingForm.Free;
    AboutBox.Free;
    MainForm.Free;
  except
    on E: Exception do
    begin
      WriteLn(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
