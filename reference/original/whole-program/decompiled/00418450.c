/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418450.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00418450(int param_1)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(param_1 + 0x3c) + 8);
  if (-1 < iVar3 + -1) {
    iVar2 = 0;
    do {
      piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0x3c),iVar2);
      FUN_00402cdc(piVar1,extraout_EDX,extraout_ECX);
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  if (*(short *)(param_1 + 0x4e) != 0) {
    (**(code **)(param_1 + 0x4c))(*(undefined4 *)(param_1 + 0x50),param_1);
  }
  return;
}

