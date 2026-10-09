/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432a64.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00432a64(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00402c0c(param_1,0,param_3);
  iVar2 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX_00);
  *(int *)(param_1 + 4) = iVar2;
  *(int *)(iVar2 + 8) = param_1;
  *(code **)(iVar2 + 4) = FUN_00432b90;
  *(undefined4 *)(param_1 + 0x1c) = 0x8080;
  *(undefined *)(param_1 + 0x20) = 1;
  bVar1 = 0;
  do {
    *(undefined4 *)(param_1 + 0xc + (uint)bVar1 * 4) = 0xffffffff;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 4);
  if (DAT_004898d4 == 0) {
    DAT_004898d4 = FUN_00432970(0x4327a0,1,extraout_ECX_01);
  }
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

