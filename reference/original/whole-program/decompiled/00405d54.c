/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405d54.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00405d54(undefined *param_1)

{
  LPCSTR lpFileName;
  HANDLE hFindFile;
  BOOL BVar1;
  LPWIN32_FIND_DATAA lpFindFileData;
  byte local_150;
  FILETIME local_13c [37];
  _FILETIME local_10;
  undefined4 local_8;
  
  lpFindFileData = (LPWIN32_FIND_DATAA)&local_150;
  lpFileName = FUN_00403814(param_1);
  hFindFile = FindFirstFileA(lpFileName,lpFindFileData);
  if ((hFindFile != (HANDLE)0xffffffff) && (FindClose(hFindFile), (local_150 & 0x10) == 0)) {
    FileTimeToLocalFileTime(local_13c,&local_10);
    BVar1 = FileTimeToDosDateTime(&local_10,(LPWORD)((int)&local_8 + 2),(LPWORD)&local_8);
    if (BVar1 != 0) {
      return local_8;
    }
  }
  return 0xffffffff;
}

