/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b408.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b408(undefined4 *param_1,HBITMAP *param_2,HPALETTE *param_3,uint param_4)

{
  undefined4 uVar1;
  undefined4 extraout_EDX;
  int local_c;
  HPALETTE *local_8;
  
  local_8 = param_3;
  uVar1 = (**(code **)*param_1)(param_1,&local_c,4);
  if (local_c == 0x28) {
    FUN_0041af34(param_1,param_2,local_8,param_4,0x28);
  }
  else if (local_c == 0xc) {
    FUN_0041b204(param_1,param_2,local_8,param_4,0xc);
  }
  else {
    FUN_0041ac38(uVar1,extraout_EDX);
  }
  return;
}

