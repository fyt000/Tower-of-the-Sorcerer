/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040448c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040448c(HANDLE *param_1,HANDLE param_2,int param_3)

{
  int iVar1;
  DWORD dwDesiredAccess;
  HANDLE pvVar2;
  DWORD DVar3;
  DWORD dwCreationDisposition;
  
  if (param_1[1] != (HANDLE)0xd7b0) {
    if (3 < (int)param_1[1] - 0xd7b0U) {
      DVar3 = 0x66;
      goto LAB_00404566;
    }
    iVar1 = (*(code *)param_1[9])();
    if (iVar1 != 0) {
      FUN_00402730(iVar1);
    }
  }
  param_1[1] = (HANDLE)0xd7b3;
  param_1[2] = param_2;
  param_1[9] = &LAB_004045ae;
  param_1[7] = &LAB_00404537;
  if (*(char *)(param_1 + 0x12) == '\0') {
    param_1[9] = &LAB_00404537;
    if (param_3 == 3) {
      DVar3 = 0xfffffff5;
    }
    else {
      DVar3 = 0xfffffff6;
    }
    pvVar2 = GetStdHandle(DVar3);
  }
  else {
    dwDesiredAccess = 0xc0000000;
    DVar3 = *(DWORD *)(&DAT_0040456d + ((DAT_0048a037 & 0x70) >> 2));
    dwCreationDisposition = 2;
    if ((param_3 != 3) && (dwCreationDisposition = 3, param_3 != 2)) {
      dwDesiredAccess = 0x40000000;
      param_1[1] = (HANDLE)0xd7b2;
      if (param_3 != 1) {
        dwDesiredAccess = 0x80000000;
        param_1[1] = (HANDLE)0xd7b1;
      }
    }
    pvVar2 = CreateFileA((LPCSTR)(param_1 + 0x12),dwDesiredAccess,DVar3,(LPSECURITY_ATTRIBUTES)0x0,
                         dwCreationDisposition,0x80,(HANDLE)0x0);
  }
  if (pvVar2 != (HANDLE)0xffffffff) {
    *param_1 = pvVar2;
    return;
  }
  param_1[1] = (HANDLE)0xd7b0;
  DVar3 = GetLastError();
LAB_00404566:
  FUN_00402730(DVar3);
  return;
}

