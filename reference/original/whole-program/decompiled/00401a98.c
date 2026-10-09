/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401a98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401a98(void)

{
  undefined4 *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  
  if (DAT_0048a419 == '\0') {
    return;
  }
  uStack_14 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_14;
  if (DAT_0048a036 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  DAT_0048a419 = 0;
  LocalFree(DAT_0048a478);
  DAT_0048a478 = (HLOCAL)0x0;
  for (puVar1 = DAT_0048a440; (undefined4 **)puVar1 != &DAT_0048a440; puVar1 = (undefined4 *)*puVar1
      ) {
    VirtualFree((LPVOID)puVar1[2],0,0x8000);
  }
  FUN_00401398(0x48a440);
  FUN_00401398(0x48a450);
  FUN_00401398(0x48a47c);
  puVar1 = DAT_0048a438;
  while (puVar1 != (undefined4 *)0x0) {
    DAT_0048a438 = (undefined4 *)*puVar1;
    LocalFree(puVar1);
    puVar1 = DAT_0048a438;
  }
  DAT_0048a438 = puVar1;
  *in_FS_OFFSET = uStack_14;
  if (DAT_0048a036 != '\0') {
    uStack_14 = 0x401b65;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  uStack_14 = 0x401b6f;
  DeleteCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  return;
}

