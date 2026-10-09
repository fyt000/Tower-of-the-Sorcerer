/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e7ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041e7ac(void)

{
  HDC hdc;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  
  hdc = GetDC((HWND)0x0);
  DAT_0048a6d4 = GetDeviceCaps(hdc,0x5a);
  ReleaseDC((HWND)0x0,hdc);
  _DAT_004894a0 = MulDiv(9,DAT_0048a6d4,0x48);
  _DAT_004894a0 = -_DAT_004894a0;
  DAT_0048a6d8 = GetStockObject(7);
  DAT_0048a6dc = GetStockObject(5);
  DAT_0048a6e0 = GetStockObject(0xd);
  DAT_0048a6e4 = LoadIconA((HINSTANCE)0x0,&DAT_00007f00);
  DAT_0048a6e8 = FUN_004195e4(0x419548,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                              CONCAT22(extraout_var,0x2c));
  DAT_0048a6ec = FUN_004195e4(0x419548,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                              CONCAT22(extraout_var_00,0x10));
  DAT_0048a6f0 = FUN_004195e4(0x419548,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                              CONCAT22(extraout_var_01,0x10));
  DAT_00489570 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),extraout_ECX);
  DAT_0048a6f4 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                              extraout_ECX_00);
  FUN_004095a0(&DAT_004189ac,FUN_00419b40,FUN_00419b10);
  return;
}

