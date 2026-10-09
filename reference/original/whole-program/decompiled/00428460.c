/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428460.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void root_00428460(int *param_1,char param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0042842c((int)param_1);
  if (param_2 != (char)uVar1) {
    if (param_2 == '\0') {
      *(ushort *)(param_1 + 0xd) = _DAT_004284a0 | *(ushort *)(param_1 + 0xd);
    }
    else {
      *(ushort *)(param_1 + 0xd) = ~_DAT_004284a0 & *(ushort *)(param_1 + 0xd);
    }
    (**(code **)(*param_1 + 0x44))();
  }
  return;
}

