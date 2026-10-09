/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e6d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043e6d4(int *param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 local_10;
  undefined local_c;
  byte local_b;
  undefined *local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_24 = &LAB_0043e78e;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  bVar1 = FUN_004028b0(param_2);
  uVar3 = FUN_0043f1b4((int)param_1);
  bVar2 = FUN_004028b0((byte)uVar3);
  if (bVar1 != bVar2) {
    if (param_2 != 0) {
      local_c = 1;
      local_b = param_2;
      FUN_004028fc(&local_10,(undefined4 *)&local_c);
      FUN_004028cc((byte *)&local_10,&LAB_0043e79c,2);
      FUN_004035fc((int *)&local_8,(byte *)&local_10);
      FUN_0040274c(local_8);
      FUN_00402710();
      FUN_00402768('\0',param_1 + 0x56);
    }
    if (*(char *)(param_1 + 0x52) == '\0') {
      (**(code **)(*param_1 + 0x98))();
      (**(code **)(*param_1 + 0x90))();
    }
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0043e795;
  puStack_24 = (undefined *)0x43e78d;
  FUN_004034dc((int *)&local_8);
  return;
}

