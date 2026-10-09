/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410f64.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410f64(int *param_1,undefined4 param_2)

{
  HWND pHVar1;
  undefined in_CL;
  
  if (param_1[2] == 0) {
    pHVar1 = FUN_0041fe08((char)param_1,(char)param_2,in_CL,0x410d48,param_1);
    param_1[4] = (int)pHVar1;
  }
  FUN_004099a4(param_1,param_2);
  return;
}

