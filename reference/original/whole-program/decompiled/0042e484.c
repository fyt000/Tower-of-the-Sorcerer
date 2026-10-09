/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e484.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e484(int param_1,byte param_2)

{
  int iVar1;
  undefined4 uStack_a4;
  undefined4 local_a0;
  ushort local_9c;
  
  if (param_2 == 0) {
    FUN_0042e564(param_1,0);
  }
  else if (param_2 == 1) {
    iVar1 = FUN_0042e544(param_1);
    if (iVar1 < 10) {
      FUN_0042e564(param_1,10);
    }
  }
  FUN_0042e398(param_1,&uStack_a4);
  local_a0 = 0x20;
  local_9c = (ushort)param_2;
  FUN_0042e3e8(param_1,(LPARAM)&uStack_a4);
  return;
}

