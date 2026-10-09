procedure LargeBattleChecks;
var
  SavedMonster: TMonsterStats;
  I: Integer;
begin
  Room(1);
  SavedMonster := Monsters[0];
  try
    Hero.attack := 1;
    Hero.defense := 0;
    Monsters[0].HP := 100000;
    Monsters[0].Attack := 0;
    Monsters[0].Defense := 0;
    Monsters[0].Gold := 1;
    Maps[1, 51] := 61;
    ContactIndex := 49;
    MainForm.taisen;
    Require((EventCursor > 0) and (EventCursor < 50), 'large-battle-uses-bounded-event-memory');
    for I := 1 to 9 do
      MainForm.timer2timer(nil);
    Require(
        (BattleHP < 100000) and (BattleHP > 99990) and (EventCursor < 50),
        'large-battle-refills-strikes'
    );
    Require(
        MainForm.Timer2.Enabled and (InputEnabled = 0),
        'large-battle-retains-timer-and-input-gate'
    );
    MainForm.gameover;
    Require((EventCursor = 0) and not BattleNeedsRefill, 'restart-cancels-pending-battle');
    MainForm.timer2timer(nil);
    Require(EventCursor = 0, 'cancelled-battle-does-not-refill');
  finally
    Monsters[0] := SavedMonster;
  end;
end;
