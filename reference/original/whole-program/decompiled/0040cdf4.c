/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040cdf4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040cdf4(int param_1,int *param_2,uint param_3)

{
  undefined4 *puVar1;
  uint local_c;
  
  local_c = param_3;
  FUN_0040bc08(param_1,&local_c,1);
  FUN_004035bc(param_2,(undefined4 *)0x0,local_c & 0xff);
  puVar1 = (undefined4 *)FUN_00403820(param_2);
  FUN_0040bc08(param_1,puVar1,local_c & 0xff);
  return;
}

