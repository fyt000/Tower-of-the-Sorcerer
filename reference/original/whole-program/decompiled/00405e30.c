/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405e30.
 * Inferred types, shared tails and runtime effects require assembly review. */

DWORD FUN_00405e30(undefined *param_1,uint param_2,LPWORD param_3)

{
  LPCSTR lpFileName;
  HANDLE pvVar1;
  DWORD DVar2;
  LPWIN32_FIND_DATAA lpFindFileData;
  
  *(uint *)(param_3 + 8) = ~param_2 & 0x1e;
  lpFindFileData = (LPWIN32_FIND_DATAA)(param_3 + 0xc);
  lpFileName = FUN_00403814(param_1);
  pvVar1 = FindFirstFileA(lpFileName,lpFindFileData);
  *(HANDLE *)(param_3 + 10) = pvVar1;
  if (pvVar1 == (HANDLE)0xffffffff) {
    DVar2 = GetLastError();
  }
  else {
    DVar2 = FUN_00405dcc(param_3);
    if (DVar2 != 0) {
      FUN_00405ea0((int)param_3);
    }
  }
  return DVar2;
}

