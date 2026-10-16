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
    Monsters[0].HP := 1000;
    Monsters[0].Attack := 0;
    Monsters[0].Defense := 0;
    Monsters[0].Gold := 1;
    Maps[1, 51] := 61;
    ContactIndex := 49;
    MainForm.taisen;
    Require(
        (EventCursor > 10000) and (EventCursor < High(EventStack)),
        'large-battle-prepares-entire-original-queue'
    );
    for I := 1 to 9 do
      MainForm.timer2timer(nil);
    Require(
        (BattleHP < 1000) and (BattleHP > 990) and (EventCursor > 10000),
        'large-battle-consumes-prepared-strikes'
    );
    Require(
        MainForm.Timer2.Enabled and (InputEnabled = 0),
        'large-battle-retains-timer-and-input-gate'
    );
    MainForm.gameover;
    Require(EventCursor = 0, 'restart-clears-original-event-queue');
    MainForm.timer2timer(nil);
    Require(EventCursor = 0, 'empty-queue-timer-stays-empty');
  finally
    Monsters[0] := SavedMonster;
  end;
end;
