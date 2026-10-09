/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e448.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e448(int param_1,undefined4 *param_2,uint param_3)

{
  undefined4 extraout_ECX;
  uint local_c;
  
  local_c = param_3;
  local_c = FUN_00403650((int)param_2);
  if ((int)local_c < 0x100) {
    FUN_0040e4a4(param_1,6,extraout_ECX);
    FUN_0040d260(param_1,&local_c,1);
  }
  else {
    FUN_0040e4a4(param_1,0xc,extraout_ECX);
    FUN_0040d260(param_1,&local_c,4);
  }
  FUN_0040d260(param_1,param_2,local_c);
  return;
}

