/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004041f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_004041f0(HANDLE *param_1,LPVOID param_2,uint param_3,uint *param_4)

{
  BOOL BVar1;
  uint uVar2;
  DWORD DVar3;
  uint uStack_10;
  uint uStack_c;
  
  if ((int)param_1[1] - 0xd7b1U < 3) {
    uStack_10 = 0;
    uStack_c = param_3;
    BVar1 = ReadFile(*param_1,param_2,(int)param_1[2] * param_3,&uStack_10,(LPOVERLAPPED)0x0);
    if (BVar1 == 1) {
      uVar2 = uStack_10 / (uint)param_1[2];
      if (param_4 != (uint *)0x0) {
        *param_4 = uVar2;
        return uVar2;
      }
      if (uVar2 == uStack_c) {
        return uVar2;
      }
      DVar3 = 100;
    }
    else {
      uStack_c = 0x404243;
      DVar3 = GetLastError();
    }
  }
  else {
    DVar3 = 0x67;
  }
  uStack_c = 0x404248;
  FUN_00402730(DVar3);
  return 0;
}

