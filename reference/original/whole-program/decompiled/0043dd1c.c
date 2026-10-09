/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043dd1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

LONG FUN_0043dd1c(int param_1)

{
  HDC hdc;
  HGDIOBJ pvVar1;
  tagTEXTMETRICA local_40;
  
  hdc = GetDC((HWND)0x0);
  pvVar1 = (HGDIOBJ)FUN_00419c90(param_1);
  pvVar1 = SelectObject(hdc,pvVar1);
  GetTextMetricsA(hdc,&local_40);
  SelectObject(hdc,pvVar1);
  ReleaseDC((HWND)0x0,hdc);
  return local_40.tmHeight;
}

