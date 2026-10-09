program EventQueueSmoke;
{$APPTYPE CONSOLE}
uses
  Windows,
  SysUtils,
  Classes,
  Controls,
  Forms,
  GameForms,
  GameState,
  GameContent,
  GameGraphics;
{$R ..\GameResources.res}

var
  Input, Output: TFileStream;
  I, Builder, Width: Longint;
begin
  try
    if ParamCount <> 4 then
      raise Exception.Create('Builder, input, output, width required');
    Builder := StrToInt(ParamStr(1));
    Width := StrToInt(ParamStr(4));
    Application.Initialize;
    LoadGameContent;
    MainForm := TTSW10.Create(Application);
    MainForm.OnActivate := nil;
    MainForm.OnClose := nil;
    MainForm.Image6.Width := Width;
    MainForm.Image6.Height := Width;
    MainForm.Timer1.Enabled := False;
    MainForm.Timer2.Enabled := False;
    MainForm.Timer3.Enabled := False;
    MainForm.Timer4.Enabled := False;
    MainForm.MouseControl1.Checked := False;
    MainForm.KeyboardControl1.Checked := True;
    Input := TFileStream.Create(ParamStr(2), fmOpenRead);
    try
      Input.ReadBuffer(Hero, SizeOf(Hero));
      Input.ReadBuffer(Maps, SizeOf(Maps));
      Input.ReadBuffer(Monsters, SizeOf(Monsters));
      Input.ReadBuffer(ScratchIndex, SizeOf(ScratchIndex));
      Input.ReadBuffer(NeighborIndex, SizeOf(NeighborIndex));
      Input.ReadBuffer(NeighborY, SizeOf(NeighborY));
      Input.ReadBuffer(DamageMode, SizeOf(DamageMode));
    finally
      Input.Free;
    end;
    EventCursor := 0;
    EventPaused := False;
    case Builder of
      1: MainForm.ichicheck;
      2: MainForm.moncheck;
      3: MainForm.zenolivework;
      4: MainForm.madoushilivework;
      5: MainForm.madoushi2;
      6: MainForm.openning2;
      7: QueueEnding(MainForm);
    else
      raise Exception.Create('Unknown scene builder');
    end;
    MainForm.Timer2.Enabled := False;
    Output := TFileStream.Create(ParamStr(3), fmCreate);
    try
      Output.WriteBuffer(EventCursor, SizeOf(EventCursor));
      for I := EventCursor downto 1 do
        Output.WriteBuffer(EventStack[I], SizeOf(EventStack[I]));
      Output.WriteBuffer(Hero, SizeOf(Hero));
      Output.WriteBuffer(Maps, SizeOf(Maps));
      Output.WriteBuffer(Monsters, SizeOf(Monsters));
    finally
      Output.Free;
    end;
    WriteLn('{"queue_records":', EventCursor, '}');
    MainForm.Free;
    MainForm := nil;
  except
    on E: Exception do
    begin
      WriteLn(E.ClassName, ': ', E.Message);
      Halt(1);
    end;
  end;
end.
