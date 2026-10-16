var
  RetryAnswer, RetryAnswers: Integer;

procedure AnswerRetry(Window: HWND; Message, TimerID, Time: UINT); stdcall;
var
  I: Integer;
begin
  for I := 0 to Screen.FormCount - 1 do
    if (Screen.Forms[I].ClassName = 'TMessageForm')
        and (Screen.Forms[I].Caption = 'Information') then
    begin
      Screen.Forms[I].ModalResult := RetryAnswer;
      Inc(RetryAnswers);
    end;
end;

procedure DialogueChecks;
var
  Order, BeforeGold: Integer;
  DialogTimer: UINT;
  Rows: TRankingTable;
  Names: TRankingNames;
  Text: string;
begin
  Room(2);
  Hero.attack := 100;
  Hero.defense := 100;
  MainForm.roujin;
  Require(
      (Hero.attack = 103)
          and (Hero.defense = 103)
          and (Hero.Word392 = 1)
          and (EventCursor = 6)
          and MainForm.Timer2.Enabled,
      'old-man-gift-keeps-six-record-delay-and-starts-timer'
  );
  MainForm.Button1Click(nil);
  Drain;
  Room(23);
  MainForm.roujin;
  Require(
      (EventCursor = 4)
          and (EventStack[2].Opcode = Ord(evDialogue))
          and (EventStack[2].A = 61)
          and MainForm.Timer2.Enabled,
      'floor23-old-man-queues-story-dialogue'
  );
  Drain;
  { A dialogue can be either dispatch of the original two-command timer tick. }
  for Order := 1 to 2 do
  begin
    Room(1);
    PushEvent(Ord(evSetHeroWord), 0, 777);
    if Order = 1 then
      PushEvent(Ord(evWait), 0, 0);
    PushEvent(Ord(evDialogue), 21, 0);
    if Order = 2 then
      PushEvent(Ord(evWait), 0, 0);
    MainForm.timer2on;
    MainForm.timer2timer(nil);
    Require(
        (EventCursor = 1)
            and (DialogueStage = 31)
            and (DialogueSpeech = 21)
            and (EventPaused = Order - 1)
            and not MainForm.Timer2.Enabled
            and MainForm.Button1.Visible,
        'dialogue-timer-order-' + IntToStr(Order)
    );
    MainForm.Button1Click(nil);
    Require(
        (EventPaused = Order - 1) and (DialogueStage = 31) and MainForm.Timer2.Enabled,
        'continuation-preserves-stage-and-pause-' + IntToStr(Order)
    );
    Drain;
    Require(
        (Hero.hp = 777) and (Hero.Word444 = 1) and (EventPaused = 0),
        'dialogue-resumes-following-command-' + IntToStr(Order)
    );
  end;
  Room(2);
  BeforeGold := Hero.gold;
  MainForm.syounin;
  Require(
      not MainForm.Button7.Enabled and MainForm.Button2.Visible,
      'floor2-merchant-requires-acceptance'
  );
  MainForm.Button2Click(nil);
  Require(
      MainForm.Button7.Enabled
          and (Hero.gold = BeforeGold + 1000)
          and (Hero.Word168 = 1)
          and (Hero.Word216 = 0),
      'trade-and-clue-flags-are-separate'
  );
  MainForm.Button1Click(nil);
  Drain;
  MainForm.syounin;
  Require(
      (Hero.Word216 = 1) and (Hero.gold = BeforeGold + 1000),
      'completed-merchant-gives-clue-without-second-payment'
  );
  MainForm.Button1Click(nil);
  Room(28);
  MainForm.syounin;
  MainForm.Button2Click(nil);
  Require(
      (Hero.yellow_keys = 0) and (MainForm.RichEdit1.Text = MainForm.ListBox2.Items[262]),
      'key-buyer-refuses-empty-inventory'
  );
  MainForm.Button1Click(nil);
  Hero.yellow_keys := 2;
  BeforeGold := Hero.gold;
  MainForm.syounin;
  MainForm.Button2Click(nil);
  Require((Hero.yellow_keys = 1) and (Hero.gold = BeforeGold + 100), 'key-buyer-exchanges-one-key');
  MainForm.Button1Click(nil);
  Drain;
  Room(12);
  ShopMode := 1;
  MainForm.Button2Click(nil);
  Require(
      (MainForm.Button40.Top = MainForm.Button39.Top + MainForm.Button39.Height)
          and (MainForm.Button42.Top = MainForm.Button41.Top + MainForm.Button41.Height)
          and (MainForm.ActiveControl = MainForm.Button42),
      'altar-vertical-choices-and-cancel-focus'
  );
  MainForm.Button42Click(nil);
  Room(10);
  Hero.hp := 10000;
  DefaultRanking(1, Hero.Word628, Rows, Names);
  WriteRanking(1, Hero.Word628, Rows, Names);
  MainForm.yousei;
  Text :=
      MainForm.ListBox2.Items[244]
          + ' 1 '
          + MainForm.ListBox2.Items[245]
          + MainForm.ListBox2.Items[220]
          + ' '
          + IntToStr(Hero.Word340)
          + ' '
          + MainForm.ListBox2.Items[221]
          + MainForm.ListBox2.Items[227]
          + MainForm.ListBox2.Items[228]
          + MainForm.ListBox2.Items[233]
          + MainForm.ListBox2.Items[234]
          + MainForm.ListBox2.Items[235];
  Require(
      (Hero.Word344 = 1) and (Hero.Word348 = 1) and (MainForm.RichEdit1.Text = Text),
      'fairy-prepares-localized-ranking-and-score-commentary'
  );
  DialogueStage := 26;
  DialogueSpeech := 16;
  MainForm.zyouout;
  Require(MainForm.RichEdit1.Text = Text, 'ranking-dialogue-preserves-fairy-text');
  { Subsequent cycles continue without opening the first-cycle ranking form. }
  Hero.cycle_factor_minus_one := 1;
  MainForm.Button1Click(nil);
  Drain;
  for Order := 0 to 1 do
  begin
    Room(1);
    DialogueStage := 103;
    DialogueSpeech := 93;
    MainForm.GameLoad1.Enabled := False;
    MainForm.Timer2.Enabled := False;
    RetryAnswers := 0;
    if Order = 0 then
      RetryAnswer := mrYes
    else
      RetryAnswer := mrNo;
    DialogTimer := SetTimer(0, 0, 10, @AnswerRetry);
    try
      MainForm.zyouout;
    finally
      KillTimer(0, DialogTimer);
    end;
    Require(RetryAnswers = 1, 'native-retry-dialog-answer-' + IntToStr(Order));
    Require(
        (MainForm.Timer2.Enabled = (Order = 0)) and (MainForm.GameLoad1.Enabled = (Order = 1)),
        'retry-dialog-resume-or-load-' + IntToStr(Order)
    );
  end;
end;
