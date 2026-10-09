/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429658.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00429658(int **param_1,char param_2)

{
  if (param_2 != *(char *)((int)param_1 + 0x109)) {
    *(char *)((int)param_1 + 0x109) = param_2;
    if (param_2 == '\x01') {
      *(ushort *)(param_1 + 0xd) = ~DAT_00429698 & *(ushort *)(param_1 + 0xd);
    }
    else {
      *(ushort *)(param_1 + 0xd) = DAT_00429698 | *(ushort *)(param_1 + 0xd);
    }
    FUN_00415174(param_1);
  }
  return;
}

