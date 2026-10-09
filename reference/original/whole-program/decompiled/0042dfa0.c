/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042dfa0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042dfa0(int param_1,byte *param_2)

{
  uint uVar1;
  undefined4 extraout_ECX;
  byte *pbVar2;
  byte *pbVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_7c;
  undefined *puStack_78;
  undefined *puStack_74;
  undefined *local_64;
  undefined4 local_60;
  uint local_5c;
  undefined local_48;
  undefined4 local_46 [8];
  byte local_24;
  byte abStack_23 [31];
  
  puStack_74 = &stack0xfffffffc;
  local_64 = (undefined *)0x0;
  local_24 = *param_2;
  if (0x1e < local_24) {
    local_24 = 0x1f;
  }
  pbVar2 = param_2 + 1;
  pbVar3 = abStack_23;
  for (uVar1 = (uint)local_24; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pbVar3 = *pbVar2;
    pbVar2 = pbVar2 + 1;
    pbVar3 = pbVar3 + 1;
  }
  puStack_78 = &LAB_0042e03b;
  uStack_7c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_7c;
  FUN_0042de6c(param_1,&local_60);
  local_5c = 0x20000000;
  FUN_004035fc((int *)&local_64,&local_24);
  FUN_004061bc(local_46,local_64,0x20);
  uVar1 = FUN_0042d360(*(int **)(param_1 + 4),(LPCSTR)local_46,extraout_ECX);
  local_48 = (undefined)uVar1;
  local_5c = local_5c | 0x8000000;
  FUN_0042dec8(param_1,(LPARAM)&local_60);
  *in_FS_OFFSET = uStack_7c;
  puStack_74 = &LAB_0042e042;
  puStack_78 = (undefined *)0x42e03a;
  FUN_004034dc((int *)&local_64);
  return;
}

