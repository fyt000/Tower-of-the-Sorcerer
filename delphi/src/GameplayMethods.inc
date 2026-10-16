{ Movement, combat, shops and item interaction. Address comments identify
  the corresponding executable handlers. }
var
  GameplayItemChoice: Longint;

procedure GameplayRefresh(Form: TTSW10);
begin
  if (MapBitmap1 = nil) or (MapBitmap2 = nil) then
    Exit;
  Form.mhyouji;
  Form.yusyahyouji1;
  Form.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
end;

function GameplayText(Form: TTSW10; Index: Longint): string;
begin
  if (Index >= 0) and (Index < Form.ListBox2.Items.Count) then
    GameplayText := Form.ListBox2.Items[Index]
  else
    GameplayText := '';
end;

procedure GameplayMessage(Form: TTSW10; Index: Longint);
begin
  TileClass := Index;
  Form.disp;
end;

procedure GameplayDialogue(Form: TTSW10; Index, Stage: Longint);
begin
  Form.itemdel;
  DialogueStage := Stage;
  Form.RichEdit1.Text := GameplayText(Form, Index);
  Form.RichEdit1.Left := UiSpan + 8;
  Form.RichEdit1.Top := UiStep + 8;
  Form.RichEdit1.Width := Form.Image6.Width * BoardWidth - 16;
  Form.RichEdit1.Height := Form.Image6.Height * 6;
  Form.RichEdit1.Visible := True;
  Form.Button1.Left := Form.RichEdit1.Left + Form.RichEdit1.Width - Form.Button1.Width;
  Form.Button1.Top := Form.RichEdit1.Top + Form.RichEdit1.Height + 4;
  Form.Button1.Visible := True;
  Form.Button1.Enabled := True;
  if Form.Visible then
    Form.Button1.SetFocus;
end;

procedure TTSW10.obudameiji; { $0044FF0C; Orb deliberately ignores Cross/Slayer }
begin
  DamageMode := 0;
  if Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack >= 0 then
    DamageMode := 1
  else
  begin
    StrikeCount := 0;
    RemainingHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
    damecount;
    if Hero.defense - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) >= 0 then
      Damage := 0
    else
      Damage :=
          (Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense)
              * (StrikeCount - 1);
  end;
  case DamageMode of
    1: DamageText := ListBox2.Items[$B9];
    0: DamageText := ListBox2.Items[$B8] + ' ' + IntToStr(Damage);
  end;
end;

procedure TTSW10.dameiji; { $00450064 }
begin
  DamageMode := 0;
  if Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack >= 0 then
    DamageMode := 1
  else
  begin
    StrikeCount := 0;
    RemainingHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);

    case MonsterIndex of
      Ord(monsterGreenSlime)..Ord(monsterBigBat): damecount;
      Ord(monsterZombie)..Ord(monsterZombieKnight):
        if Hero.cross = 0 then
          damecount
        else
          damecount2;
      Ord(monsterRock)..Ord(monsterSorcerer): damecount;
      Ord(monsterVampire):
        if Hero.cross = 0 then
          damecount
        else
          damecount2;
      Ord(monsterOctopus): damecount;
      Ord(monsterDragon):
        if Hero.dragon_slayer = 0 then
          damecount
        else
          damecount2;
      Ord(monsterGoldenKnight)..Ord(monsterGateKeeperA): damecount;
    end;
    if Hero.defense - Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) >= 0 then
      Damage := 0
    else
      Damage :=
          (Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1) - Hero.defense)
              * (StrikeCount - 1);
  end;
  case DamageMode of
    1: DamageText := ListBox2.Items[$B9];
    0: DamageText := ListBox2.Items[$B8] + ' ' + IntToStr(Damage);
  end;
end;

procedure TTSW10.taisen; { $0044A480 }
var
  I: Longint;
begin
  case Maps[Hero.floor, ContactIndex + MapTileOffset] of
    tileGreenSlime..tileVampire:
      DoorOpened := (Maps[Hero.floor, ContactIndex + MapTileOffset] + 1) div 2 - 30 + 197;
    tileOctopusFirst..105: DoorOpened := 216;
    tileDragonFirst..123: DoorOpened := 217;
    132..tileGateKeeperA:
      DoorOpened := (Maps[Hero.floor, ContactIndex + MapTileOffset] + 1) div 2 - 46 + 197;
  end;
  NeighborIndex := DoorOpened - 198;
  MonsterIndex := NeighborIndex;
  monshyouji;
  if Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack < 0 then
  begin
    idou;
    Hero.Word48 := 1;
  end;
  NeighborIndex := MonsterIndex;
  BattleHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
  if Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1) - Hero.attack >= 0 then
  begin
    TileClass := 1;
    MessageText := ListBox2.Items[217];
    disp;
  end
  else
  begin
    dameiji;
    if Hero.hp <= Damage then
    begin
      { PushCommand(3, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDefeat);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;

      case MonsterIndex of
        Ord(monsterGreenSlime)..Ord(monsterBigBat): ydameiji;
        Ord(monsterZombie)..Ord(monsterZombieKnight):
          if Hero.cross = 0 then
            ydameiji
          else
            ydameiji2;
        Ord(monsterRock)..Ord(monsterSorcerer): ydameiji;
        Ord(monsterVampire):
          if Hero.cross = 0 then
            ydameiji
          else
            ydameiji2;
        Ord(monsterOctopus): ydameiji;
        Ord(monsterDragon):
          if Hero.dragon_slayer = 0 then
            ydameiji
          else
            ydameiji2;
        Ord(monsterGoldenKnight)..Ord(monsterGateKeeperA): ydameiji;
      end;
      for I := 1 to StrikeCount do
      begin
        ScratchIndex := I;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(4, ContactIndex, unchanged). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evEnemyAttack);
        EventStack[EventCursor].A := ContactIndex;
        if ScratchIndex = 1 then
          EventStack[EventCursor].B :=
              Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset]
        else
          EventStack[EventCursor].B := 184;
        { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], (Hero.facing - 1) * 8 + 257 - 66). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
        EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 257 - 66;
        { PushCommand(9, ContactIndex, (Hero.facing - 1) * 8 + 258 - 66). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 258 - 66;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 3, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 3;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(5, ContactIndex, unchanged). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evHeroAttack);
        EventStack[EventCursor].A := ContactIndex;
        { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], 184). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
        EventStack[EventCursor].B := 184;
        { PushCommand(9, ContactIndex, 183). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := 183;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 3, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 3;
        EventStack[EventCursor].B := 0;
      end;
    end
    else
    begin
      Hero.Word48 := 0;
      dameiji;
      { PushCommand(11, 5, 5). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 5;
      EventStack[EventCursor].B := 5;
      { PushCommand(7, Monsters[MonsterIndex].Gold, unchanged). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evAwardGold);
      EventStack[EventCursor].A := Monsters[MonsterIndex].Gold;
      { PushCommand(2, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      monswork;
      TileClass := 1;
      MessageText :=
          ListBox2.Items[199]
              + ' '
              + MonsterText
              + '. '
              + ListBox2.Items[200]
              + ' '
              + IntToStr(Monsters[MonsterIndex].Gold * (Hero.lucky_gold + 1))
              + ListBox2.Items[201];
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileOctopusFirst..103:
        begin
          if Hero.lucky_gold = 0 then
          begin
            MessageText :=
                ListBox2.Items[240]
                    + ' '
                    + MonsterText
                    + '. '
                    + ListBox2.Items[200]
                    + ' '
                    + IntToStr(Monsters[MonsterIndex].Gold div 2)
                    + ListBox2.Items[201];
            EventStack[EventCursor - 1].A := Smallint(EventStack[EventCursor - 1].A) div 2;
          end
          else
          begin
            MessageText :=
                ListBox2.Items[240]
                    + ' '
                    + MonsterText
                    + '. '
                    + ListBox2.Items[200]
                    + ' '
                    + IntToStr(Monsters[MonsterIndex].Gold)
                    + ListBox2.Items[201];
            EventStack[EventCursor - 1].A := Smallint(EventStack[EventCursor - 1].A) div 2;
          end;
        end;
        105:
        begin
          if Hero.lucky_gold = 0 then
          begin
            MessageText :=
                ListBox2.Items[240]
                    + ' '
                    + MonsterText
                    + '. '
                    + ListBox2.Items[200]
                    + ' '
                    + IntToStr(Monsters[MonsterIndex].Gold div 2)
                    + ListBox2.Items[201];
            EventStack[EventCursor - 1].A := Smallint(EventStack[EventCursor - 1].A) div 2;
          end
          else
          begin
            MessageText :=
                ListBox2.Items[240]
                    + ' '
                    + MonsterText
                    + '. '
                    + ListBox2.Items[200]
                    + ' '
                    + IntToStr(Monsters[MonsterIndex].Gold)
                    + ListBox2.Items[201];
            EventStack[EventCursor - 1].A := Smallint(EventStack[EventCursor - 1].A) div 2;
          end;
        end;
      end;
      { PushCommand(17, Hero.y * 11 + Hero.x, 6). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
      EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x;
      EventStack[EventCursor].B := tileRoad;
      case MonsterIndex of
        Ord(monsterOctopus):
        begin
          if Maps[Hero.floor, ContactIndex + MapTileOffset] = tileOctopusMouth then
          begin
            { PushCommand(17, Hero.y * 11 + Hero.x - 21, 6). }
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 21;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 22, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 22;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 23, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 23;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 12, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 12;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 11, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 11;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 10, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 10;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 1, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 1;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x + 1, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x + 1;
            EventStack[EventCursor].B := tileRoad;
          end;
        end;
        Ord(monsterDragon):
        begin
          if Maps[Hero.floor, ContactIndex + MapTileOffset] = tileDragonHead then
          begin
            { PushCommand(17, Hero.y * 11 + Hero.x - 21, 6). }
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 21;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 22, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 22;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 23, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 23;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 12, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 12;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 11, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 11;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 10, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 10;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x - 1, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x - 1;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(17, Hero.y * 11 + Hero.x + 1, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
            EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x + 1;
            EventStack[EventCursor].B := tileRoad;
          end;
        end;
      end;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 9, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 9;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(5, ContactIndex, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evHeroAttack);
      EventStack[EventCursor].A := ContactIndex;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], 184). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
      EventStack[EventCursor].B := 184;
      { PushCommand(9, ContactIndex, 183). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := ContactIndex;
      EventStack[EventCursor].B := 183;
      case MonsterIndex of
        Ord(monsterOctopus):
        begin
          if Maps[Hero.floor, ContactIndex + MapTileOffset] = tileOctopusMouth then
            EventStack[EventCursor].Opcode := Ord(evHeroAttackOverlay);
        end;
        Ord(monsterDragon):
        begin
          if Maps[Hero.floor, ContactIndex + MapTileOffset] = tileDragonHead then
            EventStack[EventCursor].Opcode := Ord(evHeroAttackOverlay);
        end;
      end;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 3, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 3;
      EventStack[EventCursor].B := 0;
      if StrikeCount > 1 then
        for I := 1 to StrikeCount - 1 do
        begin
          ScratchIndex := I;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(4, ContactIndex, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evEnemyAttack);
          EventStack[EventCursor].A := ContactIndex;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], (Hero.facing - 1) * 8 + 257 - 66). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A :=
              Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
          EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 257 - 66;
          { PushCommand(9, ContactIndex, (Hero.facing - 1) * 8 + 258 - 66). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evOverlay);
          EventStack[EventCursor].A := ContactIndex;
          EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 258 - 66;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 3, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 3;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(5, ContactIndex, 183). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evHeroAttack);
          EventStack[EventCursor].A := ContactIndex;
          EventStack[EventCursor].B := 183;
          { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], 184). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A :=
              Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
          EventStack[EventCursor].B := 184;
          { PushCommand(9, ContactIndex, 183). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evOverlay);
          EventStack[EventCursor].A := ContactIndex;
          EventStack[EventCursor].B := 183;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 3, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 3;
          EventStack[EventCursor].B := 0;
        end;
    end;
  end;
  timer2on;
end;
procedure TTSW10.taisen2; { $0047F7D4 }
var
  I: Longint;
begin
  ContactIndex := Smallint(EventStack[EventCursor + 1].B);
  case Maps[Hero.floor, ContactIndex + MapTileOffset] of
    tileGreenSlime..tileVampire:
      DoorOpened := (Maps[Hero.floor, ContactIndex + MapTileOffset] + 1) div 2 - 30 + 197;
    132..tileGateKeeperA:
      DoorOpened := (Maps[Hero.floor, ContactIndex + MapTileOffset] + 1) div 2 - 46 + 197;
  end;
  NeighborIndex := DoorOpened - 198;
  MonsterIndex := NeighborIndex;
  monshyouji;
  Hero.Word48 := 1;
  NeighborIndex := MonsterIndex;
  BattleHP := Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1);
  dameiji2;
  if Hero.hp <= Damage then
  begin
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(3, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evDefeat);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;

    StrikeCount := 0;
    RemainingHP := Hero.hp;
    ydamei3;
    Damage :=
        (Hero.attack - Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1))
            * (StrikeCount - 1);
    for I := 1 to StrikeCount do
    begin
      ScratchIndex := I;
      if ScratchIndex <> 1 then
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(5, ContactIndex, unchanged). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evHeroAttack);
        EventStack[EventCursor].A := ContactIndex;
        { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], 184). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
        EventStack[EventCursor].B := 184;
        { PushCommand(9, ContactIndex, 183). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := 183;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 3, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 3;
        EventStack[EventCursor].B := 0;
      end
      else
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
      end;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(4, ContactIndex, unchanged). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evEnemyAttack);
      EventStack[EventCursor].A := ContactIndex;
      if ScratchIndex = 1 then
        EventStack[EventCursor].B := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset]
      else
        EventStack[EventCursor].B := 250;
      { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], (Hero.facing - 1) * 8 + 257 - 66). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
      EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 257 - 66;
      { PushCommand(9, ContactIndex, (Hero.facing - 1) * 8 + 258 - 66). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evOverlay);
      EventStack[EventCursor].A := ContactIndex;
      EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 258 - 66;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 3, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 3;
      EventStack[EventCursor].B := 0;
    end;
  end
  else
  begin
    Hero.Word48 := 0;
    { PushCommand(11, 5, 5). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 5;
    EventStack[EventCursor].B := 5;
    { PushCommand(7, Monsters[MonsterIndex].Gold, unchanged). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evAwardGold);
    EventStack[EventCursor].A := Monsters[MonsterIndex].Gold;
    { PushCommand(2, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    TileClass := 1;
    monswork;
    MessageText :=
        ListBox2.Items[199]
            + ' '
            + MonsterText
            + '. '
            + ListBox2.Items[200]
            + ' '
            + IntToStr(Monsters[MonsterIndex].Gold)
            + ListBox2.Items[201];
    { PushCommand(17, Hero.y * 11 + Hero.x, 6). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSetTileOnly);
    EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x;
    EventStack[EventCursor].B := tileRoad;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(11, 9, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSceneAction);
    EventStack[EventCursor].A := 9;
    EventStack[EventCursor].B := 0;
    if StrikeCount >= 1 then
      for I := 1 to StrikeCount do
      begin
        ScratchIndex := I;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(5, ContactIndex, 193). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evHeroAttack);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := 193;
        { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], 184). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
        EventStack[EventCursor].B := 184;
        { PushCommand(9, ContactIndex, 183). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := 183;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 3, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 3;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(4, ContactIndex, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evEnemyAttack);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, Maps[Hero.floor, Hero.y * 11 + Hero.x + 2], (Hero.facing - 1) * 8 + 257 - 66). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset];
        EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 257 - 66;
        { PushCommand(9, ContactIndex, (Hero.facing - 1) * 8 + 258 - 66). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := (Hero.facing - 1) * 8 + 258 - 66;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 3, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 3;
        EventStack[EventCursor].B := 0;
      end;
  end;
  timer2on;
end;

procedure TTSW10.madoushi1; { $0044C464, pincer loses half current HP }
begin
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(19, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evHalveHP);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(2, 112, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
  EventStack[EventCursor].A := 112;
  EventStack[EventCursor].B := 0;
  { PushCommand(0, 6, facing damage frame). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 6;
  case Hero.facing of
    Ord(hfDown): EventStack[EventCursor].B := 191;
    Ord(hfLeft): EventStack[EventCursor].B := 199;
    Ord(hfRight): EventStack[EventCursor].B := 207;
    Ord(hfUp): EventStack[EventCursor].B := 215;
  end;
  { PushCommand(9, ScratchIndex, facing damage frame). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evOverlay);
  EventStack[EventCursor].A := ScratchIndex;
  case Hero.facing of
    Ord(hfDown): EventStack[EventCursor].B := 192;
    Ord(hfLeft): EventStack[EventCursor].B := 200;
    Ord(hfRight): EventStack[EventCursor].B := 208;
    Ord(hfUp): EventStack[EventCursor].B := 216;
  end;
  { PushCommand(0, 0, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 1, 0). }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 1;
  EventStack[EventCursor].B := 0;
  timer2on;
  TileClass := 0;
  NeighborY := 1;
end;

procedure TTSW10.syounin; { $00449014 }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  Button1.Caption := 'OK';
  itemdel;
  RichEdit1.Font.Size := GameOptions[optionLargeFont];
  case GameOptions[optionDisplaySize] of
    display640x400:
    begin
      RichEdit1.Height := 200;
      RichEdit1.Width := 382;
      RichEdit1.Top := 45;
      RichEdit1.Left := 129;
    end;
    display800x500:
    begin
      RichEdit1.Height := 250;
      RichEdit1.Width := 478;
      RichEdit1.Top := 56;
      RichEdit1.Left := 161;
    end;
  end;
  Button1.Top := RichEdit1.Top + RichEdit1.Height - Button1.Height - Image6.Height div 2;
  Button1.Left := RichEdit1.Left + RichEdit1.Width - Button1.Width - Image6.Width div 2;
  Button7.Top := RichEdit1.Top + RichEdit1.Height - Button7.Height - Image6.Height div 2;
  Button7.Left := RichEdit1.Left + RichEdit1.Width - Button7.Width - Image6.Width div 2;
  Button2.Top := RichEdit1.Top + RichEdit1.Height - Button2.Height - Image6.Height div 2;
  Button2.Left := Button7.Left - Button2.Width - Image6.Width div 2;
  ShopMode := Ord(shopMerchant);
  DialogueStage := stageNone;
  case Hero.floor of
    2:
    begin
      GameplayHintIndex := 29;
      ScratchIndex := 0;
      MerchantTradeWord := 42;
      MerchantClueWord := 54;
      GameplayShopCost := 0;
      StrikeCount := 92;
    end;
    6:
    begin
      GameplayHintIndex := 2;
      ScratchIndex := 1;
      MerchantTradeWord := 43;
      MerchantClueWord := 55;
      GameplayShopCost := 50;
      StrikeCount := 65;
    end;
    7:
    begin
      GameplayHintIndex := 3;
      ScratchIndex := 2;
      MerchantTradeWord := 44;
      MerchantClueWord := 56;
      GameplayShopCost := 50;
      StrikeCount := 66;
    end;
    12:
    begin
      case Hero.x of
        1:
        begin
          GameplayHintIndex := 4;
          ScratchIndex := 3;
          MerchantTradeWord := 45;
          MerchantClueWord := 57;
          GameplayShopCost := 800;
          StrikeCount := 67;
        end;
        9:
        begin
          ScratchIndex := 4;
          MerchantTradeWord := 46;
          GameplayShopCost := 1000;
        end;
      end;
    end;
    15:
    begin
      GameplayHintIndex := 5;
      ScratchIndex := 5;
      MerchantTradeWord := 47;
      MerchantClueWord := 59;
      GameplayShopCost := 200;
      StrikeCount := 68;
    end;
    28:
    begin
      ScratchIndex := 6;
      MerchantTradeWord := 48;
      GameplayShopCost := 0;
    end;
    31:
    begin
      GameplayHintIndex := 11;
      ScratchIndex := 7;
      MerchantTradeWord := 49;
      MerchantClueWord := 61;
      GameplayShopCost := 1000;
      StrikeCount := 74;
    end;
    38:
    begin
      GameplayHintIndex := 15;
      ScratchIndex := 8;
      MerchantTradeWord := 50;
      MerchantClueWord := 62;
      GameplayShopCost := 200;
      StrikeCount := 78;
    end;
    39:
    begin
      GameplayHintIndex := 17;
      ScratchIndex := 9;
      MerchantTradeWord := 51;
      MerchantClueWord := 63;
      GameplayShopCost := 2000;
      StrikeCount := 80;
    end;
    45:
    begin
      GameplayHintIndex := 20;
      ScratchIndex := 10;
      MerchantTradeWord := 52;
      MerchantClueWord := 64;
      GameplayShopCost := 1000;
      StrikeCount := 83;
    end;
    47:
    begin
      GameplayHintIndex := 22;
      ScratchIndex := 11;
      MerchantTradeWord := 53;
      MerchantClueWord := 65;
      GameplayShopCost := 4000;
      StrikeCount := 85;
    end;
  end;
  NeighborY := 0;
  case HeroWords[MerchantTradeWord] of
    0:
    begin
      case ScratchIndex of
        0..11: RichEdit1.Text := ListBox2.Items[ScratchIndex + textMerchantOfferBase];
      end;
      RichEdit1.Visible := True;
      Button2.Visible := True;
      Button7.Visible := True;
      if Hero.floor = 2 then
        Button7.Enabled := False;
      Button2.SetFocus;
    end;
    1:
    begin
      case HeroWords[MerchantClueWord] of
        0:
        begin
          RichEdit1.Text := ListBox2.Items[StrikeCount - 1];
          case Hero.wisdom_orb of
            0: HeroWords[MerchantClueWord] := 1;
            1: HeroWords[MerchantClueWord] := 2;
          end;
          RichEdit1.Visible := True;
          Button1.Visible := True;
          Button1.SetFocus;
        end;
        1..2:
        begin
          if Hero.floor <> 2 then
          begin
            GameplayHintIndex := 28;
            zyouout;
          end
          else
          begin
            GameplayHintIndex := 29;
            zyouout;
          end;
        end;
      end;
    end;
  end;
end;

procedure TTSW10.roujin; { $00449708 }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  Button1.Caption := 'OK';
  RichEdit1.Font.Size := GameOptions[optionLargeFont];
  itemdel;
  DialogueStage := stageNone;
  DamageMode := 0;
  case Hero.floor of
    2:
    begin
      GameplayHintIndex := 25;
      NeighborIndex := 66;
      if Hero.Word392 = 0 then
      begin
        Hero.Word392 := 1;
        Inc(Hero.attack, Hero.attack * 3 div 100);
        Inc(Hero.defense, Hero.defense * 3 div 100);
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(2, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        timer2on;
      end;
    end;
    3:
    begin
      GameplayHintIndex := 26;
      NeighborIndex := 67;
    end;
    4:
    begin
      GameplayHintIndex := 0;
      NeighborIndex := 68;
    end;
    6:
    begin
      GameplayHintIndex := 1;
      NeighborIndex := 69;
    end;
    16:
    begin
      if Hero.x <> 9 then
      begin
        GameplayHintIndex := 6;
        NeighborIndex := 70;
      end
      else
      begin
        GameplayHintIndex := 27;
        NeighborIndex := 71;
      end;
    end;
    18:
    begin
      GameplayHintIndex := 7;
      NeighborIndex := 72;
    end;
    21:
    begin
      GameplayHintIndex := 8;
      NeighborIndex := 73;
    end;
    23:
    begin
      DamageMode := 1;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 61, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechOldManFloor23;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      timer2on;
    end;
    27:
    begin
      GameplayHintIndex := 9;
      NeighborIndex := 74;
    end;
    31:
    begin
      GameplayHintIndex := 10;
      NeighborIndex := 75;
    end;
    33:
    begin
      GameplayHintIndex := 12;
      NeighborIndex := 76;
    end;
    36:
    begin
      GameplayHintIndex := 13;
      NeighborIndex := 77;
    end;
    37:
    begin
      GameplayHintIndex := 14;
      NeighborIndex := 78;
    end;
    39:
    begin
      GameplayHintIndex := 16;
      NeighborIndex := 79;
    end;
    42:
    begin
      GameplayHintIndex := 18;
      NeighborIndex := 80;
    end;
    45:
    begin
      GameplayHintIndex := 19;
      NeighborIndex := 81;
    end;
    46:
    begin
      GameplayHintIndex := 21;
      NeighborIndex := 82;
    end;
    48:
    begin
      GameplayHintIndex := 23;
      NeighborIndex := 83;
    end;
  end;
  if DamageMode <> 1 then
  begin
    { Keep nested: combining these checks changes Delphi 2 register allocation. }
    if GameplayHintIndex = 27 then
    begin
      if Hero.Word436 = 0 then
      begin
        Hero.elixir := 1;
        Hero.Word436 := 1;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(8, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evShowPanels);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        timer2on;
      end;
    end;
    case HeroWords[NeighborIndex] of
      0:
      begin
        case Hero.wisdom_orb of
          0: HeroWords[NeighborIndex] := 1;
          1: HeroWords[NeighborIndex] := 2;
        end;
        zyouout;
        case Hero.floor of
          3:
          begin
            Hero.hero_orb := 2;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(8, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evShowPanels);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(2, 11, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
            EventStack[EventCursor].A := 11;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
      end;
      1:
      begin
        GameplayHintIndex := 24;
        zyouout;
      end;
      2:
      begin
        GameplayHintIndex := 24;
        zyouout;
      end;
    end;
  end;
end;

procedure TTSW10.Button1Click(Sender: TObject); { $0044DA10 }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  if (DialogueStage > 10) and (DialogueStage < 68) then
    HeroWords[DialogueStage + 80] := 1;
  case DialogueStage of
    stageNone:
    begin
      if Hero.hero_orb = 2 then
        Hero.hero_orb := 1;
      itemlive;
      if MouseControl1.Checked = True then
        buttonfocus;
    end;
    1:
    begin
      Button35.Enabled := True;
      Button35.SetFocus;
    end;
    103:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := True;
    end;
    speechUnconscious + DialogueStageOffset:
    begin
      Button1.Visible := False;
      Timer2.Enabled := True;
    end;
    speechThiefCallsHero + DialogueStageOffset:
    begin
      Button1.Visible := False;
      Timer2.Enabled := True;
    end;
    speechThiefWakesHero + DialogueStageOffset:
    begin
      Button1.Visible := False;
      Timer2.Enabled := False;
      Timer1.Enabled := True;
      Hero.Word48 := 0;
      EventCursor := 0;
      mhyouji;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      itemlive;
    end;
    speechThiefOpensPrison + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := False;
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 66, 77). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 66;
      EventStack[EventCursor].B := 77;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 67, 66). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 67;
      EventStack[EventCursor].B := 66;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 68, 67). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 68;
      EventStack[EventCursor].B := 67;
    end;
    speechThiefFirstDeparture + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := False;
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, 99, 6). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := 99;
      EventStack[EventCursor].B := tileRoad;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 88, 99). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 88;
      EventStack[EventCursor].B := 99;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(12, 77, 88). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evMoveMonster);
      EventStack[EventCursor].A := 77;
      EventStack[EventCursor].B := 88;
    end;
    speechThiefReturnsToPrison + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := False;
      Maps[35, 105] := tileThief;
      Maps[35, 93] := tileRoad;
      itemlive;
    end;
    speechThiefPromisesToFollow + DialogueStageOffset
        ..speechMerchantRescueReward + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := False;
      itemlive;
    end;
    speechZenoCaptureChallenge + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      openning2;
    end;
    speechHeroCaptured + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := True;
    end;
    speechSkeletonLordChallenge + DialogueStageOffset
        ..speechSkeletonLordDefeated + DialogueStageOffset,
    speechThiefSecondDeparture + DialogueStageOffset..speechVampireDefeated + DialogueStageOffset,
    speechRockChallenge + DialogueStageOffset,
    speechTimeGateInvitation + DialogueStageOffset
        ..speechGreatMagicMasterDefeated + DialogueStageOffset,
    speechGoldenKnightReportsFailure + DialogueStageOffset
        ..speechZenoDefeated + DialogueStageOffset,
    speechHeroFindsThief + DialogueStageOffset..speechZenoOffersAlliance + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := True;
    end;
    speechOldManFloor23 + DialogueStageOffset, speechThiefTimeGate + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := False;
      itemlive;
    end;
    speechFairyFloor10 + DialogueStageOffset,
    speechFairyFloor20 + DialogueStageOffset,
    speechFairyFloor25 + DialogueStageOffset,
    speechFairyFloor40 + DialogueStageOffset,
    speechFairyFloor49 + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      TileClass := 0;
      if Hero.cycle_factor_minus_one = 0 then
        RankingForm.ShowModal
      else
        Timer2.Enabled := True;
    end;
    speechBacksideZenoDefeated + DialogueStageOffset:
    begin
      Button1.Visible := False;
      RichEdit1.Visible := False;
      RichEdit1.Text := '';
      Timer2.Enabled := True;
    end;
  end;
  Button1.Visible := False;
  if DialogueStage <= 1 then
  begin
    RichEdit1.Lines.Clear;
    RichEdit1.Visible := False;
  end;
  disp;
end;

procedure TTSW10.Button2Click(Sender: TObject); { $0044E1CC }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  Button2.Visible := False;
  Button7.Visible := False;
  if Button7.Enabled = False then
    Button7.Enabled := True;
  RichEdit1.Text := '';
  if ShopMode = Ord(shopMerchant) then
    RichEdit1.Visible := False;
  disp;
  case ShopMode of
    Ord(shopMerchant):
    begin
      if Hero.floor <> 28 then
      begin
        if Hero.gold < GameplayShopCost then
        begin
          RichEdit1.Text := ListBox2.Items[258];
          RichEdit1.Visible := True;
          Button1.Visible := True;
          Button1.SetFocus;
          DialogueStage := stageNone;
        end
        else
        begin
          Dec(Hero.gold, GameplayShopCost);
          DialogueStage := stageNone;
          case MerchantTradeWord of
            42..45: HeroWords[MerchantTradeWord] := 1;
            47: HeroWords[MerchantTradeWord] := 1;
            49..53: HeroWords[MerchantTradeWord] := 1;
          end;
          case MerchantTradeWord of
            42: Inc(Hero.gold, 1000);
            43: Inc(Hero.blue_keys);
            44: Inc(Hero.yellow_keys, 5);
            45: Inc(Hero.red_keys);
            46: Inc(Hero.yellow_keys);
            47: Inc(Hero.blue_keys);
            48:
            begin
              Dec(Hero.yellow_keys);
              Inc(Hero.gold, 100);
            end;
            49:
            begin
              Inc(Hero.yellow_keys, 4);
              Inc(Hero.blue_keys);
            end;
            50: Inc(Hero.yellow_keys, 3);
            51: Inc(Hero.blue_keys, 3);
            52: Inc(Hero.hp, 2000);
            53: Hero.super_mattock := 1;
          end;
          RichEdit1.Text := ListBox2.Items[259];
          RichEdit1.Visible := True;
          Button1.Visible := True;
          Button1.SetFocus;
          { PushCommand(2, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(8, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evShowPanels);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 2, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 2;
          EventStack[EventCursor].B := 0;
          timer2on;
        end;
      end
      else
      begin
        if Hero.yellow_keys = 0 then
        begin
          RichEdit1.Text := ListBox2.Items[262];
          RichEdit1.Visible := True;
          Button1.Visible := True;
          Button1.SetFocus;
          DialogueStage := stageNone;
        end
        else
        begin
          Dec(Hero.yellow_keys);
          Inc(Hero.gold, 100);
          DialogueStage := stageNone;
          RichEdit1.Text := ListBox2.Items[259];
          RichEdit1.Visible := True;
          Button1.Visible := True;
          Button1.SetFocus;
          { PushCommand(2, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(8, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evShowPanels);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 2, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 2;
          EventStack[EventCursor].B := 0;
          timer2on;
        end;
      end;
    end;
    Ord(shopAltar):
    begin
      { Altar choices form four full-width rows inside the dialogue panel. }
      Button39.Height := Image6.Height;
      Button39.Width := RichEdit1.Width - Image6.Width;
      if Button39.Width > RichEdit1.Width then
        Button39.Width := RichEdit1.Width;
      Button39.Top := RichEdit1.Top + Image6.Height + Image6.Height div 2;
      Button39.Left := RichEdit1.Left + Image6.Width div 2;
      Button40.Height := Button39.Height;
      Button40.Width := Button39.Width;
      Button40.Top := Button39.Top + Button39.Height;
      Button40.Left := Button39.Left;
      Button41.Height := Button39.Height;
      Button41.Width := Button39.Width;
      Button41.Top := Button40.Top + Button40.Height;
      Button41.Left := Button39.Left;
      Button42.Height := Button39.Height;
      Button42.Width := Button39.Width;
      Button42.Top := Button41.Top + Button41.Height;
      Button42.Left := Button39.Left;
      RichEdit1.Text := ListBox2.Items[204];
      Button39.Caption :=
          ListBox2.Items[205]
              + ' '
              + IntToStr((Hero.Word44 + 1) * 100 * (Hero.cycle_factor_minus_one + 1))
              + ' '
              + ListBox2.Items[206];
      Button40.Caption :=
          ListBox2.Items[207]
              + ' '
              + IntToStr((Hero.floor + 10) div 10 * 2 * (Hero.cycle_factor_minus_one + 1))
              + ' '
              + ListBox2.Items[208];
      Button41.Caption :=
          ListBox2.Items[209]
              + ' '
              + IntToStr((Hero.floor + 10) div 10 * 4 * (Hero.cycle_factor_minus_one + 1))
              + ' '
              + ListBox2.Items[208];
      Button42.Caption := ListBox2.Items[210];
      Button39.Visible := True;
      Button40.Visible := True;
      Button41.Visible := True;
      Button42.Visible := True;
      Button42.SetFocus;
    end;
  end;
end;

procedure TTSW10.Button7Click(Sender: TObject);
begin
  Button2.Visible := False;
  Button7.Visible := False;
  itemlive;
  if MouseControl1.Checked = True then
    buttonfocus;
  RichEdit1.Text := '';
  RichEdit1.Visible := False;
  disp;
end;

procedure TTSW10.Button39Click(Sender: TObject);
begin
  Button39.Visible := False;
  Button40.Visible := False;
  Button41.Visible := False;
  Button42.Visible := False;
  RichEdit1.Visible := False;
  if Hero.gold >= GameplayShopCost then
  begin
    TileClass := 1;
    MessageText :=
        ListBox2.Items[181]
            + ' '
            + IntToStr((Hero.Word44 + 1) * 100 * (Hero.cycle_factor_minus_one + 1))
            + ListBox2.Items[166];
    Inc(Hero.Word44);
    Dec(Hero.gold, GameplayShopCost);
    Inc(Hero.hp, Hero.Word44 * 100 * (Hero.cycle_factor_minus_one + 1));
    timer2on;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(2, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(1, 2, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSound);
    EventStack[EventCursor].A := 2;
    EventStack[EventCursor].B := 0;
    EventPaused := 0;
  end
  else
  begin
    RichEdit1.Text := ListBox2.Items[211];
    DialogueStage := stageNone;
    Button1.Top := RichEdit1.Top + RichEdit1.Height - Button1.Height - 16;
    Button1.Left := RichEdit1.Left + RichEdit1.Width - Button1.Width - 16;
    RichEdit1.Visible := True;
    Button1.Visible := True;
    Button1.SetFocus;
  end;
end;
procedure TTSW10.Button40Click(Sender: TObject);
begin
  Button39.Visible := False;
  Button40.Visible := False;
  Button41.Visible := False;
  Button42.Visible := False;
  RichEdit1.Visible := False;
  if Hero.gold >= GameplayShopCost then
  begin
    TileClass := 1;
    MessageText :=
        ListBox2.Items[182]
            + ' '
            + IntToStr(((Hero.floor + 10) div 10) * 2 * (Hero.cycle_factor_minus_one + 1))
            + ListBox2.Items[166];
    Inc(Hero.Word44);
    Dec(Hero.gold, GameplayShopCost);
    Inc(Hero.attack, ((Hero.floor + 10) div 10) * 2 * (Hero.cycle_factor_minus_one + 1));
    timer2on;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(2, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(1, 2, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSound);
    EventStack[EventCursor].A := 2;
    EventStack[EventCursor].B := 0;
    EventPaused := 0;
  end
  else
  begin
    RichEdit1.Text := ListBox2.Items[211];
    DialogueStage := stageNone;
    Button1.Top := RichEdit1.Top + RichEdit1.Height - Button1.Height - 16;
    Button1.Left := RichEdit1.Left + RichEdit1.Width - Button1.Width - 16;
    RichEdit1.Visible := True;
    Button1.Visible := True;
    Button1.SetFocus;
  end;
end;
procedure TTSW10.Button41Click(Sender: TObject);
begin
  Button39.Visible := False;
  Button40.Visible := False;
  Button41.Visible := False;
  Button42.Visible := False;
  RichEdit1.Visible := False;
  if Hero.gold >= GameplayShopCost then
  begin
    TileClass := 1;
    MessageText :=
        ListBox2.Items[183]
            + ' '
            + IntToStr(((Hero.floor + 10) div 10) * 4 * (Hero.cycle_factor_minus_one + 1))
            + ListBox2.Items[166];
    Inc(Hero.Word44);
    Dec(Hero.gold, GameplayShopCost);
    Inc(Hero.defense, ((Hero.floor + 10) div 10) * 4 * (Hero.cycle_factor_minus_one + 1));
    timer2on;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(2, 1, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(1, 2, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evSound);
    EventStack[EventCursor].A := 2;
    EventStack[EventCursor].B := 0;
    EventPaused := 0;
  end
  else
  begin
    RichEdit1.Text := ListBox2.Items[211];
    DialogueStage := stageNone;
    Button1.Top := RichEdit1.Top + RichEdit1.Height - Button1.Height - 16;
    Button1.Left := RichEdit1.Left + RichEdit1.Width - Button1.Width - 16;
    RichEdit1.Visible := True;
    Button1.Visible := True;
    Button1.SetFocus;
  end;
end;
procedure TTSW10.Button42Click(Sender: TObject);
begin
  Button39.Visible := False;
  Button40.Visible := False;
  Button41.Visible := False;
  Button42.Visible := False;
  RichEdit1.Visible := False;
  itemlive;
end;

procedure TTSW10.zyouout; { $00449E18; wisdom and queued story dialogue }
begin
  if DialogueStage = 9 then
  begin
    if Hero.music_track <> 0 then
      Hero.music_track := 14;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(22, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evResetCycle);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(10, 93, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evDialogue);
    EventStack[EventCursor].A := 93;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    { PushCommand(0, 0, 0). }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWait);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 0;
    if Hero.music_track <> 0 then
    begin
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 5, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 5;
      EventStack[EventCursor].B := 0;
    end;
    timer2on;
  end
  else
  begin
    RichEdit1.Font.Size := GameOptions[optionLargeFont];
    case GameOptions[optionDisplaySize] of
      display640x400:
      begin
        RichEdit1.Height := 200;
        RichEdit1.Width := 382;
        RichEdit1.Top := 45;
        RichEdit1.Left := 129;
      end;
      display800x500:
      begin
        RichEdit1.Height := 250;
        RichEdit1.Width := 478;
        RichEdit1.Top := 56;
        RichEdit1.Left := 161;
      end;
    end;
    Button1.Top := RichEdit1.Top + RichEdit1.Height - Button1.Height - 16;
    Button1.Left := RichEdit1.Left + RichEdit1.Width - Button1.Width - 16;
    if DialogueStage < 10 then
      RichEdit1.Text := ListBox2.Items[GameplayHintIndex + textWisdomHintBase]
    else
    begin
      { Ranking speeches keep the text prepared by yousei. }
      if (DialogueSpeech <> speechFairyFloor10)
          and (DialogueSpeech <> speechFairyFloor20)
          and (DialogueSpeech <> speechFairyFloor25)
          and (DialogueSpeech <> speechFairyFloor40)
          and (DialogueSpeech <> speechFairyFloor49) then
        RichEdit1.Text := ListBox2.Items[DialogueSpeech - 1];
      case DialogueSpeech of
        speechThiefFirstDeparture:
          RichEdit1.Text := RichEdit1.Text + ListBox2.Items[DialogueSpeech + 53 - 1];
        speechThiefSecondDeparture:
          RichEdit1.Text := RichEdit1.Text + ListBox2.Items[DialogueSpeech + 42 - 1];
        speechZenoRevealsPlan:
          RichEdit1.Text := RichEdit1.Text + ListBox2.Items[DialogueSpeech + 5 - 1];
      end;
    end;
    if (Hero.Word668 <> 1) and (DialogueSpeech = 93) and (DialogueStage >= 10) then
    begin
      if MessageDlg('You have no life point. Do you try again?', mtInformation, [mbYes, mbNo], 0)
          = mrYes then
        timer2on
      else
        GameLoad1.Enabled := True;
    end
    else
    begin
      RichEdit1.Visible := True;
      case Hero.Word668 of
        0:
        begin
          Button1.Visible := True;
          Button1.SetFocus;
        end;
      end;
    end;
  end;
end;

procedure TTSW10.img5work; { $0048198C }
begin
  if Hero.wisdom_orb = 1 then
  begin
    DialogueStage := 1;
    itemdel;
    { The form owns the clue-grid geometry; only heard and recorded clues enable. }
    Button11.Visible := True;
    Button12.Visible := True;
    Button13.Visible := True;
    Button14.Visible := True;
    Button15.Visible := True;
    Button16.Visible := True;
    Button17.Visible := True;
    Button18.Visible := True;
    Button19.Visible := True;
    Button20.Visible := True;
    Button21.Visible := True;
    Button22.Visible := True;
    Button23.Visible := True;
    Button24.Visible := True;
    Button25.Visible := True;
    Button26.Visible := True;
    Button27.Visible := True;
    Button28.Visible := True;
    Button29.Visible := True;
    Button30.Visible := True;
    Button31.Visible := True;
    Button32.Visible := True;
    Button33.Visible := True;
    Button34.Visible := True;
    if Hero.Word272 = 2 then
      Button11.Enabled := True
    else
      Button11.Enabled := False;
    if Hero.Word276 = 2 then
      Button12.Enabled := True
    else
      Button12.Enabled := False;
    if Hero.Word220 = 2 then
      Button13.Enabled := True
    else
      Button13.Enabled := False;
    if Hero.Word224 = 2 then
      Button14.Enabled := True
    else
      Button14.Enabled := False;
    if Hero.Word228 = 2 then
      Button15.Enabled := True
    else
      Button15.Enabled := False;
    if Hero.Word236 = 2 then
      Button16.Enabled := True
    else
      Button16.Enabled := False;
    if Hero.Word280 = 2 then
      Button17.Enabled := True
    else
      Button17.Enabled := False;
    if Hero.Word288 = 2 then
      Button18.Enabled := True
    else
      Button18.Enabled := False;
    if Hero.Word292 = 2 then
      Button19.Enabled := True
    else
      Button19.Enabled := False;
    if Hero.Word296 = 2 then
      Button20.Enabled := True
    else
      Button20.Enabled := False;
    if Hero.Word300 = 2 then
      Button21.Enabled := True
    else
      Button21.Enabled := False;
    if Hero.Word244 = 2 then
      Button22.Enabled := True
    else
      Button22.Enabled := False;
    if Hero.Word304 = 2 then
      Button23.Enabled := True
    else
      Button23.Enabled := False;
    if Hero.Word308 = 2 then
      Button24.Enabled := True
    else
      Button24.Enabled := False;
    if Hero.Word312 = 2 then
      Button25.Enabled := True
    else
      Button25.Enabled := False;
    if Hero.Word248 = 2 then
      Button26.Enabled := True
    else
      Button26.Enabled := False;
    if Hero.Word316 = 2 then
      Button27.Enabled := True
    else
      Button27.Enabled := False;
    if Hero.Word252 = 2 then
      Button28.Enabled := True
    else
      Button28.Enabled := False;
    if Hero.Word320 = 2 then
      Button29.Enabled := True
    else
      Button29.Enabled := False;
    if Hero.Word324 = 2 then
      Button30.Enabled := True
    else
      Button30.Enabled := False;
    if Hero.Word256 = 2 then
      Button31.Enabled := True
    else
      Button31.Enabled := False;
    if Hero.Word328 = 2 then
      Button32.Enabled := True
    else
      Button32.Enabled := False;
    if Hero.Word260 = 2 then
      Button33.Enabled := True
    else
      Button33.Enabled := False;
    if Hero.Word332 = 2 then
      Button34.Enabled := True
    else
      Button34.Enabled := False;
    Button35.Visible := True;
    Button35.SetFocus;
  end;
end;

procedure TTSW10.Button11Click(Sender: TObject);
begin
  GameplayHintIndex := 0;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button12Click(Sender: TObject);
begin
  GameplayHintIndex := 1;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button13Click(Sender: TObject);
begin
  GameplayHintIndex := 2;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button14Click(Sender: TObject);
begin
  GameplayHintIndex := 3;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button15Click(Sender: TObject);
begin
  GameplayHintIndex := 4;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button16Click(Sender: TObject);
begin
  GameplayHintIndex := 5;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button17Click(Sender: TObject);
begin
  GameplayHintIndex := 6;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button18Click(Sender: TObject);
begin
  GameplayHintIndex := 7;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button19Click(Sender: TObject);
begin
  GameplayHintIndex := 8;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button20Click(Sender: TObject);
begin
  GameplayHintIndex := 9;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button21Click(Sender: TObject);
begin
  GameplayHintIndex := 10;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button22Click(Sender: TObject);
begin
  GameplayHintIndex := 11;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button23Click(Sender: TObject);
begin
  GameplayHintIndex := 12;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button24Click(Sender: TObject);
begin
  GameplayHintIndex := 13;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button25Click(Sender: TObject);
begin
  GameplayHintIndex := 14;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button26Click(Sender: TObject);
begin
  GameplayHintIndex := 15;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button27Click(Sender: TObject);
begin
  GameplayHintIndex := 16;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button28Click(Sender: TObject);
begin
  GameplayHintIndex := 17;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button29Click(Sender: TObject);
begin
  GameplayHintIndex := 18;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button30Click(Sender: TObject);
begin
  GameplayHintIndex := 19;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button31Click(Sender: TObject);
begin
  GameplayHintIndex := 20;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button32Click(Sender: TObject);
begin
  GameplayHintIndex := 21;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button33Click(Sender: TObject);
begin
  GameplayHintIndex := 22;
  Hero.Word668 := 1;
  zyouout;
end;
procedure TTSW10.Button34Click(Sender: TObject);
begin
  GameplayHintIndex := 23;
  Hero.Word668 := 1;
  zyouout;
end;

procedure TTSW10.Button35Click(Sender: TObject);
begin
  RichEdit1.Visible := False;
  RichEdit1.Text := '';
  DialogueStage := stageNone;
  Hero.Word668 := 0;
  { Close every clue button, then restore item controls. }
  Button11.Visible := False;
  Button12.Visible := False;
  Button13.Visible := False;
  Button14.Visible := False;
  Button15.Visible := False;
  Button16.Visible := False;
  Button17.Visible := False;
  Button18.Visible := False;
  Button19.Visible := False;
  Button20.Visible := False;
  Button21.Visible := False;
  Button22.Visible := False;
  Button23.Visible := False;
  Button24.Visible := False;
  Button25.Visible := False;
  Button26.Visible := False;
  Button27.Visible := False;
  Button28.Visible := False;
  Button29.Visible := False;
  Button30.Visible := False;
  Button31.Visible := False;
  Button32.Visible := False;
  Button33.Visible := False;
  Button34.Visible := False;
  Button35.Visible := False;
  itemlive;
end;

procedure TTSW10.yousya; { $0044F26C, append a unique Orb row }
var
  I, Tile: Longint;
begin
  MonsterIndex := NeighborIndex;
  NeighborY := 0;
  { Seven rows, in first map-occurrence order; repeated enemies share a row. }
  if OrbRow <> 1 then
    if OrbRow <= 7 then
      for I := 1 to OrbRow - 1 do
        if OrbEnemies[I] = MonsterIndex then
          NeighborY := 1;
  if NeighborY = 0 then
  begin
    if OrbRow <= 7 then
    begin
      Tile := 0;
      case MonsterIndex of
        Ord(monsterGreenSlime)..Ord(monsterVampire): Tile := MonsterIndex * 2 + 60;
        Ord(monsterOctopus): Tile := 103;
        Ord(monsterDragon): Tile := 121;
        Ord(monsterGoldenKnight)..Ord(monsterGateKeeperA): Tile := MonsterIndex * 2 + 92;
      end;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, Tile);
      case OrbRow of
        1:
        begin
          Image24.Picture.Bitmap := WorkBitmap3;
          Image24.Visible := True;
        end;
        2:
        begin
          Image25.Picture.Bitmap := WorkBitmap3;
          Image25.Visible := True;
        end;
        3:
        begin
          Image26.Picture.Bitmap := WorkBitmap3;
          Image26.Visible := True;
        end;
        4:
        begin
          Image27.Picture.Bitmap := WorkBitmap3;
          Image27.Visible := True;
        end;
        5:
        begin
          Image28.Picture.Bitmap := WorkBitmap3;
          Image28.Visible := True;
        end;
        6:
        begin
          Image29.Picture.Bitmap := WorkBitmap3;
          Image29.Visible := True;
        end;
        7:
        begin
          Image30.Picture.Bitmap := WorkBitmap3;
          Image30.Visible := True;
        end;
      end;
    end;
    case OrbRow of
      1:
      begin
        monswork;
        Edit13.Text := MonsterText;
        Edit14.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit27.Text := DamageText;
      end;
      2:
      begin
        monswork;
        Edit15.Text := MonsterText;
        Edit16.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit28.Text := DamageText;
      end;
      3:
      begin
        monswork;
        Edit17.Text := MonsterText;
        Edit18.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit29.Text := DamageText;
      end;
      4:
      begin
        monswork;
        Edit19.Text := MonsterText;
        Edit20.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit30.Text := DamageText;
      end;
      5:
      begin
        monswork;
        Edit21.Text := MonsterText;
        Edit22.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit31.Text := DamageText;
      end;
      6:
      begin
        monswork;
        Edit23.Text := MonsterText;
        Edit24.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ''
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit32.Text := DamageText;
      end;
      7:
      begin
        monswork;
        Edit25.Text := MonsterText;
        Edit26.Text :=
            ListBox2.Items[214]
                + ' '
                + IntToStr(Monsters[MonsterIndex].HP * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[215]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Attack * (Hero.cycle_factor_minus_one + 1))
                + ' '
                + ListBox2.Items[216]
                + ' '
                + IntToStr(Monsters[MonsterIndex].Defense * (Hero.cycle_factor_minus_one + 1));
        obudameiji;
        Edit33.Text := DamageText;
      end;
    end;
    if OrbRow <= 7 then
    begin
      OrbEnemies[OrbRow] := NeighborIndex;
      Inc(OrbRow);
    end;
  end;
end;

procedure TTSW10.img6work; { $00480F60 }
var
  I: Longint;
begin
  RichEdit1.Font.Size := GameOptions[optionLargeFont];
  case GameOptions[optionDisplaySize] of
    display640x400:
    begin
      RichEdit1.Height := 56;
      RichEdit1.Width := 358;
      RichEdit1.Top := 16;
      RichEdit1.Left := 141;
      Image23.Top := 24;
      Image23.Left := 144;
    end;
    display800x500:
    begin
      RichEdit1.Height := 70;
      RichEdit1.Width := 448;
      RichEdit1.Top := 20;
      RichEdit1.Left := 176;
      Image23.Top := 30;
      Image23.Left := 180;
    end;
  end;
  Image23.Height := Image6.Height * BoardWidth;
  Image23.Width := Image6.Width * BoardWidth;
  if Hero.hero_orb = 1 then
  begin
    Timer1.Enabled := False;
    itemdel;
    { Align the original fixed rows, portraits and damage column. }
    case GameOptions[optionDisplaySize] of
      display640x400: Edit13.Left := RichEdit1.Left + 40;
      display800x500: Edit13.Left := RichEdit1.Left + 50;
    end;
    Edit14.Left := Edit13.Left;
    Edit15.Left := Edit13.Left;
    Edit16.Left := Edit13.Left;
    Edit17.Left := Edit13.Left;
    Edit18.Left := Edit13.Left;
    Edit19.Left := Edit13.Left;
    Edit20.Left := Edit13.Left;
    Edit21.Left := Edit13.Left;
    Edit22.Left := Edit13.Left;
    Edit23.Left := Edit13.Left;
    Edit24.Left := Edit13.Left;
    Edit25.Left := Edit13.Left;
    Edit26.Left := Edit13.Left;
    Edit27.Left := Edit13.Left + Edit13.Width;
    Edit28.Left := Edit15.Left + Edit15.Width;
    Edit29.Left := Edit17.Left + Edit17.Width;
    Edit30.Left := Edit19.Left + Edit19.Width;
    Edit31.Left := Edit21.Left + Edit21.Width;
    Edit32.Left := Edit23.Left + Edit23.Width;
    Edit33.Left := Edit25.Left + Edit25.Width;
    Panel1.Width := Image1.Width;
    Panel1.Height := Image1.Height - 3;
    Panel1.Top := Image1.Top;
    Panel1.Left := Image1.Left;
    Image24.Top := Edit13.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image24.Left := RichEdit1.Left - Panel1.Left;
    Image25.Top := Edit15.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image25.Left := RichEdit1.Left - Panel1.Left;
    Image26.Top := Edit17.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image26.Left := RichEdit1.Left - Panel1.Left;
    Image27.Top := Edit19.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image27.Left := RichEdit1.Left - Panel1.Left;
    Image28.Top := Edit21.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image28.Left := RichEdit1.Left - Panel1.Left;
    Image29.Top := Edit23.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image29.Left := RichEdit1.Left - Panel1.Left;
    Image30.Top := Edit25.Top - Panel1.Top + (Edit13.Height + Edit14.Height - Image24.Height) div 2;
    Image30.Left := RichEdit1.Left - Panel1.Left;
    Button36.Left := Edit26.Left + Edit26.Width - Button36.Width;
    Button36.Top :=
        (Edit26.Top + Edit26.Height)
            + (Panel1.Top + Panel1.Height - (Edit26.Top + Edit26.Height) - Button36.Height) div 2;
    WorkBitmap3.Width := Image6.Width;
    WorkBitmap3.Height := Image6.Height;
    ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 162);
    for I := 1 to 7 do
    begin
      DamageMode := I;
      OrbEnemies[DamageMode] := 0;
      case DamageMode of
        1: Image24.Picture.Bitmap := WorkBitmap3;
        2: Image25.Picture.Bitmap := WorkBitmap3;
        3: Image26.Picture.Bitmap := WorkBitmap3;
        4: Image27.Picture.Bitmap := WorkBitmap3;
        5: Image28.Picture.Bitmap := WorkBitmap3;
        6: Image29.Picture.Bitmap := WorkBitmap3;
        7: Image30.Picture.Bitmap := WorkBitmap3;
      end;
    end;
    RichEdit1.Text := ListBox2.Items[180];
    OrbRow := 1;
    for I := 1 to 121 do
    begin
      DrawIndex := I;
      case Maps[Hero.floor, DrawIndex + 1] of
        tileGreenSlime..tileVampire:
        begin
          NeighborIndex := (Maps[Hero.floor, DrawIndex + 1] - tileGreenSlime) div 2;
          yousya;
        end;
        tileOctopusMouth:
        begin
          NeighborIndex := Ord(monsterOctopus);
          yousya;
        end;
        tileDragonHead:
        begin
          NeighborIndex := Ord(monsterDragon);
          yousya;
        end;
        tileGoldenKnight..tileGateKeeperA:
        begin
          NeighborIndex :=
              (Maps[Hero.floor, DrawIndex + 1] - tileGoldenKnight) div 2 + Ord(monsterGoldenKnight);
          yousya;
        end;
      end;
    end;
    Panel1.Visible := True;
    RichEdit1.Visible := True;
    Edit13.Visible := True;
    Edit14.Visible := True;
    Edit15.Visible := True;
    Edit16.Visible := True;
    Edit17.Visible := True;
    Edit18.Visible := True;
    Edit19.Visible := True;
    Edit20.Visible := True;
    Edit21.Visible := True;
    Edit22.Visible := True;
    Edit23.Visible := True;
    Edit24.Visible := True;
    Edit25.Visible := True;
    Edit26.Visible := True;
    Edit27.Visible := True;
    Edit28.Visible := True;
    Edit29.Visible := True;
    Edit30.Visible := True;
    Edit31.Visible := True;
    Edit32.Visible := True;
    Edit33.Visible := True;
    Button36.Visible := True;
    Button36.SetFocus;
  end;
end;

procedure TTSW10.Button36Click(Sender: TObject);
begin
  RichEdit1.Visible := False;
  Image24.Visible := False;
  Image25.Visible := False;
  Image26.Visible := False;
  Image27.Visible := False;
  Image28.Visible := False;
  Image29.Visible := False;
  Image30.Visible := False;
  Edit13.Visible := False;
  Edit14.Visible := False;
  Edit15.Visible := False;
  Edit16.Visible := False;
  Edit17.Visible := False;
  Edit18.Visible := False;
  Edit19.Visible := False;
  Edit20.Visible := False;
  Edit21.Visible := False;
  Edit22.Visible := False;
  Edit23.Visible := False;
  Edit24.Visible := False;
  Edit25.Visible := False;
  Edit26.Visible := False;
  Edit27.Visible := False;
  Edit28.Visible := False;
  Edit29.Visible := False;
  Edit30.Visible := False;
  Edit31.Visible := False;
  Edit32.Visible := False;
  Edit33.Visible := False;
  Edit13.Text := '';
  Edit14.Text := '';
  Edit15.Text := '';
  Edit16.Text := '';
  Edit17.Text := '';
  Edit18.Text := '';
  Edit19.Text := '';
  Edit20.Text := '';
  Edit21.Text := '';
  Edit22.Text := '';
  Edit23.Text := '';
  Edit24.Text := '';
  Edit25.Text := '';
  Edit26.Text := '';
  Edit27.Text := '';
  Edit28.Text := '';
  Edit29.Text := '';
  Edit30.Text := '';
  Edit31.Text := '';
  Edit32.Text := '';
  Edit33.Text := '';
  case GameOptions[optionDisplaySize] of
    display640x400:
    begin
      RichEdit1.Height := 200;
      RichEdit1.Width := 382;
      RichEdit1.Top := 45;
      RichEdit1.Left := 129;
    end;
    display800x500:
    begin
      RichEdit1.Height := 250;
      RichEdit1.Width := 478;
      RichEdit1.Top := 56;
      RichEdit1.Left := 161;
    end;
  end;
  Button36.Visible := False;
  Panel1.Visible := False;
  itemlive;
  keydisplay;
  Timer1.Enabled := True;
  RichEdit1.Font.Size := GameOptions[optionLargeFont];
end;

procedure TTSW10.mazyutu1; { $0044C5C4 }
begin
  case TileClass of
    110:
    begin
      case Hero.floor of
        47:
        begin
          case Hero.y of
            1..9:
            begin
              case Hero.x + Hero.y * BoardWidth + Damage of
                0..121:
                begin
                  if Maps[Hero.floor, Hero.x + Hero.y * BoardWidth + Damage + MapTileOffset]
                      = tileRoad then
                  begin
                    { PushCommand(0, 0, 0). }
                    Inc(EventCursor);
                    EventStack[EventCursor].Opcode := Ord(evWait);
                    EventStack[EventCursor].A := 0;
                    EventStack[EventCursor].B := 0;
                    { PushCommand(12, Hero.y * 11 + Hero.x + Damage div 2, Hero.y * 11 + Hero.x + Damage). }
                    Inc(EventCursor);
                    EventStack[EventCursor].Opcode := Ord(evMoveMonster);
                    EventStack[EventCursor].A := Hero.y * BoardWidth + Hero.x + Damage div 2;
                    EventStack[EventCursor].B := Hero.y * BoardWidth + Hero.x + Damage;
                    { PushCommand(0, 0, 0). }
                    Inc(EventCursor);
                    EventStack[EventCursor].Opcode := Ord(evWait);
                    EventStack[EventCursor].A := 0;
                    EventStack[EventCursor].B := 0;
                    { PushCommand(1, 2, 0). }
                    Inc(EventCursor);
                    EventStack[EventCursor].Opcode := Ord(evSound);
                    EventStack[EventCursor].A := 2;
                    EventStack[EventCursor].B := 0;
                  end;
                end;
              end;
            end;
          end;
        end;
      end;
      if Hero.sacred_shield = 0 then
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(16, Smallint((Hero.cycle_factor_minus_one + 1) * (-200)), 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evChangeHP);
        EventStack[EventCursor].A := Smallint((Hero.cycle_factor_minus_one + 1) * (-200));
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(2, magician message for this cycle, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        if Hero.cycle_factor_minus_one = 0 then
          EventStack[EventCursor].A := TileClass
        else
          EventStack[EventCursor].A := TileClass + 28;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 6, facing damage frame). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 6;
        case Hero.facing of
          Ord(hfDown): EventStack[EventCursor].B := 191;
          Ord(hfLeft): EventStack[EventCursor].B := 199;
          Ord(hfRight): EventStack[EventCursor].B := 207;
          Ord(hfUp): EventStack[EventCursor].B := 215;
        end;
        { PushCommand(9, ScratchIndex, facing damage frame). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ScratchIndex;
        case Hero.facing of
          Ord(hfDown): EventStack[EventCursor].B := 192;
          Ord(hfLeft): EventStack[EventCursor].B := 200;
          Ord(hfRight): EventStack[EventCursor].B := 208;
          Ord(hfUp): EventStack[EventCursor].B := 216;
        end;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
      end;
      timer2on;
      TileClass := 0;
      NeighborY := 1;
    end;
    111:
    begin
      if Hero.sacred_shield = 0 then
      begin
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(16, Smallint((Hero.cycle_factor_minus_one + 1) * (-100)), 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evChangeHP);
        EventStack[EventCursor].A := Smallint((Hero.cycle_factor_minus_one + 1) * (-100));
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(2, magician message for this cycle, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        if Hero.cycle_factor_minus_one = 0 then
          EventStack[EventCursor].A := TileClass
        else
          EventStack[EventCursor].A := TileClass + 28;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 6, facing damage frame). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 6;
        case Hero.facing of
          Ord(hfDown): EventStack[EventCursor].B := 191;
          Ord(hfLeft): EventStack[EventCursor].B := 199;
          Ord(hfRight): EventStack[EventCursor].B := 207;
          Ord(hfUp): EventStack[EventCursor].B := 215;
        end;
        { PushCommand(9, ScratchIndex, facing damage frame). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evOverlay);
        EventStack[EventCursor].A := ScratchIndex;
        case Hero.facing of
          Ord(hfDown): EventStack[EventCursor].B := 192;
          Ord(hfLeft): EventStack[EventCursor].B := 200;
          Ord(hfRight): EventStack[EventCursor].B := 208;
          Ord(hfUp): EventStack[EventCursor].B := 216;
        end;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
      end;
      timer2on;
      TileClass := 0;
      NeighborY := 1;
    end;
  end;
end;

procedure TTSW10.yusyaidou; { $00443808; walking frame }
begin
  if NeighborIndex mod (Image6.Width div 4) = 0 then
  begin
    case Hero.facing of
      Ord(hfDown):
      begin
        ScratchIndex := 184;
        DoorOpened := 0;
        yusyai1;
      end;
      Ord(hfLeft):
      begin
        ScratchIndex := 192;
        DoorOpened := 0;
        yusyai2;
      end;
      Ord(hfRight):
      begin
        ScratchIndex := 200;
        DoorOpened := 0;
        yusyai3;
      end;
      Ord(hfUp):
      begin
        ScratchIndex := 208;
        DoorOpened := 0;
        yusyai4;
      end;
    end;
    MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
  end
  else
  begin
    case Hero.facing of
      Ord(hfDown):
      begin
        ScratchIndex := 186;
        DoorOpened := 1;
        yusyai1;
      end;
      Ord(hfLeft):
      begin
        ScratchIndex := 194;
        DoorOpened := 1;
        yusyai2;
      end;
      Ord(hfRight):
      begin
        ScratchIndex := 202;
        DoorOpened := 1;
        yusyai3;
      end;
      Ord(hfUp):
      begin
        ScratchIndex := 210;
        DoorOpened := 1;
        yusyai4;
      end;
    end;
    MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
  end;
  if NeighborIndex = Image6.Width then
  begin
    case Hero.facing of
      Ord(hfDown):
      begin
        ScratchIndex := 186;
        DoorOpened := 1;
        yusyai1;
      end;
      Ord(hfLeft):
      begin
        ScratchIndex := 194;
        DoorOpened := 1;
        yusyai2;
      end;
      Ord(hfRight):
      begin
        ScratchIndex := 202;
        DoorOpened := 1;
        yusyai3;
      end;
      Ord(hfUp):
      begin
        ScratchIndex := 210;
        DoorOpened := 1;
        yusyai4;
      end;
    end;
    MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
  end;
end;
procedure TTSW10.yusyai1;
begin
  { Prepare the two neighboring tiles and composite the moving hero. }
  WorkBitmap1.Height := Image6.Height * 2;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap2.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex + 1);
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      0,
      0,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
  );
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      0,
      Image6.Height,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + 2 + 11] - 1
  );
  WorkBitmap2.Canvas.CopyMode := cmSrcPaint;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap3.Canvas.CopyMode := cmNotSrcCopy;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := cmSrcPaint;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := Rect(0, NeighborIndex, Image6.Width, Image6.Height + NeighborIndex);
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := cmSrcAnd;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
end;
procedure TTSW10.yusyai2;
begin
  { Prepare the two neighboring tiles and composite the moving hero. }
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap1.Width := Image6.Width * 2;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap2.Width;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex + 1);
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      Image6.Width,
      0,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
  );
  ImageList1
      .Draw(WorkBitmap1.Canvas, 0, 0, Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + 2 - 1] - 1);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(Image6.Width - NeighborIndex, 0, Image6.Width * 2 - NeighborIndex, Image6.Height);
  kasanegaki;
end;
procedure TTSW10.yusyai3;
begin
  { Prepare the two neighboring tiles and composite the moving hero. }
  WorkBitmap1.Height := Image6.Height;
  WorkBitmap1.Width := Image6.Width * 2;
  WorkBitmap2.Height := WorkBitmap1.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap3.Height := WorkBitmap1.Height;
  WorkBitmap3.Width := WorkBitmap2.Height;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex + 1);
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      0,
      0,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
  );
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      Image6.Width,
      0,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + 2 + 1] - 1
  );
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := Rect(NeighborIndex, 0, Image6.Width + NeighborIndex, Image6.Height);
  kasanegaki;
end;
procedure TTSW10.yusyai4;
begin
  { Prepare the two neighboring tiles and composite the moving hero. }
  WorkBitmap1.Height := Image6.Height * 2;
  WorkBitmap1.Width := Image6.Width;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap2.Width := WorkBitmap1.Width;
  WorkBitmap3.Height := WorkBitmap2.Height;
  WorkBitmap3.Width := WorkBitmap1.Width;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex + 1);
  ImageList1.Draw(
      WorkBitmap1.Canvas,
      0,
      Image6.Height,
      Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + MapTileOffset] - 1
  );
  ImageList1
      .Draw(WorkBitmap1.Canvas, 0, 0, Maps[Hero.floor, Hero.y * BoardWidth + Hero.x + 2 - 11] - 1);
  WorkBitmap3.Canvas.CopyMode := cmNotSrcCopy;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := cmSrcPaint;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(0, Image6.Height - NeighborIndex, Image6.Width, Image6.Height * 2 - NeighborIndex);
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := cmSrcAnd;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
end;

procedure TTSW10.idou; { $0044C04C }
var
  Steps, I: Longint;
begin
  HeroCell := Hero.y * BoardWidth + Hero.x;
  DrawX := (Hero.y * BoardWidth + Hero.x) * Image6.Width mod (Image6.Width * BoardWidth);
  DrawY :=
      ((Hero.y * BoardWidth + Hero.x) * Image6.Height div (Image6.Height * BoardWidth))
          * Image6.Height;
  case Hero.facing of
    Ord(hfLeft): Dec(DrawX, Image6.Width);
    Ord(hfUp): Dec(DrawY, Image6.Height);
  end;
  Steps := Image6.Width;
  if High1.Checked = True then
    Steps := Steps div 4;
  if Middle1.Checked = True then
    Steps := Steps div 2;
  for I := 1 to Steps do
  begin
    StrikeCount := I;
    NeighborIndex := I;
    if Steps = Image6.Width div 4 then
      NeighborIndex := NeighborIndex * 4;
    if Steps = Image6.Width div 2 then
      NeighborIndex := NeighborIndex * 2;
    yusyaidou;
    MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
  end;
  Hero.x := ContactIndex mod BoardWidth;
  Hero.y := ContactIndex div BoardWidth;
  DrawX := Image6.Width * ContactIndex mod (Image6.Width * BoardWidth);
  DrawY := (Image6.Height * ContactIndex div (Image6.Height * BoardWidth)) * Image6.Height;
  yusyahyouji1;
  NeighborY := 0;
  Damage := 0;
  TileClass := 0;
  ScratchIndex := Hero.y * BoardWidth + Hero.x;
  { Classify each neighbor before applying magician or pincer damage. }
  NeighborIndex := ScratchIndex - BoardWidth;
  case Hero.y of
    1..10:
    begin
      mmes;
      if (TileClass = 110) or (TileClass = 111) then
      begin
        Damage := -22;
        mazyutu1;
      end;
    end;
  end;
  NeighborIndex := ScratchIndex - 1;
  case Hero.x of
    1..10:
    begin
      mmes;
      if (TileClass = 110) or (TileClass = 111) then
      begin
        Damage := -2;
        mazyutu1;
      end;
    end;
  end;
  NeighborIndex := ScratchIndex + (1);
  case Hero.x of
    0..9:
    begin
      mmes;
      if (TileClass = 110) or (TileClass = 111) then
      begin
        Damage := 2;
        mazyutu1;
      end;
    end;
  end;
  NeighborIndex := ScratchIndex + (11);
  case Hero.y of
    0..9:
    begin
      mmes;
      if (TileClass = 110) or (TileClass = 111) then
      begin
        Damage := 22;
        mazyutu1;
      end;
    end;
  end;
  if Hero.sacred_shield = 0 then
  begin
    case Hero.x of
      1..9:
      begin
        if Maps[Hero.floor, ScratchIndex - 1 + MapTileOffset] = tileSorcerer then
          if Maps[Hero.floor, ScratchIndex + 1 + MapTileOffset] = tileSorcerer then
            madoushi1;
      end;
    end;
    case Hero.y of
      1..9:
      begin
        if Maps[Hero.floor, ScratchIndex - BoardWidth + MapTileOffset] = tileSorcerer then
          if Maps[Hero.floor, ScratchIndex + BoardWidth + MapTileOffset] = tileSorcerer then
            madoushi1;
      end;
    end;
  end;
  if NeighborY = 0 then
  begin
    TileClass := 0;
    ScratchIndex := Hero.y * BoardWidth + Hero.x;
    NeighborIndex := ScratchIndex - BoardWidth;
    case Hero.y of
      1..10: mmes;
    end;
    NeighborIndex := ScratchIndex - 1;
    case Hero.x of
      1..10: mmes;
    end;
    NeighborIndex := ScratchIndex + (1);
    case Hero.x of
      0..9: mmes;
    end;
    NeighborIndex := ScratchIndex + (11);
    case Hero.y of
      0..9: mmes;
    end;
    disp;
  end;
end;

procedure TTSW10.kaidanwork; { $00442DC8; spiral stair transition }
var
  I: Longint;
begin
  MapBitmap1.Free;
  MapBitmap2.Free;
  MapBitmap1 := TBitmap.Create;
  MapBitmap2 := TBitmap.Create;
  MapBitmap1.Height := Image6.Height * BoardWidth;
  MapBitmap1.Width := Image6.Width * BoardWidth;
  MapBitmap2.Height := MapBitmap1.Height;
  MapBitmap2.Width := MapBitmap1.Width;
  Timer1.Enabled := False;
  { Queue the new-floor reveal before the old-floor cover: commands run backwards. }
  for I := 1 to 121 do
  begin
    if (Hero.music_track <> 0) and (I = 20) then
    begin
      { PushCommand(15, 0, 0): change music during the reveal. }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evFloorMusic);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
    end;
    { PushCommand(21, 1, 122 - I): reveal the destination floor. }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWipe);
    EventStack[EventCursor].A := 1;
    EventStack[EventCursor].B := 122 - I;
  end;
  for I := 1 to 121 do
  begin
    { PushCommand(21, 0, 122 - I): cover the departing floor. }
    Inc(EventCursor);
    EventStack[EventCursor].Opcode := Ord(evWipe);
    EventStack[EventCursor].A := 0;
    EventStack[EventCursor].B := 122 - I;
  end;
  { PushCommand(0, 0, 0) }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evWait);
  EventStack[EventCursor].A := 0;
  EventStack[EventCursor].B := 0;
  { PushCommand(1, 9, 0): stair sound. }
  Inc(EventCursor);
  EventStack[EventCursor].Opcode := Ord(evSound);
  EventStack[EventCursor].A := 9;
  EventStack[EventCursor].B := 0;
  if High1.Checked = True then
    Timer2.Interval := 2;
  if Middle1.Checked = True then
    Timer2.Interval := 6;
  if Low1.Checked = True then
    Timer2.Interval := 10;
  timer2on;
end;

procedure TTSW10.handan; { $00444490 }
var
  I: Longint;
begin
  case Ord(Maps[Hero.floor, ContactIndex + MapTileOffset]) of
    tileYellowDoor..tileRedDoor:
    begin
      DoorOpened := 0;
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileYellowDoor:
        begin
          TileClass := 16;
          if Hero.yellow_keys > 0 then
          begin
            DoorOpened := 1;
            Dec(Hero.yellow_keys);
            TileClass := 4;
          end;
        end;
        tileBlueDoor:
        begin
          TileClass := 17;
          if Hero.blue_keys > 0 then
          begin
            DoorOpened := 1;
            Dec(Hero.blue_keys);
            TileClass := 5;
          end;
        end;
        tileRedDoor:
        begin
          TileClass := 18;
          if Hero.red_keys > 0 then
          begin
            DoorOpened := 1;
            Dec(Hero.red_keys);
            TileClass := 6;
          end;
        end;
      end;
      doorcheck;
      if DoorOpened = 1 then
      begin
        { PushCommand(2, TileClass, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := TileClass;
        EventStack[EventCursor].B := 0;
        { PushCommand(8, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evShowPanels);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(13, ContactIndex, Maps[Hero.floor, ContactIndex + 2]). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evDoorFrame);
        EventStack[EventCursor].A := ContactIndex;
        EventStack[EventCursor].B := Maps[Hero.floor, ContactIndex + MapTileOffset];
        doorstackin;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 1, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 1;
        EventStack[EventCursor].B := 0;
        timer2on;
      end
      else
      begin
        { PushCommand(2, TileClass, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := TileClass;
        EventStack[EventCursor].B := 0;
        timer2on;
      end;
    end;
    tileRoad: idou;
    tileSpecialRoad: mevent;
    tileSecretWall:
    begin
      timer2on;
      TileClass := 1;
      MessageText := ListBox2.Items[137];
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, 1, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(13, ContactIndex, 7). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDoorFrame);
      EventStack[EventCursor].A := ContactIndex;
      EventStack[EventCursor].B := 7;
      doorstackin;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 1, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 1;
      EventStack[EventCursor].B := 0;
    end;
    tileHiddenObject:
    begin
      case Hero.floor of
        12:
        begin
          if ContactIndex = 10 then
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 10, 19). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := tileMerchant;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
        16:
        begin
          if ContactIndex = 120 then
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 120, 25). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 120;
            EventStack[EventCursor].B := tileOldMan;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
        19:
        begin
          if ContactIndex = 27 then
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 27, 39). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 27;
            EventStack[EventCursor].B := tileCross;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
        41:
        begin
          if Maps[41, 14] = tileRoad then
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, 20, 151). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := 20;
            EventStack[EventCursor].B := tileMagicianA;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            timer2on;
          end;
        end;
      end;
    end;
    tileStairsUp..tileStairsDown:
    begin
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      if Hero.music_track <> 0 then
      begin
        Timer1.Enabled := False;
        MediaPlayer5.Close;
      end;
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileStairsUp:
        begin
          MonsterIndex := -1;
          monshyouji;
          TileClass := 1;
          MessageText := ListBox2.Items[243];
          disp;
          if (Hero.floor = 20) and (Maps[20, 51] = tileFairy) then
            Maps[20, 51] := tileRoad;
          if (Hero.floor = 25) and (Maps[25, 73] = tileFairy) then
            Maps[25, 73] := tileRoad;
          if (Hero.floor = 40) and (Maps[40, 62] = tileFairy) then
            Maps[40, 62] := tileRoad;
          if Hero.floor = 43 then
            Hero.floor := 45
          else
            Inc(Hero.floor);
          if Hero.highest_floor < Hero.floor then
          begin
            Hero.highest_floor := Hero.floor;
            if Hero.Word140 = 35 then
              if Maps[35, 93] + Maps[2, 122] = 27 then
                Maps[2, 122] := tileRoad;
          end;
          Hero.x := Maps[Hero.floor, 0] mod BoardWidth;
          Hero.y := Maps[Hero.floor, 0] div BoardWidth;
          kaidanupcheck;
          if (Hero.floor = 32) and (Hero.floor32_arrival_seen = 0) then
          begin
            mevent;
            Hero.floor32_arrival_seen := 1;
          end;
          if (Hero.floor = 42) and (Hero.Word524 = 0) then
          begin
            mevent;
            Hero.Word524 := 1;
          end;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(2, 7, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
          EventStack[EventCursor].A := 7;
          EventStack[EventCursor].B := 0;
        end;
        tileStairsDown:
        begin
          MonsterIndex := -1;
          monshyouji;
          TileClass := 1;
          MessageText := ListBox2.Items[243];
          disp;
          if (Hero.floor = 25) and (Maps[25, 73] = tileFairy) then
            Maps[25, 73] := tileRoad;
          if (Hero.floor = 49) and (Maps[49, 18] = tileFairy) then
            Maps[49, 18] := tileRoad;
          if Hero.floor = 45 then
            Hero.floor := 43
          else
            Dec(Hero.floor);
          if (Hero.highest_floor = 29) and (Hero.floor = 28) then
          begin
            Maps[29, 40] := tileRoad;
            Maps[29, 29] := tileRoad;
            Maps[29, 19] := tileThief;
          end;
          Hero.x := Maps[Hero.floor, 1] mod BoardWidth;
          Hero.y := Maps[Hero.floor, 1] div BoardWidth;
          kaidandowncheck;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(2, 8, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
          EventStack[EventCursor].A := 8;
          EventStack[EventCursor].B := 0;
        end;
      end;
      kaidanwork;
      MonsterIndex := -1;
      monshyouji;
      itemlive;
      timer2on;
    end;
    tileAltar:
    begin
      RichEdit1.Font.Size := GameOptions[optionLargeFont];
      ShopMode := Ord(shopAltar);
      itemdel;
      GameplayShopCost := ((Hero.Word44 + 1) * (Hero.Word44 + 1) - (Hero.Word44 + 1) + 2) * 10;
      RichEdit1.Text :=
          ListBox2.Items[202] + ' ' + IntToStr(GameplayShopCost) + ' ' + ListBox2.Items[203];
      DialogueStage := stageAltar;
      case GameOptions[optionDisplaySize] of
        display640x400:
        begin
          RichEdit1.Height := 200;
          RichEdit1.Width := 382;
          RichEdit1.Top := 45;
          RichEdit1.Left := 129;
        end;
        display800x500:
        begin
          RichEdit1.Height := 250;
          RichEdit1.Width := 478;
          RichEdit1.Top := 56;
          RichEdit1.Left := 161;
        end;
      end;
      Button7.Top := RichEdit1.Top + RichEdit1.Height - Button7.Height - Image6.Height div 2;
      Button7.Left := RichEdit1.Left + RichEdit1.Width - Button7.Width - Image6.Height div 2;
      Button2.Top := RichEdit1.Top + RichEdit1.Height - Button2.Height - Image6.Height div 2;
      Button2.Left := Button7.Left - Button2.Width - 16;
      RichEdit1.Visible := True;
      Button2.Visible := True;
      Button7.Visible := True;
      Button2.SetFocus;
    end;
    tileMerchant..tileMerchant2: syounin;
    tileThief..tileThief2: touzoku;
    tileFairy..tileFairy2: yousei;
    tileOldMan..tileOldMan2: roujin;
    tileTimeGate..tileTimeGate2:
    begin
      if Hero.music_track <> 0 then
        if Hero.music_track <> 13 then
        begin
          MediaPlayer5.Close;
          Hero.music_track := 13;
          soundplay;
        end;
      if Maps[25, 62] = tileRoad then
      begin
        Maps[24, 6] := tileWall;
        Maps[24, 8] := tileWall;
        Maps[24, 18] := tileRoad;
        Maps[24, 29] := tileRoad;
        Maps[24, 40] := tileRoad;
        Maps[24, 7] := tileSpecialRoad;
      end;
      Maps[50, 51] := tileThief;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(6, 60, 27). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSetTile);
      EventStack[EventCursor].A := 60;
      EventStack[EventCursor].B := tileTimeGate;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 26, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechHeroFindsDoll;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(10, 25, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evDialogue);
      EventStack[EventCursor].A := speechTimeGateInvitation;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      timer2on;
      Button1.Caption := 'OK';
    end;
    tileYellowKey..tileBlueKey:
    begin
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileYellowKey:
        begin
          Inc(Hero.yellow_keys);
          TileClass := 1;
          MessageText := ListBox2.Items[128];
        end;
        tileRedKey:
        begin
          Inc(Hero.red_keys);
          TileClass := 1;
          MessageText := ListBox2.Items[130];
        end;
        tileBlueKey:
        begin
          Inc(Hero.blue_keys);
          TileClass := 1;
          MessageText := ListBox2.Items[129];
        end;
      end;
      timer2on;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      Maps[Hero.floor, ContactIndex + MapTileOffset] := tileRoad;
      idou;
    end;
    tileRedPotion..tileLuckyGold:
    begin
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileRedPotion:
        begin
          Hero.hp := Hero.hp + (Hero.floor + 9) div 10 * 50 * (Hero.cycle_factor_minus_one + 1);
          TileClass := 1;
          MessageText :=
              ListBox2.Items[162]
                  + ' '
                  + IntToStr((Hero.floor + 9) div 10 * 50 * (Hero.cycle_factor_minus_one + 1))
                  + ListBox2.Items[166];
        end;
        tileBluePotion:
        begin
          Hero.hp := Hero.hp + (Hero.floor + 9) div 10 * 200 * (Hero.cycle_factor_minus_one + 1);
          TileClass := 1;
          MessageText :=
              ListBox2.Items[163]
                  + ' '
                  + IntToStr((Hero.floor + 9) div 10 * 200 * (Hero.cycle_factor_minus_one + 1))
                  + ListBox2.Items[166];
        end;
        tileRedGem:
        begin
          Hero.attack := Hero.attack + (Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1);
          TileClass := 1;
          if (Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1) = 1 then
            MessageText :=
                ListBox2.Items[164]
                    + ' '
                    + IntToStr((Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1))
                    + ' point up!'
          else
            MessageText :=
                ListBox2.Items[164]
                    + ' '
                    + IntToStr((Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1))
                    + ListBox2.Items[166];
        end;
        tileBlueGem:
        begin
          Hero.defense :=
              Hero.defense + (Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1);
          TileClass := 1;
          if (Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1) = 1 then
            MessageText :=
                ListBox2.Items[165]
                    + ' '
                    + IntToStr((Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1))
                    + ' point up!'
          else
            MessageText :=
                ListBox2.Items[165]
                    + ' '
                    + IntToStr((Hero.floor + 9) div 10 * (Hero.cycle_factor_minus_one + 1))
                    + ListBox2.Items[166];
        end;
        tileWisdomOrb:
        begin
          Hero.wisdom_orb := 1;
          TileClass := 22;
        end;
        tileFlightOrb:
        begin
          Hero.flight_orb := 1;
          TileClass := 21;
        end;
        tileCross:
        begin
          Hero.cross := 1;
          TileClass := 40;
        end;
        tileElixir:
        begin
          Hero.elixir := 1;
          TileClass := 41;
        end;
        tileMattock:
        begin
          Hero.mattock := 1;
          TileClass := 42;
        end;
        tileBomb:
        begin
          Hero.bomb := 1;
          TileClass := 43;
        end;
        tileWarpStaff:
        begin
          Hero.warp_staff := 3;
          TileClass := 44;
        end;
        tileAscentWing:
        begin
          Hero.ascent_wing := 1;
          TileClass := 45;
        end;
        tileDescentWing:
        begin
          Hero.descent_wing := 1;
          TileClass := 46;
        end;
        tileDragonSlayer:
        begin
          Hero.dragon_slayer := 1;
          TileClass := 47;
        end;
        tileSnowCrystal:
        begin
          Hero.snow_crystal := 1;
          TileClass := 48;
        end;
        tileMagicKey:
        begin
          Hero.magic_key := 1;
          TileClass := 49;
        end;
        tileSuperMattock:
        begin
          Hero.super_mattock := 1;
          TileClass := 50;
        end;
        tileLuckyGold:
        begin
          Hero.lucky_gold := 1;
          TileClass := 51;
        end;
      end;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      timer2on;
      Maps[Hero.floor, ContactIndex + MapTileOffset] := tileRoad;
      idou;
    end;
    tileIronSword..tileSacredShield:
    begin
      case Maps[Hero.floor, ContactIndex + MapTileOffset] of
        tileIronSword:
        begin
          Hero.attack := Hero.attack + (Hero.cycle_factor_minus_one + 1) * 10;
          Hero.sword := Ord(equipmentIron);
          Hero.Word128 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[152]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 10)
                  + ListBox2.Items[166];
        end;
        tileSilverSword:
        begin
          Hero.attack := Hero.attack + (Hero.cycle_factor_minus_one + 1) * 20;
          Hero.sword := Ord(equipmentSilver);
          Hero.Word132 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[153]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 20)
                  + ListBox2.Items[166];
        end;
        tileKnightSword:
        begin
          Hero.attack := Hero.attack + (Hero.cycle_factor_minus_one + 1) * 40;
          Hero.sword := Ord(equipmentKnight);
          Hero.Word136 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[154]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 40)
                  + ListBox2.Items[166];
        end;
        tileHolySword:
        begin
          Hero.attack := Hero.attack + (Hero.cycle_factor_minus_one + 1) * 50;
          Hero.sword := Ord(equipmentHoly);
          Hero.Word140 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[155]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 50)
                  + ListBox2.Items[166];
        end;
        tileSacredSword:
        begin
          Hero.attack := Hero.attack + (Hero.cycle_factor_minus_one + 1) * 100;
          Hero.sword := Ord(equipmentSacred);
          Hero.Word144 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[156]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 100)
                  + ListBox2.Items[166];
        end;
        tileIronShield:
        begin
          Hero.defense := Hero.defense + (Hero.cycle_factor_minus_one + 1) * 10;
          Hero.shield := Ord(equipmentIron);
          Hero.Word148 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[157]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 10)
                  + ListBox2.Items[166];
        end;
        tileSilverShield:
        begin
          Hero.defense := Hero.defense + (Hero.cycle_factor_minus_one + 1) * 20;
          Hero.shield := Ord(equipmentSilver);
          Hero.Word152 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[158]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 20)
                  + ListBox2.Items[166];
        end;
        tileKnightShield:
        begin
          Hero.defense := Hero.defense + (Hero.cycle_factor_minus_one + 1) * 40;
          Hero.shield := Ord(equipmentKnight);
          Hero.Word156 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[159]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 40)
                  + ListBox2.Items[166];
        end;
        tileHolyShield:
        begin
          Hero.defense := Hero.defense + (Hero.cycle_factor_minus_one + 1) * 50;
          Hero.shield := Ord(equipmentHoly);
          Hero.Word160 := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[160]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 50)
                  + ListBox2.Items[166];
        end;
        tileSacredShield:
        begin
          Hero.defense := Hero.defense + (Hero.cycle_factor_minus_one + 1) * 100;
          Hero.shield := Ord(equipmentSacred);
          Hero.sacred_shield := 1;
          TileClass := 1;
          MessageText :=
              ListBox2.Items[161]
                  + ' '
                  + IntToStr((Hero.cycle_factor_minus_one + 1) * 100)
                  + ListBox2.Items[166];
        end;
      end;
      timer2on;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;
      Maps[Hero.floor, ContactIndex + MapTileOffset] := tileRoad;
      idou;
    end;
    tileGreenSlime..tileRock + 1: taisen;
    tileZeno..tileZeno + 1:
    begin
      case Hero.floor of
        49: taisen;
        50:
        begin
          if Hero.cycle_factor_minus_one <> 0 then
          begin
            if Hero.later_cycle = 0 then
            begin
              Monsters[15].HP := 1000;
              Monsters[15].Attack := 625;
              Monsters[15].Defense := 125;
            end;
            taisen;
          end
          else
          begin
            if Hero.music_track <> 0 then
            begin
              Timer1.Enabled := False;
              MediaPlayer5.Close;
            end;
            Timer1.Enabled := False;
            timer2on;
            Button1.Caption := 'OK';
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 8, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 8;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 7, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 7;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 0;
            { The first-cycle ending is queued backwards: collapse, flashes, then dialogue. }
            for I := 1 to 400 do
            begin
              { PushCommand(0, 5, 0). }
              Inc(EventCursor);
              EventStack[EventCursor].Opcode := Ord(evWait);
              EventStack[EventCursor].A := 5;
              EventStack[EventCursor].B := 0;
              { PushCommand(11, 12, 401 - I). }
              Inc(EventCursor);
              EventStack[EventCursor].Opcode := Ord(evSceneAction);
              EventStack[EventCursor].A := 12;
              EventStack[EventCursor].B := 401 - I;
            end;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 400). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 400;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 399). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 399;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 396). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 396;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 393). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 393;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 390). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 390;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 387). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 387;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 384). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 384;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 381). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 381;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 378). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 378;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 375). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 375;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 372). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 372;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 369). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 369;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 366). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 366;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 363). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 363;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 360). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 360;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 357). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 357;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 354). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 354;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 351). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 351;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 348). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 348;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 345). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 345;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 342). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 342;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 339). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 339;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 336). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 336;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 333). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 333;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 330). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 330;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 327). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 327;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 324). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 324;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 321). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 321;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 318). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 318;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 315). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 315;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 312). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 312;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 309). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 309;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 306). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 306;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 303). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 303;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 300). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 300;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 295). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 295;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 290). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 290;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 285). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 285;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 280). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 280;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 275). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 275;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 270). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 270;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 265). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 265;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 260). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 260;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 255). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 255;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 250). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 250;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 245). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 245;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 240). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 240;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 235). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 235;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 230). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 230;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 225). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 225;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 220). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 220;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 215). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 215;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 210). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 210;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 205). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 205;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 197). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 197;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 189). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 189;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 181). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 181;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 173). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 173;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 165). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 165;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 157). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 157;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 149). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 149;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 141). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 141;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 133). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 133;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 125). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 125;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 117). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 117;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 109). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 109;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 101). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 101;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 91). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 91;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 81). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 81;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 71). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 71;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 61). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 61;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 51). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 51;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 41). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 41;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 31). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 31;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 21). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 21;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 11). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 11;
            { PushCommand(0, 4, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 4;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 1). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 1;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 17). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 17;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 16). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 16;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 15). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 15;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 14). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 14;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 13). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 13;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 12). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 12;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 11). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 11;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 10). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 10;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 9). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 9;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 8). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 8;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 7). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 7;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 6;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 5). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 5;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 4). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 4;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 3). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 3;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 2). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 2;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 10, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 10;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 6, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 6;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 1). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 1;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 247). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 247;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 246). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 246;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 245). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 245;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 244). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 244;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 243). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 243;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 242). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 242;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 241). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 241;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 240). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 240;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 239). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 239;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 238). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 238;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 237). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 237;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 236). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 236;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 235). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 235;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 234). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 234;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 233). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 233;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 12, 232). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 12;
            EventStack[EventCursor].B := 232;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 1, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 1;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 15, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 15;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(11, 14, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSceneAction);
            EventStack[EventCursor].A := 14;
            EventStack[EventCursor].B := 0;
          end;
        end;
      end;
    end;
    tileSorcerer..tileOctopusLast: taisen;
    tileDragonHead: taisen;
    tileGoldenKnight..tileGateKeeperA: taisen;
  end;
end;

procedure TTSW10.img8work;
begin
  if Hero.elixir = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemElixir);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image8.Left - Image6.Width div 2;
    Button37.Top := Image8.Top + Image8.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img9work;
begin
  if Hero.mattock = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemMattock);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image9.Left - Image6.Width div 2;
    Button37.Top := Image9.Top + Image9.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img10work;
begin
  if Hero.bomb = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemBomb);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image10.Left - Image6.Width div 2;
    Button37.Top := Image10.Top + Image10.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img11work;
begin
  if Hero.warp_staff >= 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemWarpStaff);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image11.Left - Image6.Width div 2;
    Button37.Top := Image11.Top + Image11.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img12work;
begin
  if Hero.ascent_wing = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemAscentWing);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image12.Left - Image6.Width div 2;
    Button37.Top := Image12.Top + Image12.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img13work;
begin
  if Hero.descent_wing = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemDescentWing);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image13.Left - Image6.Width div 2;
    Button37.Top := Image13.Top + Image13.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img15work;
begin
  if Hero.snow_crystal = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemSnowCrystal);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image15.Left - Image6.Width div 2;
    Button37.Top := Image15.Top + Image15.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img16work;
begin
  if Hero.magic_key = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemMagicKey);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image16.Left - Image6.Width div 2;
    Button37.Top := Image16.Top + Image16.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;
procedure TTSW10.img17work;
begin
  if Hero.super_mattock = 1 then
  begin
    itemdel;
    GameplayItemChoice := Ord(itemSuperMattock);
    Button37.Height := Image6.Height div 2;
    Button37.Width := Image6.Width * 2;
    Button37.Left := Image17.Left - Image6.Width div 2;
    Button37.Top := Image17.Top + Image17.Height;
    Button38.Height := Button37.Height;
    Button38.Width := Button37.Width;
    Button38.Left := Button37.Left;
    Button38.Top := Button37.Top + Button37.Height;
    Button37.Visible := True;
    Button38.Visible := True;
    Button37.SetFocus;
  end;
end;

procedure TTSW10.Button38Click(Sender: TObject); { $00450BA0 }
var
  X, Y: Longint;
begin
  Button37.Visible := False;
  Button38.Visible := False;
  case GameplayItemChoice of
    Ord(itemElixir):
    begin
      TileClass := 1;
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(1, 2, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSound);
      EventStack[EventCursor].A := 2;
      EventStack[EventCursor].B := 0;

      ScratchIndex := Hero.attack * 10 + Hero.defense * 5;
      MessageText := ListBox2.Items[186] + ' ' + IntToStr(ScratchIndex) + ListBox2.Items[166];
      Hero.hp := Hero.hp + ScratchIndex;
      Hero.elixir := 0;
      EventPaused := 0;
    end;
    Ord(itemMattock):
    begin
      timer2on;
      { PushCommand(2, 60, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 60;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      TileClass := 0;
      { Inspect south, east, west, north in the original order. }
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex + BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        0..9:
        begin
          mmmes;
          if TileClass = 1 then
          begin
            matokwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex + 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        0..9:
        begin
          mmmes;
          if TileClass = 1 then
          begin
            matokwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex - 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        1..10:
        begin
          mmmes;
          if TileClass = 1 then
          begin
            matokwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex - BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        1..10:
        begin
          mmmes;
          if TileClass = 1 then
          begin
            matokwork;
          end;
        end;
      end;
      Hero.mattock := 0;
    end;
    Ord(itemBomb):
    begin
      timer2on;
      { PushCommand(0, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evWait);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(11, 5, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evSceneAction);
      EventStack[EventCursor].A := 5;
      EventStack[EventCursor].B := 0;
      { PushCommand(2, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      GameplayShopCost := 0;
      TileClass := 0;
      { Inspect south, east, west, north in the original order. }
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex + BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        0..9:
        begin
          mmmes;
          if TileClass = 2 then
          begin
            GameplayShopCost := GameplayShopCost + Monsters[MonsterIndex].Gold;
            toroad2;
          end;
        end;
      end;
      NeighborIndex := ScratchIndex + 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        0..9:
        begin
          mmmes;
          if TileClass = 2 then
          begin
            GameplayShopCost := GameplayShopCost + Monsters[MonsterIndex].Gold;
            toroad2;
          end;
        end;
      end;
      NeighborIndex := ScratchIndex - 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        1..10:
        begin
          mmmes;
          if TileClass = 2 then
          begin
            GameplayShopCost := GameplayShopCost + Monsters[MonsterIndex].Gold;
            toroad2;
          end;
        end;
      end;
      NeighborIndex := ScratchIndex - BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        1..10:
        begin
          mmmes;
          if TileClass = 2 then
          begin
            GameplayShopCost := GameplayShopCost + Monsters[MonsterIndex].Gold;
            toroad2;
          end;
        end;
      end;
      Hero.gold := Hero.gold + GameplayShopCost;
      Hero.bomb := 0;
      TileClass := 1;
      MessageText :=
          ListBox2.Items[188]
              + ListBox2.Items[200]
              + ' '
              + IntToStr(GameplayShopCost)
              + ListBox2.Items[201];
    end;
    Ord(itemWarpStaff):
    begin
      Dec(Hero.warp_staff);
      TileClass := 62;
      FlightCell := Hero.y * BoardWidth + Hero.x;
      ContactIndex := 120 - FlightCell;
      if Maps[Hero.floor, ContactIndex + MapTileOffset] <> tileRoad then
        TileClass := 68
      else
      begin
        DrawX := (FlightCell * Image6.Width) mod (Image6.Width * BoardWidth);
        DrawY := (FlightCell * Image6.Height) div (Image6.Height * BoardWidth) * Image6.Height;
        ImageList1.Draw(
            MapBitmap1.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, FlightCell + MapTileOffset] - 1
        );
        GraphicTile := Maps[Hero.floor, FlightCell + MapTileOffset];
        imagework;
        ImageList1.Draw(
            MapBitmap2.Canvas,
            DrawX,
            DrawY,
            Maps[Hero.floor, FlightCell + MapTileOffset] - 1 + DoorOpened
        );
        Hero.x := ContactIndex mod BoardWidth;
        Hero.y := ContactIndex div BoardWidth;
        DrawX := (ContactIndex * Image6.Width) mod (Image6.Width * BoardWidth);
        DrawY := (ContactIndex * Image6.Height) div (Image6.Height * BoardWidth) * Image6.Height;
        yusyahyouji1;
        MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
        timer2on;
        { PushCommand(1, 2, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
      end;
      itemlive;
      disp;
    end;
    Ord(itemAscentWing):
    begin
      if (Hero.floor <> 50)
          and (Maps[Hero.floor + 1, Hero.y * BoardWidth + Hero.x + MapTileOffset] = tileRoad) then
      begin
        Hero.ascent_wing := 0;
        TileClass := 63;
        Inc(Hero.floor);
        if Hero.music_track <> 0 then
        begin
          soundcheck;
          soundplay;
        end;
        mhyouji;
        timer2on;
        { PushCommand(2, TileClass, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
        EventStack[EventCursor].A := TileClass;
        EventStack[EventCursor].B := 0;
        { PushCommand(8, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evShowPanels);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(0, 0, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evWait);
        EventStack[EventCursor].A := 0;
        EventStack[EventCursor].B := 0;
        { PushCommand(1, 2, 0). }
        Inc(EventCursor);
        EventStack[EventCursor].Opcode := Ord(evSound);
        EventStack[EventCursor].A := 2;
        EventStack[EventCursor].B := 0;
        itemlive;
        disp;
      end
      else
      begin
        TileClass := 69;
        disp;
        itemlive;
      end;
    end;
    Ord(itemDescentWing):
    begin
      case Hero.floor of
        0:
        begin
          TileClass := 70;
          disp;
          itemlive;
        end;
      else
        begin
          if Maps[Hero.floor - 1, Hero.y * BoardWidth + Hero.x + MapTileOffset] = tileRoad then
          begin
            Hero.descent_wing := 0;
            TileClass := 64;
            Dec(Hero.floor);
            if Hero.music_track <> 0 then
            begin
              soundcheck;
              soundplay;
            end;
            mhyouji;
            timer2on;
            { PushCommand(2, TileClass, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
            EventStack[EventCursor].A := TileClass;
            EventStack[EventCursor].B := 0;
            { PushCommand(8, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evShowPanels);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
          end
          else
            TileClass := 70;
          disp;
          itemlive;
        end;
      end;
    end;
    Ord(itemSnowCrystal):
    begin
      timer2on;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      NeighborY := 0;
      { Inspect south, east, west, north in the original order. }
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex + BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        0..9:
        begin
          mmmes;
          if TileClass = 3 then
          begin
            NeighborY := 1;
            DamageMode := 11;
            yukiwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex + 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        0..9:
        begin
          mmmes;
          if TileClass = 3 then
          begin
            NeighborY := 1;
            DamageMode := 10;
            yukiwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex - 1;
      ContactIndex := NeighborIndex;
      case Hero.x of
        1..10:
        begin
          mmmes;
          if TileClass = 3 then
          begin
            NeighborY := 1;
            DamageMode := 9;
            yukiwork;
          end;
        end;
      end;
      ScratchIndex := Hero.y * BoardWidth + Hero.x;
      NeighborIndex := ScratchIndex - BoardWidth;
      ContactIndex := NeighborIndex;
      case Hero.y of
        1..10:
        begin
          mmmes;
          if TileClass = 3 then
          begin
            NeighborY := 1;
            DamageMode := 12;
            yukiwork;
          end;
        end;
      end;
      if NeighborY = 1 then
      begin
        TileClass := 1;
        MessageText := ListBox2.Items[192] + ListBox2.Items[198];
      end
      else
        TileClass := 65;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
    end;
    Ord(itemMagicKey):
    begin
      Hero.magic_key := 0;
      TileClass := 66;
      timer2on;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      for X := 120 downto 0 do
      begin
        DrawIndex := X;
        if Maps[Hero.floor, DrawIndex + MapTileOffset] = tileYellowDoor then
        begin
          { PushCommand(13, DrawIndex, 1). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evDoorFrame);
          EventStack[EventCursor].A := DrawIndex;
          EventStack[EventCursor].B := 1;
          doorstackin;
          { PushCommand(0, 0, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evWait);
          EventStack[EventCursor].A := 0;
          EventStack[EventCursor].B := 0;
          { PushCommand(1, 1, 0). }
          Inc(EventCursor);
          EventStack[EventCursor].Opcode := Ord(evSound);
          EventStack[EventCursor].A := 1;
          EventStack[EventCursor].B := 0;
        end;
      end;
    end;
    Ord(itemSuperMattock):
    begin
      Hero.super_mattock := 0;
      TileClass := 67;
      timer2on;
      { PushCommand(2, TileClass, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evRefreshStatus);
      EventStack[EventCursor].A := TileClass;
      EventStack[EventCursor].B := 0;
      { PushCommand(8, 0, 0). }
      Inc(EventCursor);
      EventStack[EventCursor].Opcode := Ord(evShowPanels);
      EventStack[EventCursor].A := 0;
      EventStack[EventCursor].B := 0;
      for X := 10 downto 0 do
        for Y := 10 downto 0 do
        begin
          DrawIndex := Y * BoardWidth + X;
          if Maps[Hero.floor, DrawIndex + MapTileOffset] = tileWall then
          begin
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(6, DrawIndex, 6). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSetTile);
            EventStack[EventCursor].A := DrawIndex;
            EventStack[EventCursor].B := tileRoad;
            { PushCommand(0, 0, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evWait);
            EventStack[EventCursor].A := 0;
            EventStack[EventCursor].B := 0;
            { PushCommand(1, 2, 0). }
            Inc(EventCursor);
            EventStack[EventCursor].Opcode := Ord(evSound);
            EventStack[EventCursor].A := 2;
            EventStack[EventCursor].B := 0;
          end;
        end;
    end;
  end;
end;

procedure TTSW10.Image4Click(Sender: TObject);
begin
  img4work;
end;
procedure TTSW10.Image5Click(Sender: TObject);
begin
  img5work;
end;
procedure TTSW10.Image6Click(Sender: TObject);
begin
  img6work;
end;
procedure TTSW10.Image8Click(Sender: TObject);
begin
  img8work;
end;
procedure TTSW10.Image9Click(Sender: TObject);
begin
  img9work;
end;
procedure TTSW10.Image10Click(Sender: TObject);
begin
  img10work;
end;
procedure TTSW10.Image11Click(Sender: TObject);
begin
  img11work;
end;
procedure TTSW10.Image12Click(Sender: TObject);
begin
  img12work;
end;
procedure TTSW10.Image13Click(Sender: TObject);
begin
  img13work;
end;
procedure TTSW10.Image15Click(Sender: TObject);
begin
  img15work;
end;
procedure TTSW10.Image16Click(Sender: TObject);
begin
  img16work;
end;
procedure TTSW10.Image17Click(Sender: TObject);
begin
  img17work;
end;

procedure TTSW10.itemichiwork2; { $0046171C }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  if DrawFlag2 < 0 then
    DrawFlag2 := DrawFlag2 + 15;
  if DrawFlag2 >= 15 then
    DrawFlag2 := DrawFlag2 - 15;
  if HeroWords[DrawFlag2 + 17] = 0 then
  begin
    Inc(DrawFlag2);
    itemichiwork2;
  end;
end;

procedure TTSW10.itemichiwork(Direction: Longint); { $004610C4 }
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  HeroWords: THeroWords absolute Hero;
begin
  if DrawFlag2 < 0 then
    DrawFlag2 := DrawFlag2 + 15;
  if DrawFlag2 >= 15 then
    DrawFlag2 := DrawFlag2 - 15;
  { Try the remaining four rows/columns, then scan forward if all are empty. }
  if HeroWords[DrawFlag2 + 17] = 0 then
  begin
    case Direction of
      0: DrawFlag2 := DrawFlag2 - 3;
      1: DrawFlag2 := DrawFlag2 + 3;
      2: Inc(DrawFlag2);
      3: Dec(DrawFlag2);
    end;
    if DrawFlag2 < 0 then
      DrawFlag2 := DrawFlag2 + 15;
    if DrawFlag2 >= 15 then
      DrawFlag2 := DrawFlag2 - 15;
    if HeroWords[DrawFlag2 + 17] = 0 then
    begin
      case Direction of
        0: DrawFlag2 := DrawFlag2 - 3;
        1: DrawFlag2 := DrawFlag2 + 3;
        2: Inc(DrawFlag2);
        3: Dec(DrawFlag2);
      end;
      if DrawFlag2 < 0 then
        DrawFlag2 := DrawFlag2 + 15;
      if DrawFlag2 >= 15 then
        DrawFlag2 := DrawFlag2 - 15;
      if HeroWords[DrawFlag2 + 17] = 0 then
      begin
        case Direction of
          0: DrawFlag2 := DrawFlag2 - 3;
          1: DrawFlag2 := DrawFlag2 + 3;
          2: Inc(DrawFlag2);
          3: Dec(DrawFlag2);
        end;
        if DrawFlag2 < 0 then
          DrawFlag2 := DrawFlag2 + 15;
        if DrawFlag2 >= 15 then
          DrawFlag2 := DrawFlag2 - 15;
        if HeroWords[DrawFlag2 + 17] = 0 then
        begin
          case Direction of
            0: DrawFlag2 := DrawFlag2 - 3;
            1: DrawFlag2 := DrawFlag2 + 3;
            2: Inc(DrawFlag2);
            3: Dec(DrawFlag2);
          end;
          if DrawFlag2 < 0 then
            DrawFlag2 := DrawFlag2 + 15;
          if DrawFlag2 >= 15 then
            DrawFlag2 := DrawFlag2 - 15;
        end;
      end;
    end;
  end;
  if Hero.hero_orb
          + Hero.wisdom_orb
          + Hero.flight_orb
          + Hero.cross
          + Hero.elixir
          + Hero.mattock
          + Hero.bomb
          + Hero.warp_staff
          + Hero.ascent_wing
          + Hero.descent_wing
          + Hero.dragon_slayer
          + Hero.snow_crystal
          + Hero.magic_key
          + Hero.super_mattock
          + Hero.lucky_gold
      <> 0 then
  begin
    itemichiwork2;
    case DrawFlag2 of
      0:
      begin
        Image22.Top := Image6.Top;
        Image22.Left := Image6.Left;
      end;
      1:
      begin
        Image22.Top := Image5.Top;
        Image22.Left := Image5.Left;
      end;
      2:
      begin
        Image22.Top := Image4.Top;
        Image22.Left := Image4.Left;
      end;
      3:
      begin
        Image22.Top := Image7.Top;
        Image22.Left := Image7.Left;
      end;
      4:
      begin
        Image22.Top := Image8.Top;
        Image22.Left := Image8.Left;
      end;
      5:
      begin
        Image22.Top := Image9.Top;
        Image22.Left := Image9.Left;
      end;
      6:
      begin
        Image22.Top := Image10.Top;
        Image22.Left := Image10.Left;
      end;
      7:
      begin
        Image22.Top := Image11.Top;
        Image22.Left := Image11.Left;
      end;
      8:
      begin
        Image22.Top := Image12.Top;
        Image22.Left := Image12.Left;
      end;
      9:
      begin
        Image22.Top := Image13.Top;
        Image22.Left := Image13.Left;
      end;
      10:
      begin
        Image22.Top := Image14.Top;
        Image22.Left := Image14.Left;
      end;
      11:
      begin
        Image22.Top := Image15.Top;
        Image22.Left := Image15.Left;
      end;
      12:
      begin
        Image22.Top := Image16.Top;
        Image22.Left := Image16.Left;
      end;
      13:
      begin
        Image22.Top := Image17.Top;
        Image22.Left := Image17.Left;
      end;
      14:
      begin
        Image22.Top := Image18.Top;
        Image22.Left := Image18.Left;
      end;
    end;
    WorkBitmap3.Height := Image6.Height;
    WorkBitmap3.Width := Image6.Width;
    WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
    WorkBitmap2.Height := WorkBitmap3.Height;
    WorkBitmap2.Width := WorkBitmap3.Width;
    WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
    WorkBitmap1.Height := WorkBitmap3.Height;
    WorkBitmap1.Width := WorkBitmap3.Width;
    WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
    { Compose the selected item over the original highlight frame and mask. }
    ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 162);
    ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DrawFlag2 + 35);
    ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DrawFlag2 + 35);
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    SourceRect := TargetRect;
    kasanegaki;
    WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap1.Canvas, TargetRect);
    ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 164);
    ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, 158);
    kasanegaki;
    Image22.Picture.Bitmap := WorkBitmap1;
    Image22.Visible := True;
    k1.Enabled := False;
  end;
end;

procedure GameplayMove(Form: TTSW10; Direction: Longint);
var
  X, Y: Longint;
begin
  if (InputEnabled = 0) or (EventCursor > 0) or (EventPaused <> 0) or (Hero.hp <= 0) then
    Exit;
  X := Hero.x;
  Y := Hero.y;
  FacingRequest := Direction;
  case Direction of
    Ord(moveUp):
    begin
      Dec(Y);
      Hero.facing := Ord(hfUp);
    end;
    Ord(moveLeft):
    begin
      Dec(X);
      Hero.facing := Ord(hfLeft);
    end;
    Ord(moveRight):
    begin
      Inc(X);
      Hero.facing := Ord(hfRight);
    end;
    Ord(moveDown):
    begin
      Inc(Y);
      Hero.facing := Ord(hfDown);
    end;
  end;
  if (X < 0) or (X > 10) or (Y < 0) or (Y > 10) then
    Exit;
  HeroCell := Hero.y * BoardWidth + Hero.x;
  PreviousCell := HeroCell;
  ContactIndex := Y * BoardWidth + X;
  Form.handan;
end;

procedure TTSW10.BitBtn1Click(Sender: TObject);
begin
  if EventCursor <= 0 then
  begin
    EventCursor := 0;
    FacingRequest := Ord(moveUp);
    Hero.facing := Ord(hfUp);
    FlightCell := Hero.y * BoardWidth + Hero.x;
    ContactIndex := FlightCell - 11;
    if Hero.y <> 0 then
      handan;
  end;
end;
procedure TTSW10.BitBtn2Click(Sender: TObject);
begin
  if EventCursor <= 0 then
  begin
    EventCursor := 0;
    FacingRequest := Ord(moveLeft);
    Hero.facing := Ord(hfLeft);
    FlightCell := Hero.y * BoardWidth + Hero.x;
    ContactIndex := FlightCell - 1;
    if Hero.x <> 0 then
      handan;
  end;
end;
procedure TTSW10.BitBtn3Click(Sender: TObject);
begin
  if EventCursor <= 0 then
  begin
    EventCursor := 0;
    FacingRequest := Ord(moveRight);
    Hero.facing := Ord(hfRight);
    FlightCell := Hero.y * BoardWidth + Hero.x;
    ContactIndex := FlightCell + 1;
    if Hero.x <> 10 then
      handan;
  end;
end;
procedure TTSW10.BitBtn4Click(Sender: TObject);
begin
  if EventCursor <= 0 then
  begin
    EventCursor := 0;
    FacingRequest := Ord(moveDown);
    Hero.facing := Ord(hfDown);
    FlightCell := Hero.y * BoardWidth + Hero.x;
    ContactIndex := FlightCell + 11;
    if Hero.y <> 10 then
      handan;
  end;
end;

procedure TTSW10.formkeydown(Sender: TObject; var Key: Word; Shift: TShiftState);
type
  THeroWords = array[0..HeroWordCount - 1] of Longint;
var
  I: Longint;
  HeroWords: THeroWords absolute Hero;
begin
  if EventCursor < 0 then
    EventCursor := 0;
  if (Option1.Enabled = True) and (EventCursor = 0) then
    case Key of
      VK_UP:
      begin
        if Image22.Visible = False then
        begin
          FacingRequest := Ord(moveUp);
          FlightCell := Hero.y * BoardWidth + Hero.x;
          Hero.facing := Ord(hfUp);
          ContactIndex := FlightCell - 11;
          if Hero.y <> 0 then
            handan;
        end
        else
          case DrawFlag1 of
            0:
              case DrawFlag2 of
                4..9:
                  if Button37.Visible = True then
                    Button37.SetFocus;
                11..13:
                  if Button37.Visible = True then
                    Button37.SetFocus;
              end;
            1:
            begin
              NeighborIndex := 0;
              for I := 1 to 15 do
                NeighborIndex := NeighborIndex + HeroWords[16 + I];
              if NeighborIndex <> 0 then
              begin
                DrawFlag2 := DrawFlag2 - 3;
                itemichiwork(0);
              end;
            end;
          end;
      end;
      VK_LEFT:
      begin
        if Image22.Visible = False then
        begin
          FacingRequest := Ord(moveLeft);
          FlightCell := Hero.y * BoardWidth + Hero.x;
          Hero.facing := Ord(hfLeft);
          ContactIndex := FlightCell - 1;
          if Hero.x <> 0 then
            handan;
        end
        else
          case DrawFlag1 of
            1:
            begin
              NeighborIndex := 0;
              for I := 1 to 15 do
                NeighborIndex := NeighborIndex + HeroWords[16 + I];
              if NeighborIndex <> 0 then
              begin
                Dec(DrawFlag2);
                itemichiwork(3);
              end;
            end;
          end;
      end;
      VK_RIGHT:
      begin
        if Image22.Visible = False then
        begin
          FacingRequest := Ord(moveRight);
          FlightCell := Hero.y * BoardWidth + Hero.x;
          Hero.facing := Ord(hfRight);
          ContactIndex := FlightCell + 1;
          if Hero.x <> 10 then
            handan;
        end
        else
          case DrawFlag1 of
            1:
            begin
              NeighborIndex := 0;
              for I := 1 to 15 do
                NeighborIndex := NeighborIndex + HeroWords[16 + I];
              if NeighborIndex <> 0 then
              begin
                Inc(DrawFlag2);
                itemichiwork(2);
              end;
            end;
          end;
      end;
      VK_DOWN:
      begin
        if Image22.Visible = False then
        begin
          FacingRequest := Ord(moveDown);
          FlightCell := Hero.y * BoardWidth + Hero.x;
          Hero.facing := Ord(hfDown);
          ContactIndex := FlightCell + 11;
          if Hero.y <> 10 then
            handan;
        end
        else
          case DrawFlag1 of
            1:
            begin
              NeighborIndex := 0;
              for I := 1 to 15 do
                NeighborIndex := NeighborIndex + HeroWords[16 + I];
              if NeighborIndex <> 0 then
              begin
                DrawFlag2 := DrawFlag2 + 3;
                itemichiwork(1);
              end;
            end;
          end;
      end;
      VK_RETURN:
      begin
        if Image22.Visible = False then
          itemichiwork(4)
        else
        begin
          case DrawFlag2 of
            0: img6work;
            1: img5work;
            2: img4work;
            4: img8work;
            5: img9work;
            6: img10work;
            7: img11work;
            8: img12work;
            9: img13work;
            11: img15work;
            12: img16work;
            13: img17work;
          end;
          Image22.Visible := False;
          k1.Enabled := True;
        end;
        DrawFlag1 := 1 - DrawFlag1;
      end;
      VK_ESCAPE:
        if DrawFlag1 = 1 then
        begin
          Image22.Visible := False;
          k1.Enabled := True;
          DrawFlag1 := 0;
        end;
    end;
  if (Image34.Visible = True) and (Key = VK_RETURN) then
    append;
end;

procedure TTSW10.monidou; { $00480384; cardinal tile slide }
var
  I: Longint;
begin
  DrawX := Smallint(EventStack[EventCursor].A) * Image6.Width mod (Image6.Width * BoardWidth);
  DrawY :=
      (Smallint(EventStack[EventCursor].A) * Image6.Height div (Image6.Height * BoardWidth))
          * Image6.Height;

  { Alternate the monster frames while updating the two map-animation buffers. }
  for I := 1 to Image6.Width do
  begin
    StrikeCount := I;
    NeighborIndex := StrikeCount;
    if NeighborIndex mod (Image6.Width div 4) = 0 then
      ScratchIndex := Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] - 1
    else
      ScratchIndex := Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] - 1 + 1;
    TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
    case Smallint(EventStack[EventCursor].B) - Smallint(EventStack[EventCursor].A) of
      11:
      begin
        Damage := 1;
        if NeighborIndex mod (Image6.Width div 4) = 0 then
          DoorOpened := 0
        else
          DoorOpened := 1;
        monidouwork;
        DrawX := Smallint(EventStack[EventCursor].A) * Image6.Width mod (Image6.Width * BoardWidth);
        DrawY :=
            (Smallint(EventStack[EventCursor].A) * Image6.Height div (Image6.Height * BoardWidth))
                * Image6.Height;
      end;
      -1:
      begin
        Damage := 2;
        if NeighborIndex mod (Image6.Width div 4) = 0 then
          DoorOpened := 0
        else
          DoorOpened := 1;
        monidouwork;
        DrawX := Smallint(EventStack[EventCursor].B) * Image6.Width mod (Image6.Width * BoardWidth);
        DrawY :=
            (Smallint(EventStack[EventCursor].B) * Image6.Height div (Image6.Height * BoardWidth))
                * Image6.Height;
      end;
      1:
      begin
        Damage := 3;
        if NeighborIndex mod (Image6.Width div 4) = 0 then
          DoorOpened := 0
        else
          DoorOpened := 1;
        monidouwork;
        DrawX := Smallint(EventStack[EventCursor].A) * Image6.Width mod (Image6.Width * BoardWidth);
        DrawY :=
            (Smallint(EventStack[EventCursor].A) * Image6.Height div (Image6.Height * BoardWidth))
                * Image6.Height;
      end;
      -11:
      begin
        Damage := 4;
        if NeighborIndex mod (Image6.Width div 4) = 0 then
          DoorOpened := 0
        else
          DoorOpened := 1;
        monidouwork;
        DrawX := Smallint(EventStack[EventCursor].B) * Image6.Width mod (Image6.Width * BoardWidth);
        DrawY :=
            (Smallint(EventStack[EventCursor].B) * Image6.Height div (Image6.Height * BoardWidth))
                * Image6.Height;
      end;
    end;

    if NeighborIndex mod (Image6.Width div 4) = 0 then
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1)
    else
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
    MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
  end;
  NeighborIndex := Image6.Width;
  ScratchIndex := Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] - 1 + 1;
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  case Smallint(EventStack[EventCursor].B) - Smallint(EventStack[EventCursor].A) of
    11:
    begin
      Damage := 1;
      DoorOpened := 1;
      monidouwork;
      DrawX := Smallint(EventStack[EventCursor].A) * Image6.Width mod (Image6.Width * BoardWidth);
      DrawY :=
          (Smallint(EventStack[EventCursor].A) * Image6.Height div (Image6.Height * BoardWidth))
              * Image6.Height;
    end;
    -1:
    begin
      Damage := 2;
      DoorOpened := 1;
      monidouwork;
      DrawX := Smallint(EventStack[EventCursor].B) * Image6.Width mod (Image6.Width * BoardWidth);
      DrawY :=
          (Smallint(EventStack[EventCursor].B) * Image6.Height div (Image6.Height * BoardWidth))
              * Image6.Height;
    end;
    1:
    begin
      Damage := 3;
      DoorOpened := 1;
      monidouwork;
      DrawX := Smallint(EventStack[EventCursor].A) * Image6.Width mod (Image6.Width * BoardWidth);
      DrawY :=
          (Smallint(EventStack[EventCursor].A) * Image6.Height div (Image6.Height * BoardWidth))
              * Image6.Height;
    end;
    -11:
    begin
      Damage := 4;
      DoorOpened := 1;
      monidouwork;
      DrawX := Smallint(EventStack[EventCursor].B) * Image6.Width mod (Image6.Width * BoardWidth);
      DrawY :=
          (Smallint(EventStack[EventCursor].B) * Image6.Height div (Image6.Height * BoardWidth))
              * Image6.Height;
    end;
  end;

  MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
  Maps[Hero.floor, Smallint(EventStack[EventCursor].B) + MapTileOffset] :=
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset];
  Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
end;

procedure TTSW10.monidouwork; { $00480A90 }
begin
  case Damage of
    1:
    begin
      WorkBitmap1.Height := Image6.Height * 2;
      WorkBitmap1.Width := Image6.Width;
    end;
    2:
    begin
      WorkBitmap1.Height := Image6.Height;
      WorkBitmap1.Width := Image6.Width * 2;
    end;
    3:
    begin
      WorkBitmap1.Height := Image6.Height;
      WorkBitmap1.Width := Image6.Width * 2;
    end;
    4:
    begin
      WorkBitmap1.Height := Image6.Height * 2;
      WorkBitmap1.Width := Image6.Width;
    end;
  end;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap3.Height := WorkBitmap2.Height;
  WorkBitmap3.Width := WorkBitmap2.Width;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, ScratchIndex);
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, ScratchIndex);
  { Compose the moving sprite over two road cells, using the caller's pixel step. }
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  case Damage of
    1: ImageList1.Draw(WorkBitmap1.Canvas, 0, Image6.Height, 5);
    2: ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width, 0, 5);
    3: ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width, 0, 5);
    4: ImageList1.Draw(WorkBitmap1.Canvas, 0, Image6.Height, 5);
  end;
  case Damage of
    1: SourceRect := Rect(0, NeighborIndex, Image6.Width, Image6.Height + NeighborIndex);
    2:
      SourceRect :=
          Rect(Image6.Width - NeighborIndex, 0, Image6.Width * 2 - NeighborIndex, Image6.Height);
    3: SourceRect := Rect(NeighborIndex, 0, Image6.Width + NeighborIndex, Image6.Height);
    4:
      SourceRect :=
          Rect(0, Image6.Height - NeighborIndex, Image6.Width, Image6.Height * 2 - NeighborIndex);
  end;
  kasanegaki;
end;

procedure TTSW10.dooropen; { $004770E0; sixteen-frame door/wall movement }
begin
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  case Smallint(EventStack[EventCursor].B) of
    1..3:
    begin
      { Split colored doors horizontally. }
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 5);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, Smallint(EventStack[EventCursor].B) - 1);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(ScratchIndex, 0, Image6.Width div 2, Image6.Height);
      SourceRect := Rect(0, 0, Image6.Width div 2 - ScratchIndex, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect := Rect(Image6.Width div 2, 0, Image6.Width - ScratchIndex, Image6.Height);
      SourceRect := Rect(Image6.Width div 2 + ScratchIndex, 0, Image6.Width, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    4:
    begin
      { Open a wall into four quadrants. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 5);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 3);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(ScratchIndex, ScratchIndex, Image6.Width div 2, Image6.Height div 2);
      SourceRect :=
          Rect(0, 0, Image6.Width div 2 - ScratchIndex, Image6.Height div 2 - ScratchIndex);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(Image6.Width div 2, ScratchIndex, Image6.Width - ScratchIndex, Image6.Height div 2);
      SourceRect :=
          Rect(
              Image6.Width div 2 + ScratchIndex,
              0,
              Image6.Width,
              Image6.Height div 2 - ScratchIndex
          );
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(ScratchIndex, Image6.Height div 2, Image6.Width div 2, Image6.Height - ScratchIndex);
      SourceRect :=
          Rect(
              0,
              Image6.Height div 2 + ScratchIndex,
              Image6.Width div 2 - ScratchIndex,
              Image6.Height
          );
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(
              Image6.Width div 2,
              Image6.Height div 2,
              Image6.Width - ScratchIndex,
              Image6.Height - ScratchIndex
          );
      SourceRect :=
          Rect(
              Image6.Width div 2 + ScratchIndex,
              Image6.Height div 2 + ScratchIndex,
              Image6.Width,
              Image6.Height
          );
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    5:
    begin
      { Close a wall from four quadrants. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 5);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 3);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect :=
          Rect(
              Image6.Width div 2 - ScratchIndex,
              Image6.Height div 2 - ScratchIndex,
              Image6.Width div 2,
              Image6.Height div 2
          );
      SourceRect := Rect(0, 0, ScratchIndex, ScratchIndex);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(
              Image6.Width div 2,
              Image6.Height div 2 - ScratchIndex,
              Image6.Width div 2 + ScratchIndex,
              Image6.Height div 2
          );
      SourceRect := Rect(Image6.Width - ScratchIndex, 0, Image6.Width, ScratchIndex);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(
              Image6.Width div 2 - ScratchIndex,
              Image6.Height div 2,
              Image6.Width div 2,
              Image6.Height div 2 + ScratchIndex
          );
      SourceRect := Rect(0, Image6.Height - ScratchIndex, ScratchIndex, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      TargetRect :=
          Rect(
              Image6.Width div 2,
              Image6.Height div 2,
              Image6.Width div 2 + ScratchIndex,
              Image6.Height div 2 + ScratchIndex
          );
      SourceRect :=
          Rect(
              Image6.Width - ScratchIndex,
              Image6.Height - ScratchIndex,
              Image6.Width,
              Image6.Height
          );
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 4;
    end;
    6:
    begin
      { Lift the masked fence. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, 4);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 4);
      ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
      TargetRect := Rect(0, ScratchIndex * 2, Image6.Width, Image6.Height);
      SourceRect := Rect(0, 0, Image6.Width, Image6.Height - ScratchIndex * 2);
      kasanegaki;
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap1);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    7:
    begin
      { Lower the gate out of view. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 5);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 7);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, 0, Image6.Width, Image6.Height - ScratchIndex * 2);
      SourceRect := Rect(0, ScratchIndex * 2, Image6.Width, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    8:
    begin
      { Raise the gate into view. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 5);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 7);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, 0, Image6.Width, ScratchIndex * 2);
      SourceRect := Rect(0, (Image6.Width div 2 - ScratchIndex) * 2, Image6.Width, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 8;
    end;
    9:
    begin
      { Reveal road from the right. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 12);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 5);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, 0, ScratchIndex * 2, Image6.Height);
      SourceRect := Rect((Image6.Width div 2 - ScratchIndex) * 2, 0, Image6.Width, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    10:
    begin
      { Reveal road from the left. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 12);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 5);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, 0, ScratchIndex * 2, Image6.Height);
      SourceRect := Rect(0, 0, ScratchIndex * 2, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    11:
    begin
      { Reveal road from the top. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 12);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 5);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, 0, Image6.Width, ScratchIndex * 2);
      SourceRect := Rect(0, 0, Image6.Width, ScratchIndex * 2);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
    12:
    begin
      { Reveal road from the bottom. }
      WorkBitmap2.Height := Image6.Height;
      WorkBitmap2.Width := Image6.Width;
      WorkBitmap3.Height := WorkBitmap2.Height;
      WorkBitmap3.Width := WorkBitmap2.Width;
      if High1.Checked = True then
        Timer2.Interval := 8;
      if Middle1.Checked = True then
        Timer2.Interval := 10;
      if Low1.Checked = True then
        Timer2.Interval := 12;
      ScratchIndex := Smallint(EventStack[EventCursor - 1].B);
      if ScratchIndex = 16 then
        timerin;
      if GameOptions[optionDisplaySize] = display800x500 then
        ScratchIndex := ScratchIndex * 5 div 4;
      ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, 12);
      ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, 5);
      DrawX := (Smallint(EventStack[EventCursor].A) mod BoardWidth) * Image6.Width;
      DrawY := (Smallint(EventStack[EventCursor].A) div BoardWidth) * Image6.Height;
      TargetRect := Rect(0, (Image6.Height div 2 - ScratchIndex) * 2, Image6.Width, Image6.Height);
      SourceRect := Rect(0, (Image6.Height div 2 - ScratchIndex) * 2, Image6.Width, Image6.Height);
      WorkBitmap3.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
      MapBitmap1.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MapBitmap2.Canvas.Draw(DrawX, DrawY, WorkBitmap3);
      MainForm.Canvas.Draw(UiSpan, UiStep, MapBitmap1);
      Maps[Hero.floor, Smallint(EventStack[EventCursor].A) + MapTileOffset] := 6;
    end;
  end;
end;

procedure TTSW10.banpaiawork; { $0047C978; transformation raster tile }
begin
  { Assemble the eight bats around the central vampire in a three-by-three patch. }
  WorkBitmap1.Height := Image6.Height * 3;
  WorkBitmap1.Width := Image6.Width * 3;
  WorkBitmap2.Height := Image6.Height;
  WorkBitmap2.Width := Image6.Width;
  WorkBitmap3.Height := WorkBitmap2.Height;
  WorkBitmap3.Width := WorkBitmap2.Width;
  WorkBitmap1.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap2.Canvas.CopyMode := cmSrcCopy;
  WorkBitmap3.Canvas.CopyMode := cmSrcCopy;
  ImageList1.Draw(WorkBitmap1.Canvas, 0, 0, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width, 0, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width * 2, 0, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, 0, Image6.Height, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width, Image6.Height, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width * 2, Image6.Height, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, 0, Image6.Height * 2, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width, Image6.Height * 2, 5);
  ImageList1.Draw(WorkBitmap1.Canvas, Image6.Width * 2, Image6.Height * 2, 5);
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(ScratchIndex, ScratchIndex, Image6.Width + ScratchIndex, Image6.Height + ScratchIndex);
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(
          ScratchIndex,
          Image6.Height * 2 - ScratchIndex,
          Image6.Width + ScratchIndex,
          Image6.Height * 3 - ScratchIndex
      );
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(
          Image6.Width * 2 - ScratchIndex,
          ScratchIndex,
          Image6.Width * 2 - ScratchIndex + Image6.Width,
          Image6.Height + ScratchIndex
      );
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(
          Image6.Width * 2 - ScratchIndex,
          Image6.Height * 2 - ScratchIndex,
          Image6.Width * 2 - ScratchIndex + Image6.Width,
          Image6.Height * 3 - ScratchIndex
      );
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := Rect(Image6.Width, ScratchIndex, Image6.Width * 2, Image6.Height + ScratchIndex);
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(
          Image6.Width,
          Image6.Height * 2 - ScratchIndex,
          Image6.Width * 2,
          Image6.Height * 3 - ScratchIndex
      );
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := Rect(ScratchIndex, Image6.Height, Image6.Width + ScratchIndex, Image6.Height * 2);
  kasanegaki;
  ImageList3.Draw(WorkBitmap3.Canvas, 0, 0, DoorOpened + 82);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 82);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect :=
      Rect(
          Image6.Width * 2 - ScratchIndex,
          Image6.Height,
          Image6.Width * 2 - ScratchIndex + Image6.Width,
          Image6.Height * 2
      );
  kasanegaki;
  case GameOptions[optionDisplaySize] of
    display640x400: NeighborIndex := ScratchIndex div 2 + 231 - 66;
    display800x500: NeighborIndex := ScratchIndex * 4 div 5 div 2 + 231 - 66;
  end;
  ImageList1.Draw(WorkBitmap3.Canvas, 0, 0, NeighborIndex);
  ImageList1.Draw(WorkBitmap2.Canvas, 0, 0, DoorOpened + 94);
  TargetRect := Rect(0, 0, Image6.Width, Image6.Height);
  SourceRect := Rect(Image6.Width, Image6.Height, Image6.Width * 2, Image6.Height * 2);
  kasanegaki;
end;
