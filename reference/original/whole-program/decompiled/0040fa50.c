/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fa50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040fa50(int *param_1,undefined *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *in_FS_OFFSET;
  undefined **ppuVar3;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_1c = &LAB_0040fac0;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  ppuVar3 = &local_8;
  uVar1 = FUN_00403650((int)param_2);
  FUN_00403854(*param_1,1,uVar1,(int *)ppuVar3);
  iVar2 = FUN_00405a34(local_8,param_2);
  if (iVar2 == 0) {
    iVar2 = FUN_00403650((int)param_2);
    FUN_00403894(param_1,1,iVar2);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040fac7;
  puStack_1c = (undefined *)0x40fabf;
  FUN_004034dc((int *)&local_8);
  return;
}

