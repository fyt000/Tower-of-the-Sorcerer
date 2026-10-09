/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b9dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b9dc(HANDLE param_1,int *param_2,undefined4 *param_3,int param_4)

{
  undefined4 local_2c [3];
  short local_1e;
  undefined4 local_18;
  
  FUN_0041b928(param_1,local_2c,param_4);
  if (local_1e == 0x18) {
    *param_2 = 0x28;
  }
  else {
    *param_2 = (1 << ((byte)local_1e & 0x1f)) * 4 + 0x28;
  }
  *param_3 = local_18;
  return;
}

