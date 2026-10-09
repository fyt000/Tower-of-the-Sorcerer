/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00404a10.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00404a10(void)

{
  LPVOID pvVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  
  puStack_14 = &stack0xfffffffc;
  puStack_18 = &LAB_00404abc;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  _DAT_0048a3d8 = _tls_index << 2;
  DAT_0048a024 = 0;
  DAT_0048a028 = 0;
  DAT_0048a02c = 0;
  pvVar1 = FUN_00403498();
  *(undefined4 *)((int)pvVar1 + 4) = 0;
  _DAT_0048a030 = 0;
  DAT_0048a037 = 2;
  DAT_0048a038 = 2;
  DAT_0048a039 = 3;
  _DAT_0048a3e0 = 0;
  _DAT_0048a3f0 = 1;
  FUN_00402abc();
  FUN_00403f38();
  FUN_00402b6c();
  FUN_0040414d((undefined4 *)&DAT_0048a03c,"");
  FUN_0040414d((undefined4 *)&DAT_0048a208,"");
  *in_FS_OFFSET = uStack_1c;
  return;
}

