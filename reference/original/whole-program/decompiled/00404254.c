/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00404254.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00404254(HANDLE *param_1,LPCVOID param_2,uint param_3,uint *param_4)

{
  BOOL BVar1;
  uint uVar2;
  DWORD DVar3;
  uint uStack_10;
  uint uStack_c;
  
  if ((int)param_1[1] - 0xd7b2U < 2) {
    uStack_10 = 0;
    uStack_c = param_3;
    BVar1 = WriteFile(*param_1,param_2,(int)param_1[2] * param_3,&uStack_10,(LPOVERLAPPED)0x0);
    if (BVar1 == 1) {
      uVar2 = uStack_10 / (uint)param_1[2];
      if (param_4 != (uint *)0x0) {
        *param_4 = uVar2;
        return uVar2;
      }
      if (uVar2 == uStack_c) {
        return uVar2;
      }
      DVar3 = 0x65;
    }
    else {
      uStack_c = 0x4042a6;
      DVar3 = GetLastError();
    }
  }
  else {
    DVar3 = 0x67;
  }
  uStack_c = 0x4042ab;
  FUN_00402730(DVar3);
  return 0;
}

