unit OriginalContent;

interface
procedure LoadOriginalContent;

implementation
uses Windows, Classes, SysUtils, OriginalState;

procedure LoadOriginalContent;
var
  Stream: TResourceStream;
begin
  Stream := TResourceStream.Create(HInstance, 'ORIGINAL_MONSTERS', RT_RCDATA);
  try
    if Stream.Size <> SizeOf(Monsters) then
      raise Exception.Create('Invalid original monster table size');
    Stream.ReadBuffer(Monsters, SizeOf(Monsters));
  finally
    Stream.Free;
  end;
  Stream := TResourceStream.Create(HInstance, 'ORIGINAL_RENDER_ORDER', RT_RCDATA);
  try
    if Stream.Size <> SizeOf(RenderOrder) then
      raise Exception.Create('Invalid original rendering order size');
    Stream.ReadBuffer(RenderOrder, SizeOf(RenderOrder));
  finally
    Stream.Free;
  end;
end;

end.
