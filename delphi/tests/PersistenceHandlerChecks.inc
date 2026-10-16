type
  TPersistenceDialog = class
    Answer, Seen: Integer;
    Started: DWORD;
    procedure Tick(Sender: TObject);
  end;

procedure TPersistenceDialog.Tick(Sender: TObject);
var
  I, J: Integer;
  Dialog: TForm;
  MessageText: string;
begin
  for I := 0 to Screen.FormCount - 1 do
  begin
    Dialog := Screen.Forms[I];
    for J := 0 to Dialog.ComponentCount - 1 do
      if Dialog.Components[J] is TLabel then
      begin
        MessageText := TLabel(Dialog.Components[J]).Caption;
        if (MessageText = 'Overwrite. Is it true?')
            or (MessageText = 'Save options. Is it true?') then
        begin
          Inc(Seen);
          Dialog.ModalResult := Answer;
          Exit;
        end;
        if (MessageText = 'Done.') or (MessageText = 'Donot use this save data.') then
        begin
          Inc(Seen);
          Dialog.ModalResult := mrOk;
          Exit;
        end;
      end;
  end;
  if GetTickCount - Started > 5000 then
    raise Exception.Create('Persistence dialog timed out');
end;

function SamePersistenceBytes(var Left, Right; Count: Integer): Boolean;
type
  TBytes = array[0..7000] of Byte;
  PBytes = ^TBytes;
var
  I: Integer;
begin
  Result := False;
  for I := 0 to Count - 1 do
    if PBytes(@Left)^[I] <> PBytes(@Right)^[I] then
      Exit;
  Result := True;
end;

procedure PersistenceHandlerChecks;
var
  Slot, I, Speed, Mode: Integer;
  Path: string;
  Stream: TFileStream;
  DiskHero, ExpectedHero: THeroState;
  DiskMaps: TFloorMaps;
  Options: array[0..9] of Byte;
  Dismiss: TPersistenceDialog;
  Timer: TTimer;
  Timer1Event, Timer4Event: TNotifyEvent;
begin
  Room(1);
  MainForm.BGMON1.Checked := False;
  Timer1Event := MainForm.Timer1.OnTimer;
  Timer4Event := MainForm.Timer4.OnTimer;
  MainForm.Timer1.OnTimer := nil;
  MainForm.Timer4.OnTimer := nil;
  Dismiss := TPersistenceDialog.Create;
  Timer := TTimer.Create(nil);
  try
    Timer.Interval := 10;
    Timer.OnTimer := Dismiss.Tick;
    Timer.Enabled := False;
    for Slot := 1 to 8 do
    begin
      Path := Fixtures + '\save' + IntToStr(Slot) + '.dat';
      if FileExists(Path) then
        DeleteFile(Path);
      Hero.hp := 2000 + Slot;
      Hero.gold := MaxLongint - Slot;
      ExpectedHero := Hero;
      SaveChecksums(ExpectedHero);
      case Slot of
        1: MainForm.Save11Click(nil);
        2: MainForm.Save21Click(nil);
        3: MainForm.Save31Click(nil);
        4: MainForm.Save41Click(nil);
        5: MainForm.Save51Click(nil);
        6: MainForm.Save61Click(nil);
        7: MainForm.Save71Click(nil);
        8: MainForm.Save81Click(nil);
      end;
      ReadSaveRecords(Path, False, DiskMaps, DiskHero);
      Require(
          (DiskHero.hp = 2000 + Slot)
              and (DiskHero.Word656 = ExpectedHero.Word656)
              and (DiskHero.Word660 = ExpectedHero.Word660),
          'save-handler-record-' + IntToStr(Slot)
      );
      Require(TileClass = 134, 'save-handler-status-' + IntToStr(Slot));
      for I := 1 to 8 do
        Require(
            TMenuItem(MainForm.FindComponent('Save' + IntToStr(I) + '1')).Checked = (I = Slot),
            'save-handler-menu-' + IntToStr(Slot) + '-' + IntToStr(I)
        );
      Hero.hp := 3000 + Slot;
      Hero.Word656 := 12345;
      Hero.Word660 := -23456;
      Maps[1, 62] := 7;
      MainForm.Timer4.Enabled := True;
      MainForm.Timer1.Enabled := False;
      case Slot of
        1: MainForm.Load11Click(nil);
        2: MainForm.Load21Click(nil);
        3: MainForm.Load31Click(nil);
        4: MainForm.Load41Click(nil);
        5: MainForm.Load51Click(nil);
        6: MainForm.Load61Click(nil);
        7: MainForm.Load71Click(nil);
        8: MainForm.Load81Click(nil);
      end;
      Require(
          (Hero.hp = 2000 + Slot) and (TileClass = 133),
          'load-handler-state-' + IntToStr(Slot)
      );
      Require(
          not MainForm.Timer4.Enabled and MainForm.Timer1.Enabled,
          'load-handler-timers-' + IntToStr(Slot)
      );
      ReadSaveRecords(Fixtures + '\save0.dat', True, DiskMaps, DiskHero);
      Require(
          (DiskHero.hp = 3000 + Slot)
              and (DiskHero.Word656 = 12345)
              and (DiskHero.Word660 = -23456)
              and (DiskMaps[1, 62] = 7),
          'load-handler-raw-checkpoint-' + IntToStr(Slot)
      );
      for I := 1 to 8 do
        Require(
            TMenuItem(MainForm.FindComponent('Load' + IntToStr(I) + '1')).Checked = (I = Slot),
            'load-handler-menu-' + IntToStr(Slot) + '-' + IntToStr(I)
        );
    end;
    Dismiss.Answer := mrNo;
    Dismiss.Seen := 0;
    Dismiss.Started := GetTickCount;
    Timer.Enabled := True;
    Hero.hp := 9999;
    MainForm.Save81Click(nil);
    Timer.Enabled := False;
    ReadSaveRecords(Fixtures + '\save8.dat', False, DiskMaps, DiskHero);
    Require((Dismiss.Seen = 1) and (DiskHero.hp = 2008), 'save-handler-overwrite-no');
    Dismiss.Answer := mrYes;
    Dismiss.Seen := 0;
    Dismiss.Started := GetTickCount;
    Timer.Enabled := True;
    MainForm.Save81Click(nil);
    Timer.Enabled := False;
    ReadSaveRecords(Fixtures + '\save8.dat', False, DiskMaps, DiskHero);
    Require((Dismiss.Seen = 1) and (DiskHero.hp = 9999), 'save-handler-overwrite-yes');
    for Speed := 1 to 3 do
    begin
      MainForm.Memo1.Font.Size := 9;
      MainForm.Edit8.Font.Size := 12;
      MainForm.High1.Checked := Speed = 1;
      MainForm.Low1.Checked := Speed = 3;
      GameOptions[9] := 173;
      Dismiss.Seen := 0;
      Dismiss.Started := GetTickCount;
      Timer.Enabled := True;
      MainForm.OptionSave1Click(nil);
      Timer.Enabled := False;
      Stream := TFileStream.Create(Fixtures + '\option.dat', fmOpenRead);
      try
        Require(Stream.Size = 10, 'option-handler-size-' + IntToStr(Speed));
        Stream.ReadBuffer(Options, 10);
      finally
        Stream.Free;
      end;
      Require(
          (Dismiss.Seen = 2)
              and (Options[0] = 9)
              and (Options[1] = 12)
              and (Options[2] = 0)
              and (Options[3] = Speed)
              and (Options[9] = 173),
          'option-handler-bytes-' + IntToStr(Speed)
      );
    end;
    Dismiss.Answer := mrNo;
    Dismiss.Seen := 0;
    Dismiss.Started := GetTickCount;
    MainForm.High1.Checked := True;
    MainForm.Low1.Checked := False;
    Timer.Enabled := True;
    MainForm.OptionSave1Click(nil);
    Timer.Enabled := False;
    Stream := TFileStream.Create(Fixtures + '\option.dat', fmOpenRead);
    try
      Stream.ReadBuffer(Options, 10);
    finally
      Stream.Free;
    end;
    Require((Dismiss.Seen = 1) and (Options[3] = 3), 'option-handler-cancel');
    SavedHero := Hero;
    SavedMaps := Maps;
    { Match the original live reads and raw save0 rollback, including failures. }
    for Mode := 1 to 7 do
    begin
      Hero := SavedHero;
      Maps := SavedMaps;
      Stream := TFileStream.Create(Fixtures + '\save0.dat', fmCreate);
      try
        if Mode <> 3 then
        begin
          Stream.WriteBuffer(SavedMaps, SizeOf(SavedMaps));
          Stream.WriteBuffer(SavedHero, SizeOf(SavedHero));
        end;
      finally
        Stream.Free;
      end;
      if Mode = 4 then
        DeleteFile(Fixtures + '\save0.dat');
      DiskHero := SavedHero;
      DiskMaps := SavedMaps;
      DiskHero.hp := 111;
      DiskMaps[1, 62] := 99;
      DiskMaps[0, 2] := 77;
      if Mode = 2 then
        DiskHero.Word628 := 0;
      SaveChecksums(DiskHero);
      if Mode in [1, 3, 4] then
        Inc(DiskHero.Word656);
      Path := Fixtures + '\invalid.dat';
      Stream := TFileStream.Create(Path, fmCreate);
      try
        if Mode = 5 then
          Stream.WriteBuffer(DiskMaps, 20)
        else
        begin
          Stream.WriteBuffer(DiskMaps, SizeOf(DiskMaps));
          Stream.WriteBuffer(DiskHero, SizeOf(DiskHero));
          if Mode = 6 then
            Stream.WriteBuffer(Mode, 1);
        end;
      finally
        Stream.Free;
      end;
      if Mode = 7 then
        DeleteFile(Path);
      IOPath := Path;
      Dismiss.Seen := 0;
      Dismiss.Started := GetTickCount;
      Timer.Enabled := True;
      MainForm.loadwork;
      Timer.Enabled := False;
      { Original I/O failure paths can leave the file open; release the test fixture. }
      if Mode in [3, 4, 5, 7] then
      begin
        {$I-}
        CloseFile(SettingsFile);
        I := IOResult;
        {$I+}
      end;
      if Mode = 6 then
      begin
        Require(
            (Hero.hp = 111) and (Maps[1, 62] = 99) and (TileClass = 133) and (Dismiss.Seen = 0),
            'load-handler-ignores-trailing-bytes'
        );
        Hero := SavedHero;
        Maps := SavedMaps;
        Continue;
      end;
      if Mode <= 2 then
      begin
        Require(
            SamePersistenceBytes(Hero, SavedHero, SizeOf(Hero))
                and SamePersistenceBytes(Maps, SavedMaps, SizeOf(Maps)),
            'load-handler-restores-raw-checkpoint-' + IntToStr(Mode)
        );
        Require(
            (Dismiss.Seen = 1) and (IOPath = Fixtures + '\save0.dat'),
            'load-handler-invalid-warning-' + IntToStr(Mode)
        )
      end
      else
      begin
        if Mode in [3, 4] then
          Require(
              SamePersistenceBytes(Hero, DiskHero, SizeOf(Hero))
                  and SamePersistenceBytes(Maps, DiskMaps, SizeOf(Maps)),
              'load-handler-failed-rollback-keeps-loaded-state-' + IntToStr(Mode)
          );
        if Mode = 5 then
        begin
          Move(DiskMaps, SavedMaps, 20);
          Require(
              SamePersistenceBytes(Hero, SavedHero, SizeOf(Hero))
                  and SamePersistenceBytes(Maps, SavedMaps, SizeOf(Maps)),
              'load-handler-short-read-partially-updates-map'
          );
        end;
        if Mode = 7 then
          Require(
              SamePersistenceBytes(Hero, SavedHero, SizeOf(Hero))
                  and SamePersistenceBytes(Maps, SavedMaps, SizeOf(Maps)),
              'load-handler-missing-input-keeps-state'
          );
        Require(
            (Dismiss.Seen = 0) and (TileClass = 115),
            'load-handler-io-error-' + IntToStr(Mode)
        );
      end;
    end;
  finally
    Timer.Free;
    Dismiss.Free;
    MainForm.Timer1.Enabled := False;
    MainForm.Timer4.Enabled := False;
    MainForm.Timer1.OnTimer := Timer1Event;
    MainForm.Timer4.OnTimer := Timer4Event;
    MainForm.Middle1Click(nil);
  end;
end;
