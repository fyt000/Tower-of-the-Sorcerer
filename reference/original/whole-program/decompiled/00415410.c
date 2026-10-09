/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415410.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00415410(int *param_1,undefined4 *param_2)

{
  HWND pHVar1;
  HWND pHVar2;
  int *piVar3;
  undefined4 uVar4;
  int local_1c;
  int local_18;
  int local_14 [2];
  
  pHVar1 = (HWND)FUN_00416cbc(param_1);
  pHVar2 = GetCapture();
  if (pHVar1 == pHVar2) {
    piVar3 = (int *)0x0;
    if ((DAT_00489320 != (int *)0x0) && (param_1 == (int *)DAT_00489320[8])) {
      piVar3 = DAT_00489320;
    }
  }
  else {
    FUN_004052e0(param_2[2],local_14);
    piVar3 = FUN_00415350((int)param_1,local_14,0);
  }
  if (piVar3 != (int *)0x0) {
    local_1c = (int)*(short *)(param_2 + 2) - piVar3[9];
    local_18 = (int)*(short *)((int)param_2 + 10) - piVar3[10];
    uVar4 = FUN_004052f4((undefined2 *)&local_1c);
    FUN_00413cb8(piVar3,*param_2,param_2[1],uVar4);
  }
  return piVar3 != (int *)0x0;
}

