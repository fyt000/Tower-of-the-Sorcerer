/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417780.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417780(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  uVar1 = FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  if (((*(int *)(param_1 + 0x20) < 1) || (0x8000 < *(int *)(param_1 + 0x20))) ||
     (*(int *)(param_1 + 0x24) < 1)) {
    uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf024);
    FUN_004031f8(uVar1);
  }
  *(undefined4 *)(param_1 + 0x28) = 4;
  *(undefined *)(param_1 + 0x31) = 1;
  *(undefined *)(param_1 + 0x30) = 2;
  *(undefined *)(param_1 + 0x33) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x1fffffff;
  *(undefined4 *)(param_1 + 0x38) = 0x1fffffff;
  FUN_0041825c(param_1,-1);
  iVar2 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),extraout_ECX);
  *(int *)(param_1 + 0x48) = iVar2;
  FUN_00417814(param_1);
  return;
}

