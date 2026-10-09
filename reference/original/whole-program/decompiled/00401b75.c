/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401b75.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00401b75(void)

{
  if (DAT_0048a036 != '\0') {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  DeleteCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  return;
}

