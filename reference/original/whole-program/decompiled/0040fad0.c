/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fad0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040fad0(undefined *param_1)

{
  char cVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *local_c;
  undefined *local_8;
  
  local_c = (undefined *)0x0;
  puStack_1c = (undefined *)0x40fae9;
  local_8 = param_1;
  FUN_00403804((int)param_1);
  puStack_20 = &LAB_0040fbab;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_1c = &stack0xfffffffc;
  do {
    do {
      cVar1 = FUN_0040fa50((int *)&local_8,DAT_0048a680);
    } while (cVar1 != '\0');
    cVar1 = FUN_0040fa50((int *)&local_8,&LAB_0040fbc4);
  } while (((cVar1 != '\0') || (cVar1 = FUN_0040fa50((int *)&local_8,DAT_0048a684), cVar1 != '\0'))
          || (cVar1 = FUN_0040fa50((int *)&local_8,DAT_0048a688), cVar1 != '\0'));
  if (local_8 != (undefined *)0x0) {
    uVar3 = 8;
    do {
      FUN_0040f848(uVar3,(int *)&local_c);
      iVar2 = FUN_00405a34(local_8,local_c);
      if (iVar2 == 0) break;
      uVar3 = uVar3 + 1;
    } while (uVar3 != 0x256);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0040fbb2;
  puStack_20 = (undefined *)0x40fbaa;
  FUN_004034fc((int *)&local_c,2);
  return;
}

