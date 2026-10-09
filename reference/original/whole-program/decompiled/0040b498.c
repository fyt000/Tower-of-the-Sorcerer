/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b498.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b498(int param_1,HMODULE param_2,LPCSTR param_3,LPCSTR param_4)

{
  HRSRC pHVar1;
  HGLOBAL pvVar2;
  DWORD DVar3;
  LPVOID pvVar4;
  undefined extraout_CL;
  undefined extraout_CL_00;
  undefined extraout_DL;
  undefined extraout_DL_00;
  
  pHVar1 = FindResourceA(param_2,param_3,param_4);
  *(HRSRC *)(param_1 + 0x10) = pHVar1;
  if (pHVar1 == (HRSRC)0x0) {
    FUN_0040b424(0,extraout_DL,extraout_CL,&stack0xfffffffc);
  }
  pvVar2 = LoadResource(param_2,*(HRSRC *)(param_1 + 0x10));
  *(HGLOBAL *)(param_1 + 0x14) = pvVar2;
  if (pvVar2 == (HGLOBAL)0x0) {
    FUN_0040b424(0,extraout_DL_00,extraout_CL_00,&stack0xfffffffc);
  }
  DVar3 = SizeofResource(param_2,*(HRSRC *)(param_1 + 0x10));
  pvVar4 = LockResource(*(HGLOBAL *)(param_1 + 0x14));
  FUN_0040b120(param_1,pvVar4,DVar3);
  return;
}

