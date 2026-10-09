/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ff5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ff5c(undefined4 param_1,char *param_2)

{
  undefined *puVar1;
  char *pcVar2;
  int iVar3;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *local_c;
  undefined *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  local_c = (undefined *)0x0;
  puStack_20 = &LAB_0041ffde;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  pcVar2 = FUN_004038dc("&",param_2);
  if ((pcVar2 != (char *)0x0) && (iVar3 = FUN_00403650((int)param_2), (int)pcVar2 < iVar3)) {
    FUN_004035ec((int *)&local_8,param_1);
    puVar1 = local_8;
    FUN_004035ec((int *)&local_c,CONCAT31((int3)((uint)extraout_EDX >> 8),param_2[(int)pcVar2]));
    FUN_00405a34(local_c,puVar1);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0041ffe5;
  puStack_20 = (undefined *)0x41ffdd;
  FUN_004034fc((int *)&local_c,2);
  return;
}

