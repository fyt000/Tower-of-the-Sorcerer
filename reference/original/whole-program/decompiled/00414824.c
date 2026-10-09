/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414824.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414824(char param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  undefined4 extraout_ECX;
  int iVar6;
  int local_c;
  
  FUN_004099cc(*(undefined4 **)(param_4 + -8));
  if ((*(int *)(param_4 + -0xc) != 0) &&
     (((*(char *)(*(int *)(param_4 + -0xc) + 0x37) != '\0' ||
       (((*(byte *)(*(int *)(param_4 + -0xc) + 0x1c) & 0x10) != 0 &&
        ((*(byte *)(*(int *)(param_4 + -0xc) + 0x35) & 4) == 0)))) &&
      (*(char *)(*(int *)(param_4 + -0xc) + 0x3b) == param_1)))) {
    FUN_004099a4(*(int **)(param_4 + -8),*(undefined4 *)(param_4 + -0xc));
  }
  iVar1 = FUN_00414ccc(*(int *)(param_4 + -0x10));
  if (-1 < iVar1 + -1) {
    local_c = 0;
    do {
      iVar2 = FUN_00414c9c(*(int *)(param_4 + -0x10),local_c);
      if (((*(char *)(iVar2 + 0x3b) == param_1) &&
          ((*(char *)(iVar2 + 0x37) != '\0' ||
           (((*(byte *)(iVar2 + 0x1c) & 0x10) != 0 && ((*(byte *)(iVar2 + 0x35) & 4) == 0)))))) &&
         (iVar2 != *(int *)(param_4 + -0xc))) {
        for (iVar6 = 0; iVar6 < *(int *)(*(int *)(param_4 + -8) + 8); iVar6 = iVar6 + 1) {
          iVar3 = FUN_00409a40(*(undefined4 **)(param_4 + -8),iVar6);
          uVar4 = FUN_00414628(iVar2,iVar3,param_1);
          if ((char)uVar4 != '\0') break;
        }
        FUN_00409aa8(*(int **)(param_4 + -8),iVar6,iVar2);
      }
      local_c = local_c + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  iVar1 = *(int *)(*(int *)(param_4 + -8) + 8);
  if (-1 < iVar1 + -1) {
    local_c = 0;
    do {
      iVar2 = param_4;
      piVar5 = (int *)FUN_00409a40(*(undefined4 **)(param_4 + -8),local_c);
      FUN_00414690(piVar5,param_1,extraout_ECX,iVar2);
      local_c = local_c + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

