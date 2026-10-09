/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041275c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041275c(POINT *param_1,HWND *param_2)

{
  HWND pHVar1;
  undefined4 extraout_EDX;
  
  pHVar1 = FUN_00412730(param_1);
  *param_2 = pHVar1;
  FUN_004126c4(*param_2,CONCAT31((int3)((uint)extraout_EDX >> 8),5),DAT_0048a6a0,&param_1->x,0);
  return;
}

