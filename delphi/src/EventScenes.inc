{ Floor arrival scenes and rewards unlocked after combat. Scene commands are
  pushed in reverse playback order. }

procedure TTSW10.ichicheck; { Arrival triggers. $0046CB1C }
begin
  if ((Hero.floor >= 10) and (Hero.floor < 50)) then
  begin
    case Hero.floor of
      10: { First visit: skeleton march and arena gates. Return visit: thief escort. }
      begin
        if (Hero.Word424 = 0) then
        begin
          if (Hero.music_track <> 0) then
          begin
            Hero.music_track := 15;
            PushEvent(0, 0, 0);
            PushEvent(1, 5, 0);
          end;
          PushEvent(13, (3 * 11 + 7), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(13, (3 * 11 + 3), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          EventWaits(5);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 8), (3 * 11 + 7));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 9), (3 * 11 + 8));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 10), (3 * 11 + 9));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 10), (3 * 11 + 10));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 2), (3 * 11 + 3));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 1), (3 * 11 + 2));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 0), (3 * 11 + 1));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 0), (3 * 11 + 0));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 6), (4 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 8), (3 * 11 + 7));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 9), (3 * 11 + 8));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 9), (3 * 11 + 9));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 2), (3 * 11 + 3));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 1), (3 * 11 + 2));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 1), (3 * 11 + 1));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (4 * 11 + 6), (5 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 6), (4 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 8), (3 * 11 + 7));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 8), (3 * 11 + 8));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (4 * 11 + 4), (5 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 2), (3 * 11 + 3));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 2), (3 * 11 + 2));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 6), (3 * 11 + 5));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 8), (3 * 11 + 7));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 9), (3 * 11 + 8));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (5 * 11 + 4), (5 * 11 + 5));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (4 * 11 + 4), (5 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 2), (3 * 11 + 3));
          EventWaits(3);
          PushEvent(1, 4, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 1), (3 * 11 + 2));
          PushEvent(13, (3 * 11 + 7), 4);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(13, (3 * 11 + 3), 4);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(13, (6 * 11 + 5), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(13, (2 * 11 + 5), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (1 * 11 + 5), (0 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(12, (2 * 11 + 5), (1 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(12, (3 * 11 + 5), (2 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(6, (5 * 11 + 6), 6);
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          PushEvent(0, 0, 0);
          PushEvent(6, (5 * 11 + 4), 6);
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          PushEvent(0, 0, 0);
          PushEvent(10, 13, 0);
          if (Hero.music_track <> 0) then
          begin
            PushEvent(0, 0, 0);
            PushEvent(1, 6, 0);
          end;
        end
        else
        begin
          PushEvent(0, 0, 0);
          PushEvent(6, (9 * 11 + 5), 6);
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          PushEvent(0, 0, 0);
          PushEvent(10, 17, 0);
          PushEvent(0, 0, 0);
          PushEvent(12, (9 * 11 + 4), (9 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(12, (10 * 11 + 4), (9 * 11 + 4));
          PushEvent(0, 0, 0);
          PushEvent(12, (10 * 11 + 3), (10 * 11 + 4));
          PushEvent(0, 0, 0);
          PushEvent(12, (10 * 11 + 2), (10 * 11 + 3));
          PushEvent(0, 0, 0);
          PushEvent(12, (9 * 11 + 2), (10 * 11 + 2));
          PushEvent(0, 0, 0);
          PushEvent(12, (8 * 11 + 2), (9 * 11 + 2));
          PushEvent(0, 0, 0);
          PushEvent(12, (7 * 11 + 2), (8 * 11 + 2));
          PushEvent(0, 0, 0);
          PushEvent(12, (7 * 11 + 1), (7 * 11 + 2));
          PushEvent(0, 0, 0);
          PushEvent(12, (7 * 11 + 0), (7 * 11 + 1));
          PushEvent(0, 0, 0);
          PushEvent(12, (8 * 11 + 0), (7 * 11 + 0));
          PushEvent(0, 0, 0);
          PushEvent(12, (9 * 11 + 0), (8 * 11 + 0));
          PushEvent(0, 0, 0);
          PushEvent(6, (9 * 11 + 0), 21);
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
        end;
      end;
      15: { Enter the octopus chamber and close its gate. }
      begin
        PushEvent(13, (8 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 5);
        EventWaits(2);
      end;
      20: { Clear the central chamber and animate the vampire transformation. }
      begin
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 5, 0);
        end;
        Maps[Hero.floor, 2 + 4 * 11 + 4] := 6;
        Maps[Hero.floor, 2 + 4 * 11 + 5] := 6;
        Maps[Hero.floor, 2 + 4 * 11 + 6] := 6;
        Maps[Hero.floor, 2 + 5 * 11 + 4] := 6;
        Maps[Hero.floor, 2 + 5 * 11 + 6] := 6;
        Maps[Hero.floor, 2 + 6 * 11 + 4] := 6;
        Maps[Hero.floor, 2 + 6 * 11 + 5] := 6;
        Maps[Hero.floor, 2 + 6 * 11 + 6] := 6;
        Maps[Hero.floor, 2 + 5 * 11 + 5] := 95;
        PushEvent(0, 0, 0);
        PushEvent(10, 20, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 32);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 31);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 30);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 29);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 28);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 27);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 26);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 25);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 24);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 23);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 22);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 21);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 20);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 19);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 18);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 17);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 16);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 15);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 14);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 13);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 12);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 11);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 10);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 9);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 8);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 7);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 6);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 5);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 4);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 3);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 2);
        PushEvent(0, 0, 0);
        PushEvent(11, 4, 1);
        PushEvent(0, 0, 0);
        PushEvent(1, 8, 0);
        PushEvent(13, (8 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
      24: { Enter the time gate, travel to 50F, then reveal the true Zeno. }
      begin
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
          PushEvent(0, 0, 0);
          PushEvent(11, 10, 71);
          EventWaits(3);
          PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          EventWaits(3);
          PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
        end;
        EventWaits(3);
        PushEvent(10, 57, 0);
        EventWaits(5);
        PushEvent(10, 56, 0);
        EventWaits(5);
        PushEvent(10, 55, 0);
        EventWaits(5);
        PushEvent(10, 54, 0);
        EventWaits(5);
        PushEvent(10, 53, 0);
        EventWaits(5);
        PushEvent(10, 52, 0);
        EventWaits(5);
        PushEvent(10, 51, 0);
        EventWaits(5);
        PushEvent(10, 50, 0);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(15, 0, 0);
        end;
        PushEvent(17, (4 * 11 + 5), 91);
        EventWaits(6);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 182);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 181);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 180);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 179);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 178);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 177);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 176);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 175);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 174);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 173);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 172);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 171);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 170);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 169);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 168);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 167);
        PushEvent(0, 21, 91);
        PushEvent(9, 49, 166);
        PushEvent(0, 0, 0);
        PushEvent(1, 7, 0);
        EventWaits(7);
        PushEvent(10, 49, 0);
        EventWaits(5);
        PushEvent(10, 48, 0);
        EventWaits(11);
        PushEvent(11, 11, 50);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 49);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 48);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 47);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 46);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 45);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 44);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 43);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 42);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 41);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 40);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 39);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 38);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 37);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 36);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 32);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 31);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 28);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 27);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 26);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 11, 25);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
      25: { Introduce the Great Magic Master and seal the chamber. }
      begin
        PushEvent(0, 0, 0);
        PushEvent(10, 23, 0);
        PushEvent(13, (9 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      30: { Seal both gates of the guard chamber. }
      begin
        PushEvent(13, (6 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (3 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      32: { Stair arrival: Golden Knight approach, dialogue and forced battle. }
      begin
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 104);
        EventWaits(3);
        PushEvent(12, (8 * 11 + 5), (9 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (7 * 11 + 5), (8 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (6 * 11 + 5), (7 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        EventWaits(3);
        PushEvent(10, 30, 0);
        EventWaits(7);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (2 * 11 + 5), (3 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (1 * 11 + 5), (2 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 5), (1 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 6), (0 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 7), (0 * 11 + 6));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 8), (0 * 11 + 7));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 9), (0 * 11 + 8));
        EventWaits(3);
        PushEvent(6, (0 * 11 + 9), 133);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(10);
      end;
      33: { Wrong approach at cell 107 raises a wall; otherwise seal the guard room. }
      begin
        if (((Hero.y * 11) + Hero.x) = 107) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(2, 114, 0);
          PushEvent(0, 0, 0);
          PushEvent(13, (9 * 11 + 7), 8);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          EventWaits(2);
        end
        else
        begin
          PushEvent(13, (7 * 11 + 9), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          PushEvent(13, (3 * 11 + 9), 5);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          EventWaits(2);
        end;
      end;
      38: { The blocked shortcut raises a wall. }
      begin
        PushEvent(0, 0, 0);
        PushEvent(2, 114, 0);
        PushEvent(0, 0, 0);
        PushEvent(13, (4 * 11 + 1), 8);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      40: { Seal the Golden Knight arena and stage the thirteen-fight gauntlet. }
      begin
        if (Maps[Hero.floor, 2 + 3 * 11 + 4] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 4] := 141;
        end;
        if (Maps[Hero.floor, 2 + 3 * 11 + 3] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 3] := 141;
        end;
        if (Maps[Hero.floor, 2 + 3 * 11 + 2] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 2] := 141;
        end;
        if (Maps[Hero.floor, 2 + 3 * 11 + 6] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 6] := 139;
        end;
        if (Maps[Hero.floor, 2 + 3 * 11 + 7] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 7] := 139;
        end;
        if (Maps[Hero.floor, 2 + 3 * 11 + 8] = 6) then
        begin
          Maps[Hero.floor, 2 + 3 * 11 + 8] := 139;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 3] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 3] := 137;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 2] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 2] := 137;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 1] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 1] := 137;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 7] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 7] := 135;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 8] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 8] := 135;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 9] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 9] := 135;
        end;
        if (Maps[Hero.floor, 2 + 1 * 11 + 5] = 6) then
        begin
          Maps[Hero.floor, 2 + 1 * 11 + 5] := 133;
        end;
        PushEvent(0, 0, 0);
        PushEvent(11, 5, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 5), 6);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 5), (1 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (3 * 11 + 5), (2 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (4 * 11 + 5), (3 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (5 * 11 + 5), (4 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (6 * 11 + 5), (5 * 11 + 5));
        EventWaits(6);
        PushEvent(17, (6 * 11 + 5), 133);
        PushEvent(10, 39, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (0 * 11 + 5), 11);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(3);
        PushEvent(2, 4, 0);
        PushEvent(0, 0, 0);
        PushEvent(13, (7 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(3);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 5), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 5), (2 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(10, 38, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 6), (3 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 7), (2 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 7), (2 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 8), (1 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 9), (1 * 11 + 8));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 6), (3 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 7), (2 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 7), (2 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 8), (1 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 6), (3 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 7), (2 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 7), (2 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(10, 37, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 4), (3 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 3), (2 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 3), (2 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 2), (1 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 1), (1 * 11 + 2));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 4), (3 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 3), (2 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 3), (2 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 2), (1 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 5), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (3 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 4), (3 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (2 * 11 + 3), (2 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (1 * 11 + 3), (2 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(10, 36, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 6), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (4 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 8), (3 * 11 + 7));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 6), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (4 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 7), (3 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 6), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 6), (4 * 11 + 6));
        PushEvent(0, 0, 0);
        PushEvent(10, 35, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 4), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 2), (3 * 11 + 3));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 4), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 3), (3 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(11, 10, 71);
        PushEvent(0, 0, 0);
        PushEvent(12, (5 * 11 + 5), (6 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 5), (5 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (4 * 11 + 4), (4 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(12, (3 * 11 + 4), (4 * 11 + 4));
        PushEvent(0, 0, 0);
        PushEvent(10, 34, 0);
        PushEvent(13, (7 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      42: { Zeno arrives, summons four guards and executes the Golden Knight. }
      begin
        Maps[35, 2 + 9 * 11 + 4] := 6;
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 5), 6);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(7);
        PushEvent(10, 44, 0);
        EventWaits(6);
        PushEvent(6, (7 * 11 + 6), 6);
        PushEvent(6, (7 * 11 + 4), 6);
        PushEvent(6, (8 * 11 + 5), 6);
        PushEvent(6, (6 * 11 + 5), 6);
        EventWaits(7);
        PushEvent(6, (7 * 11 + 5), 6);
        EventWaits(4);
        PushEvent(0, Maps[Hero.floor, 2 + 7 * 11 + 5], 184);
        PushEvent(9, 82, 183);
        PushEvent(0, 0, 0);
        PushEvent(1, 4, 0);
        PushEvent(0, 0, 0);
        PushEvent(10, 43, 0);
        ScratchIndex := 71;
        NeighborIndex := 93;
        EventSummonFour(Self, ScratchIndex, NeighborIndex, 81, 83);
        EventWaits(5);
        PushEvent(10, 42, 0);
        EventWaits(5);
        PushEvent(10, 41, 0);
        ScratchIndex := 60;
        EventSummon(Self, ScratchIndex, 91);
        EventWaits(6);
      end;
      43: { The upper-passage sorcerer retreats and raises two walls. }
      begin
        if (Maps[Hero.floor, 2 + 0 * 11 + 8] = 93) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(13, (0 * 11 + 9), 8);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          EventWaits(3);
          PushEvent(13, (0 * 11 + 6), 8);
          doorstackin;
          PushEvent(0, 0, 0);
          PushEvent(1, 1, 0);
          EventWaits(5);
          PushEvent(12, (0 * 11 + 9), (0 * 11 + 10));
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          EventWaits(5);
          PushEvent(12, (0 * 11 + 8), (0 * 11 + 9));
          PushEvent(0, 0, 0);
          PushEvent(1, 2, 0);
          EventWaits(2);
        end
        else
        begin
          PushEvent(0, 0, 0);
        end;
      end;
      48: { Reveal the sorcerer in the northwest corner. }
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (0 * 11 + 0), 93);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(2);
      end;
      49: { Seal the decoy Zeno chamber and summon Zeno with eight sorcerer guards. }
      begin
        PushEvent(0, 0, 0);
        PushEvent(11, 3, 0);
        PushEvent(0, 0, 0);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 5, 0);
        end;
        PushEvent(0, 0, 0);
        PushEvent(10, 45, 0);
        EventWaits(3);
        PushEvent(11, 2, 0);
        PushEvent(13, (6 * 11 + 5), 5);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
    end;
  end;
  Exit;
end;

procedure TTSW10.moncheck; { Guard gates and boss rewards after combat. $004664E4 }
var
  sum: Longint;
begin
  sum := 0;
  case Hero.floor of
    2: { Defeat both prison guards to open the six cell gates. }
    begin
      sum := Maps[Hero.floor, 2 + 4 * 11 + 4];
      if (((Maps[Hero.floor, 2 + 1 * 11 + 5] + Maps[Hero.floor, 2 + 1 * 11 + 7]) + sum) = 17) then
      begin
        PushEvent(13, (10 * 11 + 8), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (10 * 11 + 4), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (7 * 11 + 8), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (7 * 11 + 4), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (4 * 11 + 8), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (4 * 11 + 4), 6);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    8: { Defeat the guard pair to open their gate. }
    begin
      sum := Maps[Hero.floor, 2 + 3 * 11 + 9];
      if (((Maps[Hero.floor, 2 + 4 * 11 + 8] + Maps[Hero.floor, 2 + 4 * 11 + 10]) + sum) = 16) then
      begin
        PushEvent(13, (3 * 11 + 9), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    10: { Skeleton guards unlock the boss; clearing the arena unlocks stairs and loot. }
    begin
      if (((((((((Maps[Hero.floor, 2 + 3 * 11 + 4] + Maps[Hero.floor, 2 + 3 * 11 + 5])
                                      + Maps[Hero.floor, 2 + 3 * 11 + 6])
                                  + Maps[Hero.floor, 2 + 4 * 11 + 4])
                              + Maps[Hero.floor, 2 + 4 * 11 + 6])
                          + Maps[Hero.floor, 2 + 5 * 11 + 4])
                      + Maps[Hero.floor, 2 + 5 * 11 + 5])
                  + Maps[Hero.floor, 2 + 5 * 11 + 6])
              + Maps[Hero.floor, 2 + 2 * 11 + 5])
          = 52) then
      begin
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 5, 0);
        end;
        PushEvent(13, (2 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(3);
        PushEvent(10, 14, 0);
        EventWaits(2);
      end;
      sum := Maps[Hero.floor, 2 + 3 * 11 + 3];
      if ((((Maps[Hero.floor, 2 + 0 * 11 + 5] + Maps[Hero.floor, 2 + 6 * 11 + 5])
                  + Maps[Hero.floor, 2 + 3 * 11 + 7])
              + sum)
          = 18) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (8 * 11 + 5), 7);
        PushEvent(0, 0, 0);
        PushEvent(6, (10 * 11 + 5), 11);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 10), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 9), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 8), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 2), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 1), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 0), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 10), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 9), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 8), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 2), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 1), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 0), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 5), 23);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (6 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (3 * 11 + 7), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (3 * 11 + 3), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(3);
        PushEvent(10, 15, 0);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
    end;
    11: { Defeat the guard pair to open their gate. }
    begin
      sum := Maps[Hero.floor, 2 + 3 * 11 + 1];
      if (((Maps[Hero.floor, 2 + 4 * 11 + 0] + Maps[Hero.floor, 2 + 4 * 11 + 2]) + sum) = 16) then
      begin
        PushEvent(13, (3 * 11 + 1), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    14: { Defeat all three guards to reveal a red key. }
    begin
      sum := Maps[Hero.floor, 2 + 2 * 11 + 0];
      if ((((Maps[Hero.floor, 2 + 0 * 11 + 0] + Maps[Hero.floor, 2 + 0 * 11 + 2])
                  + Maps[Hero.floor, 2 + 1 * 11 + 1])
              + sum)
          = 26) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (2 * 11 + 0), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(2);
      end;
    end;
    15: { Defeat the octopus to reveal the mattock and reopen the chamber. }
    begin
      sum :=
          ((Maps[Hero.floor, 2 + 5 * 11 + 5] + Maps[Hero.floor, 2 + 2 * 11 + 5])
              + Maps[Hero.floor, 2 + 8 * 11 + 5]);
      if (sum = 14) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 5), 41);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (8 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (2 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    17: { Each of the four guard pairs opens its own gate. }
    begin
      if (((Maps[Hero.floor, 2 + 4 * 11 + 8] + Maps[Hero.floor, 2 + 4 * 11 + 10])
              + Maps[Hero.floor, 2 + 3 * 11 + 9])
          = 16) then
      begin
        PushEvent(13, (3 * 11 + 9), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      if (((Maps[Hero.floor, 2 + 7 * 11 + 8] + Maps[Hero.floor, 2 + 7 * 11 + 10])
              + Maps[Hero.floor, 2 + 6 * 11 + 9])
          = 16) then
      begin
        PushEvent(13, (6 * 11 + 9), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      if (((Maps[Hero.floor, 2 + 4 * 11 + 0] + Maps[Hero.floor, 2 + 4 * 11 + 2])
              + Maps[Hero.floor, 2 + 3 * 11 + 1])
          = 16) then
      begin
        PushEvent(13, (3 * 11 + 1), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      sum :=
          ((Maps[Hero.floor, 2 + 7 * 11 + 0] + Maps[Hero.floor, 2 + 7 * 11 + 2])
              + Maps[Hero.floor, 2 + 6 * 11 + 1]);
      if (sum = 16) then
      begin
        PushEvent(13, (6 * 11 + 1), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    20: { Defeat the vampire to reveal the fairy, stairs and chamber loot. }
    begin
      sum :=
          ((((((((((Maps[Hero.floor, 2 + 4 * 11 + 4] + Maps[Hero.floor, 2 + 4 * 11 + 5])
                                              + Maps[Hero.floor, 2 + 4 * 11 + 6])
                                          + Maps[Hero.floor, 2 + 5 * 11 + 4])
                                      + Maps[Hero.floor, 2 + 5 * 11 + 6])
                                  + Maps[Hero.floor, 2 + 6 * 11 + 4])
                              + Maps[Hero.floor, 2 + 6 * 11 + 5])
                          + Maps[Hero.floor, 2 + 6 * 11 + 6])
                      + Maps[Hero.floor, 2 + 5 * 11 + 5])
                  + Maps[Hero.floor, 2 + 2 * 11 + 5])
              + Maps[Hero.floor, 2 + 8 * 11 + 5]);
      if (sum = 62) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (0 * 11 + 5), 11);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 6), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 5), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 4), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 6), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 5), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 4), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 7), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 7), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 7), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 3), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 3), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 3), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 5), 23);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
        PushEvent(0, 0, 0);
        PushEvent(10, 21, 0);
        PushEvent(13, (8 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (2 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    25: { Defeat the Great Magic Master to reveal the fairy and red keys. }
    begin
      sum := (Maps[Hero.floor, 2 + 5 * 11 + 5] + Maps[Hero.floor, 2 + 9 * 11 + 5]);
      if (sum = 10) then
      begin
        if (Hero.Word464 = 1) then
        begin
          { The time-gate dialogue also prepares the route through 24F. }
          Maps[24, 2 + 0 * 11 + 4] := 8;
          Maps[24, 2 + 0 * 11 + 6] := 8;
          Maps[24, 2 + 1 * 11 + 5] := 6;
          Maps[24, 2 + 2 * 11 + 5] := 6;
          Maps[24, 2 + 3 * 11 + 5] := 6;
          Maps[24, 2 + 0 * 11 + 5] := 7;
        end;
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 7), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 6), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 5), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 4), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (7 * 11 + 3), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 5), 23);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (9 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    30: { Clear the guard line to reveal stairs and reopen the chamber. }
    begin
      sum :=
          (((((((Maps[Hero.floor, 2 + 4 * 11 + 2] + Maps[Hero.floor, 2 + 4 * 11 + 3])
                                  + Maps[Hero.floor, 2 + 4 * 11 + 4])
                              + Maps[Hero.floor, 2 + 4 * 11 + 6])
                          + Maps[Hero.floor, 2 + 4 * 11 + 7])
                      + Maps[Hero.floor, 2 + 4 * 11 + 8])
                  + Maps[Hero.floor, 2 + 3 * 11 + 5])
              + Maps[Hero.floor, 2 + 6 * 11 + 5]);
      if (sum = 44) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(6, (0 * 11 + 5), 11);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (6 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (3 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    32: { Open the paired-guard gate; the Golden Knight defeat advances the thief story. }
    begin
      if (((Maps[Hero.floor, 2 + 9 * 11 + 0] + Maps[Hero.floor, 2 + 9 * 11 + 2])
              + Maps[Hero.floor, 2 + 8 * 11 + 1])
          = 16) then
      begin
        PushEvent(13, (8 * 11 + 1), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      sum := ((Maps[Hero.floor, 2 + 5 * 11 + 5] + Hero.Word480) + Hero.Word484);
      if (sum = 7) then
      begin
        Maps[29, 2 + 1 * 11 + 6] := 6;
        Maps[2, 2 + 10 * 11 + 10] := 21;
        PushEvent(0, 0, 0);
        PushEvent(6, (0 * 11 + 9), 6);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(3);
        PushEvent(12, (0 * 11 + 8), (0 * 11 + 9));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 7), (0 * 11 + 8));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 6), (0 * 11 + 7));
        EventWaits(3);
        PushEvent(12, (0 * 11 + 5), (0 * 11 + 6));
        EventWaits(3);
        PushEvent(12, (1 * 11 + 5), (0 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (2 * 11 + 5), (1 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (3 * 11 + 5), (2 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (4 * 11 + 5), (3 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (5 * 11 + 5), (4 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (6 * 11 + 5), (5 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (7 * 11 + 5), (6 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (8 * 11 + 5), (7 * 11 + 5));
        EventWaits(3);
        PushEvent(12, (9 * 11 + 5), (8 * 11 + 5));
        PushEvent(0, 0, 0);
        PushEvent(17, (9 * 11 + 5), 133);
        EventWaits(5);
        PushEvent(10, 31, 0);
        EventWaits(2);
      end;
    end;
    33: { Defeat all four guards to reopen the chamber gates. }
    begin
      sum :=
          (((((Maps[Hero.floor, 2 + 4 * 11 + 8] + Maps[Hero.floor, 2 + 4 * 11 + 10])
                          + Maps[Hero.floor, 2 + 6 * 11 + 8])
                      + Maps[Hero.floor, 2 + 6 * 11 + 10])
                  + Maps[Hero.floor, 2 + 3 * 11 + 9])
              + Maps[Hero.floor, 2 + 7 * 11 + 9]);
      if (sum = 32) then
      begin
        PushEvent(13, (7 * 11 + 9), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(13, (3 * 11 + 9), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    34: { Defeat all eight guards to reveal the key cache once. }
    begin
      sum :=
          (((((((Maps[Hero.floor, 2 + 3 * 11 + 4] + Maps[Hero.floor, 2 + 3 * 11 + 6])
                                  + Maps[Hero.floor, 2 + 3 * 11 + 8])
                              + Maps[Hero.floor, 2 + 3 * 11 + 10])
                          + Maps[Hero.floor, 2 + 7 * 11 + 4])
                      + Maps[Hero.floor, 2 + 7 * 11 + 6])
                  + Maps[Hero.floor, 2 + 7 * 11 + 8])
              + Maps[Hero.floor, 2 + 7 * 11 + 10]);
      if ((sum = 48) and (Hero.Word592 = 0)) then
      begin
        Hero.Word592 := 1;
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 2), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 0), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 2), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 0), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 1), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(2);
      end;
    end;
    35: { Defeat the dragon to reveal the snow crystal and potions once. }
    begin
      sum := (Maps[Hero.floor, 2 + 6 * 11 + 5] + Maps[Hero.floor, 2 + 2 * 11 + 5]);
      if ((sum = 10) and (Hero.Word596 = 0)) then
      begin
        Hero.Word596 := 1;
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 6), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 5), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 4), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 5), 47);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (2 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    38: { Clearing the two guards reveals a secret wall. }
    begin
      sum := (Maps[Hero.floor, 2 + 9 * 11 + 0] + Maps[Hero.floor, 2 + 9 * 11 + 2]);
      if (sum = 12) then
      begin
        Maps[Hero.floor, 2 + 8 * 11 + 1] := 9;
      end;
    end;
    40: { Defeat the Golden Knight to reveal the fairy and arena loot once. }
    begin
      sum := (Maps[Hero.floor, 2 + 1 * 11 + 5] + Maps[Hero.floor, 2 + 0 * 11 + 5]);
      if ((sum = 17) and (Hero.Word600 = 0)) then
      begin
        Hero.Word600 := 1;
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 8), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 7), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 6), 29);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 4), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 3), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 2), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 9), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 8), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 7), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 3), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 2), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 1), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 5), 23);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
    end;
    41: { Defeat both magicians to reveal the descent wing and change the central walls. }
    begin
      sum := (Maps[Hero.floor, 2 + 1 * 11 + 1] + Maps[Hero.floor, 2 + 1 * 11 + 9]);
      if ((sum = 12) and (Hero.Word616 = 0)) then
      begin
        Hero.Word616 := 1;
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 5), 45);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 6), 6);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (6 * 11 + 4), 6);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 6), 8);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 5), 8);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (5 * 11 + 4), 8);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    44: { Defeat the guard pair to open their gate. }
    begin
      sum :=
          ((Maps[Hero.floor, 2 + 8 * 11 + 4] + Maps[Hero.floor, 2 + 8 * 11 + 6])
              + Maps[Hero.floor, 2 + 7 * 11 + 5]);
      if (sum = 16) then
      begin
        PushEvent(13, (7 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    45: { Each guard pair opens its neighboring gate. }
    begin
      if (((Maps[Hero.floor, 2 + 8 * 11 + 4] + Maps[Hero.floor, 2 + 10 * 11 + 4])
              + Maps[Hero.floor, 2 + 9 * 11 + 3])
          = 16) then
      begin
        PushEvent(13, (9 * 11 + 3), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      sum :=
          ((Maps[Hero.floor, 2 + 8 * 11 + 7] + Maps[Hero.floor, 2 + 10 * 11 + 7])
              + Maps[Hero.floor, 2 + 9 * 11 + 6]);
      if (sum = 16) then
      begin
        PushEvent(13, (9 * 11 + 6), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    48: { Defeat the corner sorcerer to open the lower gate. }
    begin
      sum := (Maps[Hero.floor, 2 + 0 * 11 + 0] + Maps[Hero.floor, 2 + 7 * 11 + 7]);
      if (sum = 10) then
      begin
        PushEvent(13, (7 * 11 + 7), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
    end;
    49: { Open outer guard gates, apply the sealing puzzle, then award decoy-Zeno loot. }
    begin
      if (((Maps[Hero.floor, 2 + 9 * 11 + 4] + Maps[Hero.floor, 2 + 9 * 11 + 6])
              + Maps[Hero.floor, 2 + 8 * 11 + 5])
          = 16) then
      begin
        PushEvent(13, (8 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      if ((((Maps[Hero.floor, 2 + 7 * 11 + 4] + Maps[Hero.floor, 2 + 7 * 11 + 6])
                  + Maps[Hero.floor, 2 + 6 * 11 + 5])
              + Maps[Hero.floor, 2 + 5 * 11 + 5])
          = 23) then
      begin
        PushEvent(13, (6 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        EventWaits(2);
      end;
      { Four cardinal sorcerers gone with the corner sorcerers intact seals Zeno to one-tenth strength. }
      if (((((Maps[Hero.floor, 2 + 1 * 11 + 5] + Maps[Hero.floor, 2 + 2 * 11 + 4])
                      + Maps[Hero.floor, 2 + 2 * 11 + 6])
                  + Maps[Hero.floor, 2 + 3 * 11 + 5])
              = 24)
          and ((((Maps[Hero.floor, 2 + 1 * 11 + 4] + Maps[Hero.floor, 2 + 1 * 11 + 6])
                      + Maps[Hero.floor, 2 + 3 * 11 + 4])
                  + Maps[Hero.floor, 2 + 3 * 11 + 6])
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
          PushEvent(0, 0, 0);
          PushEvent(1, 5, 0);
        end;
        PushEvent(0, 0, 0);
        PushEvent(10, 46, 0);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
        EventWaits(2);
      end;
      sum :=
          ((Maps[Hero.floor, 2 + 2 * 11 + 5] + Maps[Hero.floor, 2 + 6 * 11 + 5])
              + Maps[Hero.floor, 2 + 5 * 11 + 5]);
      if (sum = 16) then
      begin
        { Boss loot replaces any pending sealing dialogue queued above. }
        EventCursor := 0;
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 6), 46);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 4), 30);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 9), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 8), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 7), 35);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 3), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 2), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (3 * 11 + 1), 34);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 6), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 5), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (4 * 11 + 4), 33);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(0, 0, 0);
        PushEvent(6, (1 * 11 + 5), 23);
        PushEvent(0, 0, 0);
        PushEvent(1, 2, 0);
        PushEvent(13, (6 * 11 + 5), 4);
        doorstackin;
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(6, (3 * 11 + 6), 6);
        PushEvent(6, (3 * 11 + 4), 6);
        PushEvent(6, (1 * 11 + 6), 6);
        PushEvent(6, (1 * 11 + 4), 6);
        EventWaits(2);
        if (Hero.music_track <> 0) then
        begin
          PushEvent(0, 0, 0);
          PushEvent(1, 6, 0);
        end;
      end;
    end;
    50: { Finish the later-cycle Zeno battle with the ending fade and next-cycle reset. }
    begin
      if (Hero.cycle_factor_minus_one <> 0) then
      begin
        PushEvent(0, 0, 0);
        PushEvent(11, 6, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 247);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 246);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 245);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 244);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 243);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 242);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 241);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 240);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 239);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 238);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 237);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 236);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 235);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 234);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 233);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 2, 0);
        PushEvent(11, 12, 232);
        PushEvent(0, 0, 0);
        PushEvent(1, 1, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 15, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 14, 0);
        PushEvent(0, 0, 0);
        PushEvent(11, 13, 0);
        PushEvent(0, 0, 0);
        PushEvent(2, 140, 0);
        EventWaits(3);
        PushEvent(10, 62, 99);
      end;
    end;
  end;
  Exit;
end;
