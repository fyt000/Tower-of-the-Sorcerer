/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428a54.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428a54(int *param_1)

{
  HDC hdc;
  HGDIOBJ pvVar1;
  int iVar2;
  int iVar3;
  tagTEXTMETRICA local_7c;
  tagTEXTMETRICA local_44;
  
  hdc = GetDC((HWND)0x0);
  GetTextMetricsA(hdc,&local_7c);
  pvVar1 = (HGDIOBJ)FUN_00419c90(param_1[0x11]);
  pvVar1 = SelectObject(hdc,pvVar1);
  GetTextMetricsA(hdc,&local_44);
  SelectObject(hdc,pvVar1);
  ReleaseDC((HWND)0x0,hdc);
  if (DAT_0048a694 == '\0') {
    iVar2 = local_7c.tmHeight;
    if (local_44.tmHeight < local_7c.tmHeight) {
      iVar2 = local_44.tmHeight;
    }
    iVar3 = GetSystemMetrics(6);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 3;
    }
    iVar2 = iVar3 * 4 + (iVar2 >> 2);
  }
  else {
    if (*(char *)((int)param_1 + 0xc5) == '\0') {
      iVar3 = 6;
    }
    else {
      iVar3 = 8;
    }
    iVar2 = GetSystemMetrics(6);
    iVar2 = iVar2 * iVar3;
  }
  FUN_004130f8(param_1,local_44.tmHeight + iVar2);
  return;
}

