/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423f2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423f2c(void)

{
  if (DAT_0048a724 != (HHOOK)0x0) {
    UnhookWindowsHookEx(DAT_0048a724);
  }
  DAT_0048a724 = (HHOOK)0x0;
  if (DAT_0048a728 != (HANDLE)0x0) {
    TerminateThread(DAT_0048a728,0);
  }
  DAT_0048a728 = (HANDLE)0x0;
  return;
}

