unit OriginalGraphics;

{ Separate linker storage for the original bitmap globals. Graphics methods
  operate on Delphi's real canvases and image lists. }
interface
uses Windows, Graphics;

var
  MapBitmap1, MapBitmap2, WorkBitmap1, WorkBitmap2, WorkBitmap3,
    FrameBitmap: TBitmap;
  SourceRect, TargetRect: TRect;

procedure ComposeSprite;
procedure ReleaseGraphics;

implementation

procedure ComposeSprite; { $0044439C }
begin
  WorkBitmap2.Canvas.CopyMode := $EE0086;
  WorkBitmap2.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap3.Canvas.CopyMode := $330008;
  WorkBitmap3.Canvas.CopyRect(TargetRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $EE0086;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap3.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $8800C6;
  WorkBitmap1.Canvas.CopyRect(SourceRect, WorkBitmap2.Canvas, TargetRect);
  WorkBitmap1.Canvas.CopyMode := $CC0020;
  WorkBitmap2.Canvas.CopyMode := $CC0020;
  WorkBitmap3.Canvas.CopyMode := $CC0020;
end;

procedure ReleaseGraphics;
begin
  MapBitmap1.Free; MapBitmap1 := nil;
  MapBitmap2.Free; MapBitmap2 := nil;
  WorkBitmap1.Free; WorkBitmap1 := nil;
  WorkBitmap2.Free; WorkBitmap2 := nil;
  WorkBitmap3.Free; WorkBitmap3 := nil;
  FrameBitmap.Free; FrameBitmap := nil;
end;

end.
