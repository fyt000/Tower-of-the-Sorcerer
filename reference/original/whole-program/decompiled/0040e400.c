/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e400.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e400(int param_1,undefined *param_2,uint param_3)

{
  undefined4 *puVar1;
  uint local_c;
  
  local_c = param_3;
  local_c = FUN_00403650((int)param_2);
  if (0xff < (int)local_c) {
    local_c = 0xff;
  }
  FUN_0040d260(param_1,&local_c,1);
  puVar1 = (undefined4 *)FUN_00403814(param_2);
  FUN_0040d260(param_1,puVar1,local_c);
  return;
}

