/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004254d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004254d0(int param_1)

{
  if (*(char *)(param_1 + 0x65) != '\0') {
    KillTimer((HWND)0x0,(uint)*(ushort *)(param_1 + 0x68));
    *(undefined *)(param_1 + 0x65) = 0;
  }
  return;
}

