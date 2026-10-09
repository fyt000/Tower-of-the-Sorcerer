/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e624.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e624(int param_1,byte param_2,int param_3)

{
  undefined4 uStack_a8;
  undefined4 local_a4;
  ushort local_8e;
  int aiStack_8c [32];
  
  FUN_0042e3b4(param_1,&uStack_a8);
  aiStack_8c[param_2] = param_3 * 0x14;
  local_a4 = 0x10;
  if ((short)local_8e < (short)(ushort)param_2) {
    local_8e = (ushort)param_2;
  }
  FUN_0042e3e8(param_1,(LPARAM)&uStack_a8);
  return;
}

