/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004019d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004019d4(void)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_10;
  
  uStack_10 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_10;
  InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  if (DAT_0048a036 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  FUN_00401398(0x48a440);
  FUN_00401398(0x48a450);
  FUN_00401398(0x48a47c);
  DAT_0048a478 = LocalAlloc(0,0xff8);
  if (DAT_0048a478 != (HLOCAL)0x0) {
    iVar1 = 3;
    do {
      *(undefined4 *)((int)DAT_0048a478 + iVar1 * 4 + -0xc) = 0;
      iVar1 = iVar1 + 1;
    } while (iVar1 != 0x401);
    DAT_0048a464 = &DAT_0048a460;
    DAT_0048a460 = &DAT_0048a460;
    DAT_0048a46c = &DAT_0048a460;
    DAT_0048a419 = 1;
  }
  *in_FS_OFFSET = uStack_10;
  if (DAT_0048a036 != '\0') {
    uStack_10 = 0x401a89;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  return;
}

