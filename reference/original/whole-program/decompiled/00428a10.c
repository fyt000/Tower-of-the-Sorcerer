/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428a10.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428a10(int *param_1)

{
  if ((*(char *)((int)param_1 + 0x107) != '\0') && (*(char *)(param_1 + 0x41) == '\x01')) {
    *(ushort *)(param_1 + 0xd) = DAT_00428a50 | *(ushort *)(param_1 + 0xd);
    FUN_00428a54(param_1);
    return;
  }
  *(ushort *)(param_1 + 0xd) = ~DAT_00428a50 & *(ushort *)(param_1 + 0xd);
  return;
}

