/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409370.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409370(undefined4 *param_1,undefined *param_2)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_12c;
  undefined *puStack_128;
  undefined *puStack_124;
  byte local_114 [256];
  undefined *local_14;
  undefined **local_10;
  int local_c;
  undefined *local_8;
  
  puStack_124 = &stack0xfffffffc;
  local_14 = (undefined *)0x0;
  puStack_128 = &LAB_00409426;
  uStack_12c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_12c;
  local_8 = param_2;
  for (local_10 = (undefined **)FUN_00402b78(param_1); local_10 != &PTR_FUN_00408b48;
      local_10 = (undefined **)FUN_00402bb8((int)local_10)) {
    psVar1 = (short *)FUN_00409274((int)local_10);
    if ((psVar1 != (short *)0x0) && (iVar3 = (int)*psVar1, -1 < iVar3 + -1)) {
      local_c = 0;
      do {
        FUN_00402b7c(*(int *)(psVar1 + local_c * 2 + 1),local_114);
        FUN_004035fc((int *)&local_14,local_114);
        iVar2 = FUN_00405a34(local_14,local_8);
        if (iVar2 == 0) goto LAB_00409410;
        local_c = local_c + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  FUN_00409350((int)local_8);
LAB_00409410:
  *in_FS_OFFSET = uStack_12c;
  puStack_124 = &LAB_0040942d;
  puStack_128 = (undefined *)0x409425;
  FUN_004034dc((int *)&local_14);
  return;
}

