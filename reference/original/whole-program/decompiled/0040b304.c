/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b304.
 * Inferred types, shared tails and runtime effects require assembly review. */

LPCVOID FUN_0040b304(int param_1,SIZE_T *param_2)

{
  undefined4 uVar1;
  LPCVOID pvVar2;
  LPCVOID extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  if (0 < (int)*param_2) {
    *param_2 = *param_2 + 0x1fff & 0xffffe000;
  }
  pvVar2 = *(LPCVOID *)(param_1 + 4);
  if (*param_2 != *(SIZE_T *)(param_1 + 0x10)) {
    if (*param_2 == 0) {
      FUN_004052cc(pvVar2);
      pvVar2 = (LPCVOID)0x0;
    }
    else {
      if (*(SIZE_T *)(param_1 + 0x10) == 0) {
        pvVar2 = (LPCVOID)FUN_004052a0((uint)DAT_00489000,*param_2);
        uVar1 = extraout_EDX;
      }
      else {
        pvVar2 = (LPCVOID)FUN_004052b0(pvVar2,*param_2,(uint)DAT_00489000);
        uVar1 = extraout_EDX_00;
      }
      if (pvVar2 == (LPCVOID)0x0) {
        uVar1 = FUN_004074cc(0x4087ac,CONCAT31((int3)((uint)uVar1 >> 8),1),0xf005);
        FUN_004031f8(uVar1);
        pvVar2 = extraout_ECX;
      }
    }
  }
  return pvVar2;
}

