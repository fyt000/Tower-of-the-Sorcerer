/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c390.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c390(int *param_1,UINT *param_2,undefined4 param_3)

{
  UINT UVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar2;
  
  if (*param_2 == 0x113) {
    uVar2 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffe0;
    FUN_00402cdc(param_1,param_2,param_3);
    *in_FS_OFFSET = uVar2;
  }
  else {
    UVar1 = DefWindowProcA((HWND)param_1[10],*param_2,param_2[1],param_2[2]);
    param_2[3] = UVar1;
  }
  return;
}

