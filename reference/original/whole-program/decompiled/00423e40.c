/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423e40.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00423e40(void)

{
  HANDLE pvVar1;
  DWORD dwMilliseconds;
  tagPOINT tStack_c;
  
  do {
    do {
      dwMilliseconds = 1000;
      pvVar1 = GetCurrentProcess();
      WaitForInputIdle(pvVar1,dwMilliseconds);
    } while (DAT_0048a6f8 == 0);
    if (*(int *)(DAT_0048a6f8 + 0x40) != 0) {
      GetCursorPos(&tStack_c);
      pvVar1 = FUN_00412bb4(&tStack_c);
      if (pvVar1 == (HANDLE)0x0) {
        FUN_00425618(DAT_0048a6f8);
      }
    }
  } while( true );
}

