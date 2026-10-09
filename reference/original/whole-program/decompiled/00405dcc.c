/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405dcc.
 * Inferred types, shared tails and runtime effects require assembly review. */

DWORD FUN_00405dcc(LPWORD param_1)

{
  BOOL BVar1;
  DWORD DVar2;
  _FILETIME local_c;
  
  do {
    if ((*(uint *)(param_1 + 0xc) & *(uint *)(param_1 + 8)) == 0) {
      FileTimeToLocalFileTime((FILETIME *)(param_1 + 0x16),&local_c);
      FileTimeToDosDateTime(&local_c,param_1 + 1,param_1);
      *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_1 + 0x1c);
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 0xc);
      FUN_00403638((int *)(param_1 + 6),(undefined4 *)(param_1 + 0x22),0x104);
      return 0;
    }
    BVar1 = FindNextFileA(*(HANDLE *)(param_1 + 10),(LPWIN32_FIND_DATAA)(param_1 + 0xc));
  } while (BVar1 != 0);
  DVar2 = GetLastError();
  return DVar2;
}

