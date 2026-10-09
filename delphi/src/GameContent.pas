unit GameContent;

interface
procedure LoadGameContent;

implementation
uses
  Windows,
  Classes,
  SysUtils,
  GameState;

procedure LoadGameContent;
var
  Stream: TResourceStream;
begin
  Stream := TResourceStream.Create(HInstance, 'MONSTER_STATS', RT_RCDATA);
  try
    if Stream.Size <> SizeOf(Monsters) then
      raise Exception.Create('Invalid monster table size');
    Stream.ReadBuffer(Monsters, SizeOf(Monsters));
  finally
    Stream.Free;
  end;
  Stream := TResourceStream.Create(HInstance, 'RENDER_ORDER', RT_RCDATA);
  try
    if Stream.Size <> SizeOf(RenderOrder) then
      raise Exception.Create('Invalid rendering order size');
    Stream.ReadBuffer(RenderOrder, SizeOf(RenderOrder));
  finally
    Stream.Free;
  end;
end;

end.
