/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bb04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bb04(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  
  puStack_18 = &stack0xfffffffc;
  iVar3 = *(int *)(param_1 + 0x2c);
  if (iVar3 != 0) {
    puStack_1c = &LAB_0040bb75;
    uStack_20 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_20;
    iVar3 = *(int *)(iVar3 + 8);
    if (-1 < iVar3 + -1) {
      iVar4 = 0;
      do {
        iVar1 = FUN_00409a40(*(undefined4 **)(param_1 + 0x2c),iVar4);
        pcVar2 = (char *)FUN_0040e968(*(int *)(param_1 + 0x18),*(undefined **)(iVar1 + 0x14));
        FUN_0040838c(*(int **)(iVar1 + 4),*(char ***)(iVar1 + 0xc),pcVar2);
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    *in_FS_OFFSET = uStack_20;
    puStack_18 = (undefined *)0x40bb7c;
    puStack_1c = (undefined *)0x40bb74;
    FUN_0040bbb0(param_1);
    return;
  }
  return;
}

