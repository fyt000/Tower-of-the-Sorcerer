{ Floor arrival scenes and rewards unlocked after combat. Scene commands are
  pushed in reverse playback order. PushCommand comments show the compact
  equivalent of each expanded write; they are annotations, not helper calls.
  Explicit stores preserve the original Delphi 2 routine structure. }

procedure TTSW10.ichicheck; { Arrival triggers. $0046CB1C }
begin
  case Hero.floor of
    10: { First visit: skeleton march and arena gates. Return visit: thief escort. }
    begin
      if (Hero.Word424 = 0) then
      begin
        if (Hero.music_track <> 0) then
        begin
          Hero.music_track := 15;
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 5, 0): resume selected music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 5;
          EventStack[EventCursor].B := 0;
        end;
        { PushCommand(13, (3 * 11 + 7), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 3), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := (3 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 8), (3 * 11 + 7)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := (3 * BoardWidth + 7);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 9), (3 * 11 + 8)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := (3 * BoardWidth + 8);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 10), (3 * 11 + 9)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 10);
        EventStack[EventCursor].B := (3 * BoardWidth + 9);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 10), (3 * 11 + 10)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 10);
        EventStack[EventCursor].B := (3 * BoardWidth + 10);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := (3 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 2), (3 * 11 + 3)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := (3 * BoardWidth + 3);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 1), (3 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := (3 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 0), (3 * 11 + 1)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 0);
        EventStack[EventCursor].B := (3 * BoardWidth + 1);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 0), (3 * 11 + 0)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 0);
        EventStack[EventCursor].B := (3 * BoardWidth + 0);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 6), (4 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 6);
        EventStack[EventCursor].B := (4 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := (3 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 8), (3 * 11 + 7)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := (3 * BoardWidth + 7);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 9), (3 * 11 + 8)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := (3 * BoardWidth + 8);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 9), (3 * 11 + 9)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 9);
        EventStack[EventCursor].B := (3 * BoardWidth + 9);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 4);
        EventStack[EventCursor].B := (4 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := (3 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 2), (3 * 11 + 3)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := (3 * BoardWidth + 3);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 1), (3 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := (3 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 1), (3 * 11 + 1)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 1);
        EventStack[EventCursor].B := (3 * BoardWidth + 1);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (4 * 11 + 6), (5 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (4 * BoardWidth + 6);
        EventStack[EventCursor].B := (5 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 6), (4 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 6);
        EventStack[EventCursor].B := (4 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := (3 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 8), (3 * 11 + 7)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := (3 * BoardWidth + 7);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 8), (3 * 11 + 8)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 8);
        EventStack[EventCursor].B := (3 * BoardWidth + 8);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (4 * 11 + 4), (5 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (4 * BoardWidth + 4);
        EventStack[EventCursor].B := (5 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 4);
        EventStack[EventCursor].B := (4 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := (3 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 2), (3 * 11 + 3)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := (3 * BoardWidth + 3);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 2), (3 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 2);
        EventStack[EventCursor].B := (3 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 6), (3 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 6);
        EventStack[EventCursor].B := (3 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := (3 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 8), (3 * 11 + 7)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := (3 * BoardWidth + 7);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 9), (3 * 11 + 8)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := (3 * BoardWidth + 8);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (5 * 11 + 4), (5 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (5 * BoardWidth + 4);
        EventStack[EventCursor].B := (5 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (4 * 11 + 4), (5 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (4 * BoardWidth + 4);
        EventStack[EventCursor].B := (5 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 4);
        EventStack[EventCursor].B := (4 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := (3 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 2), (3 * 11 + 3)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := (3 * BoardWidth + 3);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 4, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 4;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 1), (3 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := (3 * BoardWidth + 2);
        { PushCommand(13, (3 * 11 + 7), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 3), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (6 * 11 + 5), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (2 * 11 + 5), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (1 * 11 + 5), (0 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (1 * BoardWidth + 5);
        EventStack[EventCursor].B := (0 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 5), (1 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := (1 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 5), (2 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 5);
        EventStack[EventCursor].B := (2 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (5 * 11 + 6), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (5 * BoardWidth + 6);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (5 * 11 + 4), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (5 * BoardWidth + 4);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 13, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechSkeletonLordChallenge;
        EventStack[EventCursor].B := 0;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 6, 0): stop music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 6;
          EventStack[EventCursor].B := 0;
        end;
      end
      else
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (9 * 11 + 5), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (9 * BoardWidth + 5);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 17, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechThiefSecondDeparture;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (9 * 11 + 4), (9 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (9 * BoardWidth + 4);
        EventStack[EventCursor].B := (9 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (10 * 11 + 4), (9 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (10 * BoardWidth + 4);
        EventStack[EventCursor].B := (9 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (10 * 11 + 3), (10 * 11 + 4)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (10 * BoardWidth + 3);
        EventStack[EventCursor].B := (10 * BoardWidth + 4);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (10 * 11 + 2), (10 * 11 + 3)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (10 * BoardWidth + 2);
        EventStack[EventCursor].B := (10 * BoardWidth + 3);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (9 * 11 + 2), (10 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (9 * BoardWidth + 2);
        EventStack[EventCursor].B := (10 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (8 * 11 + 2), (9 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (8 * BoardWidth + 2);
        EventStack[EventCursor].B := (9 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (7 * 11 + 2), (8 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (7 * BoardWidth + 2);
        EventStack[EventCursor].B := (8 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (7 * 11 + 1), (7 * 11 + 2)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (7 * BoardWidth + 1);
        EventStack[EventCursor].B := (7 * BoardWidth + 2);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (7 * 11 + 0), (7 * 11 + 1)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (7 * BoardWidth + 0);
        EventStack[EventCursor].B := (7 * BoardWidth + 1);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (8 * 11 + 0), (7 * 11 + 0)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (8 * BoardWidth + 0);
        EventStack[EventCursor].B := (7 * BoardWidth + 0);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (9 * 11 + 0), (8 * 11 + 0)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (9 * BoardWidth + 0);
        EventStack[EventCursor].B := (8 * BoardWidth + 0);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (9 * 11 + 0), 21): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (9 * BoardWidth + 0);
        EventStack[EventCursor].B := tileThief;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
      end;
    end;
    15: { Enter the octopus chamber and close its gate. }
    begin
      { PushCommand(13, (8 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (8 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 5): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 5;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    20: { Clear the central chamber and animate the vampire transformation. }
    begin
      Button1.Caption := ListBox2.Items[218];
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 5, 0): resume selected music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 5;
        EventStack[EventCursor].B := 0;
      end;
      Maps[Hero.floor, 2 + 4 * BoardWidth + 4] := tileRoad;
      Maps[Hero.floor, 2 + 4 * BoardWidth + 5] := tileRoad;
      Maps[Hero.floor, 2 + 4 * BoardWidth + 6] := tileRoad;
      Maps[Hero.floor, 2 + 5 * BoardWidth + 4] := tileRoad;
      Maps[Hero.floor, 2 + 5 * BoardWidth + 6] := tileRoad;
      Maps[Hero.floor, 2 + 6 * BoardWidth + 4] := tileRoad;
      Maps[Hero.floor, 2 + 6 * BoardWidth + 5] := tileRoad;
      Maps[Hero.floor, 2 + 6 * BoardWidth + 6] := tileRoad;
      Maps[Hero.floor, 2 + 5 * BoardWidth + 5] := tileVampire;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 20, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechVampireChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 32): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 32;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 31): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 31;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 30): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 30;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 29): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 29;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 28): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 28;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 27): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 27;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 26): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 26;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 25): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 25;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 24): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 24;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 23): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 23;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 22): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 22;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 21): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 21;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 20): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 20;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 19): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 19;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 18): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 18;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 17): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 17;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 16): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 16;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 15): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 15;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 14): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 14;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 13): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 13;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 12): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 12;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 11): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 11;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 10): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 10;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 9): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 9;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 8): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 8;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 7): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 7;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 6): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 6;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 5): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 5;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 4): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 4;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 3): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 3;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 2): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 2;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 4, 1): vampire transformation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 1;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 8, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 8;
      EventStack[EventCursor].B := 0;
      timer2on;
      { PushCommand(13, (8 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (8 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 6, 0): stop music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 6;
        EventStack[EventCursor].B := 0;
      end;
    end;
    24: { Enter the time gate, travel to 50F, then reveal the true Zeno. }
    begin
      timer2on;
      Button1.Caption := 'OK';
      { The true Zeno restores any strength removed by the 49F sealing puzzle. }
      if (Hero.zeno_sealed = 1) then
      begin
        Hero.zeno_sealed := 0;
        Monsters[15].HP := (Monsters[15].HP * 10);
        Monsters[15].attack := (Monsters[15].attack * 10);
        Monsters[15].defense := (Monsters[15].defense * 10);
      end;
      if ((Hero.cycle_factor_minus_one <> 0) and (Hero.later_cycle = 0)) then
      begin
        Monsters[15].HP := 1000;
        Monsters[15].attack := 625;
        Monsters[15].defense := 125;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 10, 71): start forced combat at cell B. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 10;
        EventStack[EventCursor].B := 71;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (5 * BoardWidth + 5);
        EventStack[EventCursor].B := (6 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (4 * BoardWidth + 5);
        EventStack[EventCursor].B := (5 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
      end;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 57, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoOffersAlliance;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 56, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroQuestionsPrincessRumor;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 55, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoRevealsPlan;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 54, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroQuestionsLegend;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 53, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoExplainsLegend;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 52, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroQuestionsTest;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 51, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoExplainsTest;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 50, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroRecognizesZeno;
      EventStack[EventCursor].B := 0;
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(15, 0, 0): floor music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evFloorMusic);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      { PushCommand(17, (4 * 11 + 5), 91): change map only. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := tileZeno;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 182): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 182;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 181): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 181;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 180): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 180;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 179): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 179;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 178): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 178;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 177): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 177;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 176): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 176;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 175): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 175;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 174): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 174;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 173): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 173;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 172): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 172;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 171): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 171;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 170): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 170;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 169): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 169;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 168): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 168;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 167): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 167;
      { PushCommand(0, 21, 91): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 21;
      EventStack[EventCursor].B := 91;
      { PushCommand(9, 49, 166): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 49;
      EventStack[EventCursor].B := 166;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 7, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 7;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 49, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechThiefRevealsDisguise;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 48, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroFindsThief;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 50): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 50;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 49): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 49;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 48): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 48;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 47): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 47;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 46): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 46;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 45): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 45;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 44): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 44;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 43): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 43;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 42): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 42;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 41): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 41;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 40): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 40;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 39): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 39;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 38): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 38;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 37): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 37;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 36): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 36;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 35): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 35;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 34): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 34;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 33): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 33;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 32): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 32;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 31): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 31;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 30): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 30;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 29): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 29;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 28): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 28;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 27): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 27;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 26): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 26;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 11, 25): change floor to B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 11;
      EventStack[EventCursor].B := 25;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 6, 0): stop music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 6;
        EventStack[EventCursor].B := 0;
      end;
    end;
    25: { Introduce the Great Magic Master and seal the chamber. }
    begin
      Button1.Caption := ListBox2.Items[218];
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 23, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechRockChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (9 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (9 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    30: { Seal both gates of the guard chamber. }
    begin
      { PushCommand(13, (6 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (3 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    32: { Stair arrival: Golden Knight approach, dialogue and forced battle. }
    begin
      Button1.Caption := ListBox2.Items[218];
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 104): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 104;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (8 * 11 + 5), (9 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (8 * BoardWidth + 5);
      EventStack[EventCursor].B := (9 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (7 * 11 + 5), (8 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (7 * BoardWidth + 5);
      EventStack[EventCursor].B := (8 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (6 * 11 + 5), (7 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := (7 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 30, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 5), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 5);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 5), (2 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 5);
      EventStack[EventCursor].B := (2 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (0 * 11 + 5), (1 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (0 * BoardWidth + 5);
      EventStack[EventCursor].B := (1 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (0 * 11 + 6), (0 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (0 * BoardWidth + 6);
      EventStack[EventCursor].B := (0 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (0 * 11 + 7), (0 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (0 * BoardWidth + 7);
      EventStack[EventCursor].B := (0 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (0 * 11 + 8), (0 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (0 * BoardWidth + 8);
      EventStack[EventCursor].B := (0 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (0 * 11 + 9), (0 * 11 + 8)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (0 * BoardWidth + 9);
      EventStack[EventCursor].B := (0 * BoardWidth + 8);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (0 * 11 + 9), 133): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (0 * BoardWidth + 9);
      EventStack[EventCursor].B := tileGoldenKnight;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    33: { Wrong approach at cell 107 raises a wall; otherwise seal the guard room. }
    begin
      if (((Hero.y * BoardWidth) + Hero.x) = 107) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(2, 114, 0): refresh status/message. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := 114;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (9 * 11 + 7), 8): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (9 * BoardWidth + 7);
        EventStack[EventCursor].B := 8;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end
      else
      begin
        { PushCommand(13, (7 * 11 + 9), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 9);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 9), 5): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := 5;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    38: { The blocked shortcut raises a wall. }
    begin
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, 114, 0): refresh status/message. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 114;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (4 * 11 + 1), 8): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (4 * BoardWidth + 1);
      EventStack[EventCursor].B := 8;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    40: { Seal the Golden Knight arena and stage the thirteen-fight gauntlet. }
    begin
      Button1.Caption := ListBox2.Items[218];
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + 4] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + 4] := tileGhostSoldier;
      end;
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + 3] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + 3] := tileGhostSoldier;
      end;
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + MapTileOffset] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + MapTileOffset] := tileGhostSoldier;
      end;
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + 6] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + 6] := tileSoldier;
      end;
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + 7] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + 7] := tileSoldier;
      end;
      if (Maps[Hero.floor, 2 + 3 * BoardWidth + 8] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 3 * BoardWidth + 8] := tileSoldier;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 3] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 3] := tileSwordsman;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + MapTileOffset] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + MapTileOffset] := tileSwordsman;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 1] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 1] := tileSwordsman;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 7] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 7] := tileKnight;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 8] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 8] := tileKnight;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 9] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 9] := tileKnight;
      end;
      if (Maps[Hero.floor, 2 + 1 * BoardWidth + 5] = tileRoad) then
      begin
        Maps[Hero.floor, 2 + 1 * BoardWidth + 5] := tileGoldenKnight;
      end;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 5, 0): check post-combat rewards. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 5;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (1 * 11 + 5), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (1 * BoardWidth + 5);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 5), (1 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 5);
      EventStack[EventCursor].B := (1 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (2 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (2 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (6 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(17, (6 * 11 + 5), 133): change map only. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := tileGoldenKnight;
      { PushCommand(10, 39, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterDefeated;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (0 * 11 + 5), 11): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (0 * BoardWidth + 5);
      EventStack[EventCursor].B := tileStairsUp;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, 4, 0): refresh status/message. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (7 * 11 + 5), 4): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (7 * BoardWidth + 5);
      EventStack[EventCursor].B := 4;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 5), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 5);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 5), (2 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 5);
      EventStack[EventCursor].B := (2 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 38, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterBattle;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 6), (3 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 7), (2 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 7), (2 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 8), (1 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 8);
      EventStack[EventCursor].B := (1 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 9), (1 * 11 + 8)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 9);
      EventStack[EventCursor].B := (1 * BoardWidth + 8);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 6), (3 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 7), (2 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 7), (2 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 8), (1 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 8);
      EventStack[EventCursor].B := (1 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 6), (3 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 6);
      EventStack[EventCursor].B := (3 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 7), (2 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 7), (2 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 7);
      EventStack[EventCursor].B := (2 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 37, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterSummonsKnights;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 4), (3 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 3), (2 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 3), (2 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 2), (1 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 2);
      EventStack[EventCursor].B := (1 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 1), (1 * 11 + 2)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 1);
      EventStack[EventCursor].B := (1 * BoardWidth + 2);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 4), (3 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 3), (2 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 3), (2 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 2), (1 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 2);
      EventStack[EventCursor].B := (1 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 5), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 5);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (3 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 4), (3 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 4);
      EventStack[EventCursor].B := (3 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (2 * 11 + 3), (2 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (2 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (1 * 11 + 3), (2 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (1 * BoardWidth + 3);
      EventStack[EventCursor].B := (2 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 36, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterSummonsSwordsmen;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 6), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (4 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 7);
      EventStack[EventCursor].B := (3 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 8), (3 * 11 + 7)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 8);
      EventStack[EventCursor].B := (3 * BoardWidth + 7);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 6), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (4 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 7), (3 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 7);
      EventStack[EventCursor].B := (3 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 6), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 6), (4 * 11 + 6)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 6);
      EventStack[EventCursor].B := (4 * BoardWidth + 6);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 35, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterSummonsSoldiers;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 4), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 3);
      EventStack[EventCursor].B := (3 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 2), (3 * 11 + 3)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 2);
      EventStack[EventCursor].B := (3 * BoardWidth + 3);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 4), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 3), (3 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 3);
      EventStack[EventCursor].B := (3 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 10, 71): start forced combat at cell B. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 10;
      EventStack[EventCursor].B := 71;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (5 * 11 + 5), (6 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := (6 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 5), (5 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 5);
      EventStack[EventCursor].B := (5 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (4 * 11 + 4), (4 * 11 + 5)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (4 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 5);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, (3 * 11 + 4), (4 * 11 + 4)): monster movement. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := (3 * BoardWidth + 4);
      EventStack[EventCursor].B := (4 * BoardWidth + 4);
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 34, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGreatMagicMasterFinalChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (7 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (7 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    42: { Zeno arrives, summons four guards and executes the Golden Knight. }
    begin
      Maps[35, 2 + 9 * BoardWidth + 4] := tileRoad;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (5 * 11 + 5), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (5 * BoardWidth + 5);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 44, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoPromisesFairFight;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (7 * 11 + 6), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (7 * BoardWidth + 6);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(6, (7 * 11 + 4), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (7 * BoardWidth + 4);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(6, (8 * 11 + 5), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (8 * BoardWidth + 5);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(6, (6 * 11 + 5), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (7 * 11 + 5), 6): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (7 * BoardWidth + 5);
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, Maps[Hero.floor, 2 + 7 * 11 + 5], 184): wait / paired animation operands. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := Maps[Hero.floor, 2 + 7 * BoardWidth + 5];
      EventStack[EventCursor].B := 184;
      { PushCommand(9, 82, 183): masked overlay. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := 82;
      EventStack[EventCursor].B := 183;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 4, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 4;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 43, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGoldenKnightPleads;
      EventStack[EventCursor].B := 0;
      ScratchIndex := 71;
      NeighborIndex := 93;
      NeighborY := 81;
      DamageMode := 83;
      madoushilivework;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 42, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoRebukesGoldenKnight;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 41, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechGoldenKnightReportsFailure;
      EventStack[EventCursor].B := 0;
      ScratchIndex := 60;
      zenolivework;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      timer2on;
    end;
    43: { The upper-passage sorcerer retreats and raises two walls. }
    begin
      if (Maps[Hero.floor, 2 + 0 * BoardWidth + 8] = tileSorcerer) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (0 * 11 + 9), 8): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (0 * BoardWidth + 9);
        EventStack[EventCursor].B := 8;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (0 * 11 + 6), 8): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (0 * BoardWidth + 6);
        EventStack[EventCursor].B := 8;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 9), (0 * 11 + 10)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 9);
        EventStack[EventCursor].B := (0 * BoardWidth + 10);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 8), (0 * 11 + 9)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 8);
        EventStack[EventCursor].B := (0 * BoardWidth + 9);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end
      else
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    48: { Reveal the sorcerer in the northwest corner. }
    begin
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, (0 * 11 + 0), 93): change tile and redraw. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := (0 * BoardWidth + 0);
      EventStack[EventCursor].B := tileSorcerer;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    49: { Seal the decoy Zeno chamber and summon Zeno with eight sorcerer guards. }
    begin
      Button1.Caption := ListBox2.Items[218];
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 3, 0): summon the eight floor-49 guards. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 3;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 5, 0): resume selected music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 5;
        EventStack[EventCursor].B := 0;
      end;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 45, 0): story dialogue. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechZenoFinalChallenge;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 2, 0): materialize Zeno. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, (6 * 11 + 5), 5): door/wall animation frame. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := (6 * BoardWidth + 5);
      EventStack[EventCursor].B := 5;
      doorstackin;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0): play sound effect A. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0): wait. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      if (Hero.music_track <> 0) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 6, 0): stop music. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 6;
        EventStack[EventCursor].B := 0;
      end;
    end;
  end;
  if EventCursor >= 1 then
    timer2on;
end;

procedure TTSW10.moncheck; { Guard gates and boss rewards after combat. $004664E4 }
begin
  case Hero.floor of
    2: { Defeat both prison guards to open the six cell gates. }
    begin
      if (((Maps[Hero.floor, 2 + 1 * BoardWidth + 5] + Maps[Hero.floor, 2 + 1 * BoardWidth + 7])
              + Maps[Hero.floor, 2 + 4 * BoardWidth + 4])
          = 17) then
      begin
        { PushCommand(13, (10 * 11 + 8), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (10 * BoardWidth + 8);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (10 * 11 + 4), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (10 * BoardWidth + 4);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (7 * 11 + 8), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 8);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (7 * 11 + 4), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 4);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (4 * 11 + 8), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (4 * BoardWidth + 8);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (4 * 11 + 4), 6): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (4 * BoardWidth + 4);
        EventStack[EventCursor].B := 6;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    8: { Defeat the guard pair to open their gate. }
    begin
      if (((Maps[Hero.floor, 2 + 4 * BoardWidth + 8] + Maps[Hero.floor, 2 + 4 * BoardWidth + 10])
              + Maps[Hero.floor, 2 + 3 * BoardWidth + 9])
          = 16) then
      begin
        { PushCommand(13, (3 * 11 + 9), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    10: { Skeleton guards unlock the boss; clearing the arena unlocks stairs and loot. }
    begin
      if (((((((((Maps[Hero.floor, 2 + 3 * BoardWidth + 4]
                                          + Maps[Hero.floor, 2 + 3 * BoardWidth + 5])
                                      + Maps[Hero.floor, 2 + 3 * BoardWidth + 6])
                                  + Maps[Hero.floor, 2 + 4 * BoardWidth + 4])
                              + Maps[Hero.floor, 2 + 4 * BoardWidth + 6])
                          + Maps[Hero.floor, 2 + 5 * BoardWidth + 4])
                      + Maps[Hero.floor, 2 + 5 * BoardWidth + 5])
                  + Maps[Hero.floor, 2 + 5 * BoardWidth + 6])
              + Maps[Hero.floor, 2 + 2 * BoardWidth + 5])
          = 52) then
      begin
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 5, 0): resume selected music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 5;
          EventStack[EventCursor].B := 0;
        end;
        { PushCommand(13, (2 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 14, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechSkeletonLordBattle;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if ((((Maps[Hero.floor, 2 + 0 * BoardWidth + 5] + Maps[Hero.floor, 2 + 6 * BoardWidth + 5])
                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 7])
              + Maps[Hero.floor, 2 + 3 * BoardWidth + 3])
          = 18) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (8 * 11 + 5), 7): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (8 * BoardWidth + 5);
        EventStack[EventCursor].B := tileSpecialRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (10 * 11 + 5), 11): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (10 * BoardWidth + 5);
        EventStack[EventCursor].B := tileStairsUp;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 10), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 10);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 9), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 8), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 2), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 1), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 0), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 0);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 10), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 10);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 9), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 9);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 8), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 8);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 2), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 2);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 1), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 1);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 0), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 0);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 5), 23): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := tileFairy;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (6 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 7), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 3), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 15, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechSkeletonLordDefeated;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 6, 0): stop music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 6;
          EventStack[EventCursor].B := 0;
        end;
      end;
    end;
    11: { Defeat the guard pair to open their gate. }
    begin
      if (((Maps[Hero.floor, 2 + 4 * BoardWidth + 0]
                  + Maps[Hero.floor, 2 + 4 * BoardWidth + MapTileOffset])
              + Maps[Hero.floor, 2 + 3 * BoardWidth + 1])
          = 16) then
      begin
        { PushCommand(13, (3 * 11 + 1), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    14: { Defeat all three guards to reveal a red key. }
    begin
      if ((((Maps[Hero.floor, 2 + 0 * BoardWidth + 0]
                      + Maps[Hero.floor, 2 + 0 * BoardWidth + MapTileOffset])
                  + Maps[Hero.floor, 2 + 1 * BoardWidth + 1])
              + Maps[Hero.floor, 2 + 2 * BoardWidth + 0])
          = 26) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (2 * 11 + 0), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (2 * BoardWidth + 0);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    15: { Defeat the octopus to reveal the mattock and reopen the chamber. }
    begin
      if (((Maps[Hero.floor, 2 + 5 * BoardWidth + 5] + Maps[Hero.floor, 2 + 2 * BoardWidth + 5])
              + Maps[Hero.floor, 2 + 8 * BoardWidth + 5])
          = 14) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 5), 41): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 5);
        EventStack[EventCursor].B := tileMattock;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (8 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (8 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (2 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    17: { Each of the four guard pairs opens its own gate. }
    begin
      if (((Maps[Hero.floor, 2 + 4 * BoardWidth + 8] + Maps[Hero.floor, 2 + 4 * BoardWidth + 10])
              + Maps[Hero.floor, 2 + 3 * BoardWidth + 9])
          = 16) then
      begin
        { PushCommand(13, (3 * 11 + 9), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 7 * BoardWidth + 8] + Maps[Hero.floor, 2 + 7 * BoardWidth + 10])
              + Maps[Hero.floor, 2 + 6 * BoardWidth + 9])
          = 16) then
      begin
        { PushCommand(13, (6 * 11 + 9), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 9);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 4 * BoardWidth + 0]
                  + Maps[Hero.floor, 2 + 4 * BoardWidth + MapTileOffset])
              + Maps[Hero.floor, 2 + 3 * BoardWidth + 1])
          = 16) then
      begin
        { PushCommand(13, (3 * 11 + 1), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 7 * BoardWidth + 0]
                  + Maps[Hero.floor, 2 + 7 * BoardWidth + MapTileOffset])
              + Maps[Hero.floor, 2 + 6 * BoardWidth + 1])
          = 16) then
      begin
        { PushCommand(13, (6 * 11 + 1), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 1);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    20: { Defeat the vampire to reveal the fairy, stairs and chamber loot. }
    begin
      if (((((((((((Maps[Hero.floor, 2 + 4 * BoardWidth + 4]
                                                  + Maps[Hero.floor, 2 + 4 * BoardWidth + 5])
                                              + Maps[Hero.floor, 2 + 4 * BoardWidth + 6])
                                          + Maps[Hero.floor, 2 + 5 * BoardWidth + 4])
                                      + Maps[Hero.floor, 2 + 5 * BoardWidth + 6])
                                  + Maps[Hero.floor, 2 + 6 * BoardWidth + 4])
                              + Maps[Hero.floor, 2 + 6 * BoardWidth + 5])
                          + Maps[Hero.floor, 2 + 6 * BoardWidth + 6])
                      + Maps[Hero.floor, 2 + 5 * BoardWidth + 5])
                  + Maps[Hero.floor, 2 + 2 * BoardWidth + 5])
              + Maps[Hero.floor, 2 + 8 * BoardWidth + 5])
          = 62) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (0 * 11 + 5), 11): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (0 * BoardWidth + 5);
        EventStack[EventCursor].B := tileStairsUp;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 6), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 6);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 5), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 5);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 4), 29): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 4);
        EventStack[EventCursor].B := tileYellowKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 6), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 6);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 5), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 5);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 4), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 4);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (6 * 11 + 7), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (6 * BoardWidth + 7);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (5 * 11 + 7), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (5 * BoardWidth + 7);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 7), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 7);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (6 * 11 + 3), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (6 * BoardWidth + 3);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (5 * 11 + 3), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (5 * BoardWidth + 3);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 3), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 3);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 5), 23): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 5);
        EventStack[EventCursor].B := tileFairy;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 6, 0): stop music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 6;
          EventStack[EventCursor].B := 0;
        end;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 21, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechVampireDefeated;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (8 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (8 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (2 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    25: { Defeat the Great Magic Master to reveal the fairy and red keys. }
    begin
      if ((Maps[Hero.floor, 2 + 5 * BoardWidth + 5] + Maps[Hero.floor, 2 + 9 * BoardWidth + 5])
          = 10) then
      begin
        if (Hero.Word464 = 1) then
        begin
          { The time-gate dialogue also prepares the route through 24F. }
          Maps[24, 2 + 0 * BoardWidth + 4] := tileWall;
          Maps[24, 2 + 0 * BoardWidth + 6] := tileWall;
          Maps[24, 2 + 1 * BoardWidth + 5] := tileRoad;
          Maps[24, 2 + 2 * BoardWidth + 5] := tileRoad;
          Maps[24, 2 + 3 * BoardWidth + 5] := tileRoad;
          Maps[24, 2 + 0 * BoardWidth + 5] := tileSpecialRoad;
        end;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 7), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 7);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 6), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 6);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 5), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 5);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 4), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 4);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (7 * 11 + 3), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (7 * BoardWidth + 3);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (6 * 11 + 5), 23): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := tileFairy;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (9 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (9 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    30: { Clear the guard line to reveal stairs and reopen the chamber. }
    begin
      if ((((((((Maps[Hero.floor, 2 + 4 * BoardWidth + MapTileOffset]
                                      + Maps[Hero.floor, 2 + 4 * BoardWidth + 3])
                                  + Maps[Hero.floor, 2 + 4 * BoardWidth + 4])
                              + Maps[Hero.floor, 2 + 4 * BoardWidth + 6])
                          + Maps[Hero.floor, 2 + 4 * BoardWidth + 7])
                      + Maps[Hero.floor, 2 + 4 * BoardWidth + 8])
                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 5])
              + Maps[Hero.floor, 2 + 6 * BoardWidth + 5])
          = 44) then
      begin
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (0 * 11 + 5), 11): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (0 * BoardWidth + 5);
        EventStack[EventCursor].B := tileStairsUp;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (6 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    32: { Open the paired-guard gate; the Golden Knight defeat advances the thief story. }
    begin
      if (((Maps[Hero.floor, 2 + 9 * BoardWidth + 0]
                  + Maps[Hero.floor, 2 + 9 * BoardWidth + MapTileOffset])
              + Maps[Hero.floor, 2 + 8 * BoardWidth + 1])
          = 16) then
      begin
        { PushCommand(13, (8 * 11 + 1), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (8 * BoardWidth + 1);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 5 * BoardWidth + 5] + Hero.Word480) + Hero.Word484) = 7) then
      begin
        Button1.Caption := 'OK';
        Maps[29, 2 + 1 * BoardWidth + 6] := tileRoad;
        Maps[2, 2 + 10 * BoardWidth + 10] := tileThief;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (0 * 11 + 9), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (0 * BoardWidth + 9);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 8), (0 * 11 + 9)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 8);
        EventStack[EventCursor].B := (0 * BoardWidth + 9);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 7), (0 * 11 + 8)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 7);
        EventStack[EventCursor].B := (0 * BoardWidth + 8);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 6), (0 * 11 + 7)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 6);
        EventStack[EventCursor].B := (0 * BoardWidth + 7);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (0 * 11 + 5), (0 * 11 + 6)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (0 * BoardWidth + 5);
        EventStack[EventCursor].B := (0 * BoardWidth + 6);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (1 * 11 + 5), (0 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (1 * BoardWidth + 5);
        EventStack[EventCursor].B := (0 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (2 * 11 + 5), (1 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (2 * BoardWidth + 5);
        EventStack[EventCursor].B := (1 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (3 * 11 + 5), (2 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (3 * BoardWidth + 5);
        EventStack[EventCursor].B := (2 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (4 * 11 + 5), (3 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (4 * BoardWidth + 5);
        EventStack[EventCursor].B := (3 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (5 * 11 + 5), (4 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (5 * BoardWidth + 5);
        EventStack[EventCursor].B := (4 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (6 * 11 + 5), (5 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := (5 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (7 * 11 + 5), (6 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (7 * BoardWidth + 5);
        EventStack[EventCursor].B := (6 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (8 * 11 + 5), (7 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (8 * BoardWidth + 5);
        EventStack[EventCursor].B := (7 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(12, (9 * 11 + 5), (8 * 11 + 5)): monster movement. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evMoveMonster);
        EventStack[EventCursor].A := (9 * BoardWidth + 5);
        EventStack[EventCursor].B := (8 * BoardWidth + 5);
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(17, (9 * 11 + 5), 133): change map only. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
        EventStack[EventCursor].A := (9 * BoardWidth + 5);
        EventStack[EventCursor].B := tileGoldenKnight;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 31, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechGreatMagicMasterRetreat;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    33: { Defeat all four guards to reopen the chamber gates. }
    begin
      if ((((((Maps[Hero.floor, 2 + 4 * BoardWidth + 8] + Maps[Hero.floor, 2 + 4 * BoardWidth + 10])
                          + Maps[Hero.floor, 2 + 6 * BoardWidth + 8])
                      + Maps[Hero.floor, 2 + 6 * BoardWidth + 10])
                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 9])
              + Maps[Hero.floor, 2 + 7 * BoardWidth + 9])
          = 32) then
      begin
        { PushCommand(13, (7 * 11 + 9), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 9);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (3 * 11 + 9), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    34: { Defeat all eight guards to reveal the key cache once. }
    begin
      if ((((((((Maps[Hero.floor, 2 + 3 * BoardWidth + 4]
                                      + Maps[Hero.floor, 2 + 3 * BoardWidth + 6])
                                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 8])
                              + Maps[Hero.floor, 2 + 3 * BoardWidth + 10])
                          + Maps[Hero.floor, 2 + 7 * BoardWidth + 4])
                      + Maps[Hero.floor, 2 + 7 * BoardWidth + 6])
                  + Maps[Hero.floor, 2 + 7 * BoardWidth + 8])
              + Maps[Hero.floor, 2 + 7 * BoardWidth + 10])
          = 48) then
        case Hero.Word592 of
          0:
          begin
            Hero.Word592 := 1;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (6 * 11 + 2), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (6 * BoardWidth + 2);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (6 * 11 + 0), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (6 * BoardWidth + 0);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 2), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 2);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 0), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 0);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 1), 30): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 1);
            EventStack[EventCursor].B := tileRedKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
          end;
        end;
    end;
    35: { Defeat the dragon to reveal the snow crystal and potions once. }
    begin
      if ((Maps[Hero.floor, 2 + 6 * BoardWidth + 5] + Maps[Hero.floor, 2 + 2 * BoardWidth + 5])
          = 10) then
        case Hero.Word596 of
          0:
          begin
            Hero.Word596 := 1;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 6), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 6);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 5), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 5);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 4), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 4);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 5), 47): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 5);
            EventStack[EventCursor].B := tileSnowCrystal;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(13, (2 * 11 + 5), 4): door/wall animation frame. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evDoorFrame);
            EventStack[EventCursor].A := (2 * BoardWidth + 5);
            EventStack[EventCursor].B := 4;
            doorstackin;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
          end;
        end;
    end;
    38: { Clearing the two guards reveals a secret wall. }
    begin
      if ((Maps[Hero.floor, 2 + 9 * BoardWidth + 0]
              + Maps[Hero.floor, 2 + 9 * BoardWidth + MapTileOffset])
          = 12) then
      begin
        Maps[Hero.floor, 2 + 8 * BoardWidth + 1] := tileSecretWall;
      end;
    end;
    40: { Defeat the Golden Knight to reveal the fairy and arena loot once. }
    begin
      if ((Maps[Hero.floor, 2 + 1 * BoardWidth + 5] + Maps[Hero.floor, 2 + 0 * BoardWidth + 5])
          = 17) then
        case Hero.Word600 of
          0:
          begin
            Hero.Word600 := 1;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 8), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 8);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 7), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 7);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 6), 29): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 6);
            EventStack[EventCursor].B := tileYellowKey;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 4), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 4);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 3), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 3);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (3 * 11 + 2), 33): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (3 * BoardWidth + 2);
            EventStack[EventCursor].B := tileBluePotion;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 9), 35): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 9);
            EventStack[EventCursor].B := tileBlueGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 8), 35): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 8);
            EventStack[EventCursor].B := tileBlueGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 7), 35): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 7);
            EventStack[EventCursor].B := tileBlueGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 3), 34): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 3);
            EventStack[EventCursor].B := tileRedGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 2), 34): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 2);
            EventStack[EventCursor].B := tileRedGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (1 * 11 + 1), 34): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (1 * BoardWidth + 1);
            EventStack[EventCursor].B := tileRedGem;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 5), 23): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 5);
            EventStack[EventCursor].B := tileFairy;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            if (Hero.music_track <> 0) then
            begin
              { PushCommand(0, 0, 0): wait. }
              Inc(EventCursor);
              EventStack[EventCursor].Opcode := Ord(evWait);
              EventStack[EventCursor].A := 0;
              EventStack[EventCursor].B := 0;
              { PushCommand(1, 6, 0): stop music. }
              Inc(EventCursor);
              EventStack[EventCursor].Opcode := Ord(evSound);
              EventStack[EventCursor].A := 6;
              EventStack[EventCursor].B := 0;
            end;
          end;
        end;
    end;
    41: { Defeat both magicians to reveal the descent wing and change the central walls. }
    begin
      if ((Maps[Hero.floor, 2 + 1 * BoardWidth + 1] + Maps[Hero.floor, 2 + 1 * BoardWidth + 9])
          = 12) then
        case Hero.Word616 of
          0:
          begin
            Hero.Word616 := 1;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (4 * 11 + 5), 45): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (4 * BoardWidth + 5);
            EventStack[EventCursor].B := tileDescentWing;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (6 * 11 + 6), 6): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (6 * BoardWidth + 6);
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (6 * 11 + 4), 6): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (6 * BoardWidth + 4);
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 6), 8): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 6);
            EventStack[EventCursor].B := tileWall;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 5), 8): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 5);
            EventStack[EventCursor].B := tileWall;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, (5 * 11 + 4), 8): change tile and redraw. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := (5 * BoardWidth + 4);
            EventStack[EventCursor].B := tileWall;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0): play sound effect A. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0): wait. }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
          end;
        end;
    end;
    44: { Defeat the guard pair to open their gate. }
    begin
      if (((Maps[Hero.floor, 2 + 8 * BoardWidth + 4] + Maps[Hero.floor, 2 + 8 * BoardWidth + 6])
              + Maps[Hero.floor, 2 + 7 * BoardWidth + 5])
          = 16) then
      begin
        { PushCommand(13, (7 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    45: { Each guard pair opens its neighboring gate. }
    begin
      if (((Maps[Hero.floor, 2 + 8 * BoardWidth + 4] + Maps[Hero.floor, 2 + 10 * BoardWidth + 4])
              + Maps[Hero.floor, 2 + 9 * BoardWidth + 3])
          = 16) then
      begin
        { PushCommand(13, (9 * 11 + 3), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (9 * BoardWidth + 3);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 8 * BoardWidth + 7] + Maps[Hero.floor, 2 + 10 * BoardWidth + 7])
              + Maps[Hero.floor, 2 + 9 * BoardWidth + 6])
          = 16) then
      begin
        { PushCommand(13, (9 * 11 + 6), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (9 * BoardWidth + 6);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    48: { Defeat the corner sorcerer to open the lower gate. }
    begin
      if ((Maps[Hero.floor, 2 + 0 * BoardWidth + 0] + Maps[Hero.floor, 2 + 7 * BoardWidth + 7])
          = 10) then
      begin
        { PushCommand(13, (7 * 11 + 7), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (7 * BoardWidth + 7);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
    end;
    49: { Open outer guard gates, apply the sealing puzzle, then award decoy-Zeno loot. }
    begin
      if (((Maps[Hero.floor, 2 + 9 * BoardWidth + 4] + Maps[Hero.floor, 2 + 9 * BoardWidth + 6])
              + Maps[Hero.floor, 2 + 8 * BoardWidth + 5])
          = 16) then
      begin
        { PushCommand(13, (8 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (8 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if ((((Maps[Hero.floor, 2 + 7 * BoardWidth + 4] + Maps[Hero.floor, 2 + 7 * BoardWidth + 6])
                  + Maps[Hero.floor, 2 + 6 * BoardWidth + 5])
              + Maps[Hero.floor, 2 + 5 * BoardWidth + 5])
          = 23) then
      begin
        { PushCommand(13, (6 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      { Four cardinal sorcerers gone with the corner sorcerers intact seals Zeno to one-tenth strength. }
      if (((((Maps[Hero.floor, 2 + 1 * BoardWidth + 5] + Maps[Hero.floor, 2 + 2 * BoardWidth + 4])
                      + Maps[Hero.floor, 2 + 2 * BoardWidth + 6])
                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 5])
              = 24)
          and ((((Maps[Hero.floor, 2 + 1 * BoardWidth + 4]
                          + Maps[Hero.floor, 2 + 1 * BoardWidth + 6])
                      + Maps[Hero.floor, 2 + 3 * BoardWidth + 4])
                  + Maps[Hero.floor, 2 + 3 * BoardWidth + 6])
              = 372)) then
      begin
        if (Hero.zeno_sealed = 0) then
        begin
          Hero.zeno_sealed := 1;
          Monsters[15].HP := (Monsters[15].HP div 10);
          Monsters[15].attack := (Monsters[15].attack div 10);
          Monsters[15].defense := (Monsters[15].defense div 10);
        end;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 5, 0): resume selected music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 5;
          EventStack[EventCursor].B := 0;
        end;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 46, 0): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechZenoDefeated;
        EventStack[EventCursor].B := 0;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 6, 0): stop music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 6;
          EventStack[EventCursor].B := 0;
        end;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      if (((Maps[Hero.floor, 2 + 2 * BoardWidth + 5] + Maps[Hero.floor, 2 + 6 * BoardWidth + 5])
              + Maps[Hero.floor, 2 + 5 * BoardWidth + 5])
          = 16) then
      begin
        { Boss loot replaces any pending sealing dialogue queued above. }
        EventCursor := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (1 * 11 + 6), 46): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (1 * BoardWidth + 6);
        EventStack[EventCursor].B := tileDragonSlayer;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (1 * 11 + 4), 30): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (1 * BoardWidth + 4);
        EventStack[EventCursor].B := tileRedKey;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 9), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 9);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 8), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 8);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 7), 35): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 7);
        EventStack[EventCursor].B := tileBlueGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 3), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 3);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 2), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 2);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 1), 34): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 1);
        EventStack[EventCursor].B := tileRedGem;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 6), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 6);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 5), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 5);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (4 * 11 + 4), 33): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (4 * BoardWidth + 4);
        EventStack[EventCursor].B := tileBluePotion;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (1 * 11 + 5), 23): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (1 * BoardWidth + 5);
        EventStack[EventCursor].B := tileFairy;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, (6 * 11 + 5), 4): door/wall animation frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := (6 * BoardWidth + 5);
        EventStack[EventCursor].B := 4;
        doorstackin;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(6, (3 * 11 + 6), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 6);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(6, (3 * 11 + 4), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (3 * BoardWidth + 4);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(6, (1 * 11 + 6), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (1 * BoardWidth + 6);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(6, (1 * 11 + 4), 6): change tile and redraw. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSetTile);
        EventStack[EventCursor].A := (1 * BoardWidth + 4);
        EventStack[EventCursor].B := tileRoad;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        if (Hero.music_track <> 0) then
        begin
          { PushCommand(0, 0, 0): wait. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 6, 0): stop music. }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 6;
          EventStack[EventCursor].B := 0;
        end;
      end;
    end;
    50: { Finish the later-cycle Zeno battle with the ending fade and next-cycle reset. }
    begin
      if (Hero.cycle_factor_minus_one <> 0) then
      begin
        timer2on;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 6, 0): advance cycle and restart. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 6;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 247): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 247;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 246): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 246;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 245): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 245;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 244): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 244;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 243): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 243;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 242): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 242;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 241): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 241;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 240): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 240;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 239): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 239;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 238): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 238;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 237): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 237;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 236): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 236;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 235): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 235;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 234): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 234;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 233): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 233;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 2, 0): wait / paired animation operands. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 12, 232): screen fade/raster frame. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 12;
        EventStack[EventCursor].B := 232;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0): play sound effect A. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 15, 0): capture the screen for the next effect. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 15;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 14, 0): hide game panels. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 14;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(11, 13, 0): hide hero and stop map animation. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSceneAction);
        EventStack[EventCursor].A := 13;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(2, 140, 0): refresh status/message. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := 140;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0): wait. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(10, 62, 99): story dialogue. }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDialogue);
        EventStack[EventCursor].A := speechBacksideZenoDefeated;
        EventStack[EventCursor].B := 99;
        timer2on;
      end;
    end;
  end;
end;
