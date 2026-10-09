/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415678.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00415678(HWND param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_004121e4(param_1);
  if (piVar1 != (int *)0x0) {
    iVar2 = FUN_00413cb8(piVar1,*param_2 + 0xbc00,param_2[1],param_2[2]);
    param_2[3] = iVar2;
  }
  return piVar1 != (int *)0x0;
}

