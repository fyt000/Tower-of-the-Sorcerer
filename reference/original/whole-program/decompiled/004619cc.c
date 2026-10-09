/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004619cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004619cc(int param_1)

{
  if (*(char *)(*(int *)(param_1 + 0x1e4) + 0x38) == '\x01') {
    _DAT_0048c5c6 = 0;
    FUN_0042c454(*(int *)(param_1 + 0x30c),'\0');
    FUN_0047f5a8(param_1);
    original_hero._632_4_ = 2;
  }
  return;
}

