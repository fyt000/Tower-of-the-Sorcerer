/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416f10.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416f10(int param_1,int *param_2)

{
  int *piVar1;
  undefined4 extraout_ECX;
  int iVar2;
  int iStack_14;
  
  if ((*(int *)(param_1 + 0xb8) != 0) &&
     (iVar2 = *(int *)(*(int *)(param_1 + 0xb8) + 8), -1 < iVar2 + -1)) {
    iStack_14 = 0;
    do {
      piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0xb8),iStack_14);
      FUN_004099a4(param_2,piVar1);
      FUN_00402cdc(piVar1,param_2,extraout_ECX);
      iStack_14 = iStack_14 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

