/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040edcc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040edcc(uint *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined uVar5;
  uint **ppuVar6;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  uint *local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = (uint *)0x0;
  puStack_20 = &LAB_0040ee5b;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  local_8 = 0;
  iVar2 = local_8;
  if (param_1 != (uint *)0x0) {
    for (iVar4 = 1; iVar3 = FUN_00403650(param_2), iVar2 = local_8, iVar4 <= iVar3;
        iVar4 = iVar4 + 1) {
      uVar5 = *(char *)param_1 == *(char *)(param_2 + -1 + iVar4);
      if ((bool)uVar5) {
        ppuVar6 = &local_c;
        uVar1 = FUN_00403650((int)param_1);
        FUN_00403854(param_2,iVar4,uVar1,(int *)ppuVar6);
        FUN_00403760(param_1,local_c);
        iVar2 = iVar4;
        if ((bool)uVar5) break;
      }
      iVar2 = FUN_0040ed20(*(BYTE *)(param_2 + -1 + iVar4));
      if (iVar2 != 0) {
        iVar4 = iVar4 + 1;
      }
    }
  }
  local_8 = iVar2;
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0040ee62;
  puStack_20 = (undefined *)0x40ee5a;
  FUN_004034dc((int *)&local_c);
  return;
}

