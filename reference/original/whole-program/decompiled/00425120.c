/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425120.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00425120(int param_1,int param_2)

{
  LPCSTR pCVar1;
  LPCSTR pCVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *local_c;
  undefined *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  local_c = (undefined *)0x0;
  puStack_20 = &LAB_00425196;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  uVar3 = 0x10;
  FUN_00424bec(param_1,(int *)&local_8);
  pCVar1 = FUN_00403814(local_8);
  FUN_00403570((int *)&local_c,*(int *)(param_2 + 4));
  FUN_00403658((int *)&local_c,(undefined4 *)&DAT_004251ac);
  pCVar2 = FUN_00403814(local_c);
  FUN_004250ac(param_1,pCVar2,pCVar1,(ushort)uVar3);
  *in_FS_OFFSET = uVar3;
  puStack_20 = &LAB_0042519d;
  uStack_24 = 0x425195;
  FUN_004034fc((int *)&local_c,2);
  return;
}

