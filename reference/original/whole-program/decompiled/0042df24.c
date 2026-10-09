/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042df24.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042df24(int param_1,uint param_2)

{
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_30;
  
  FUN_0042de6c(param_1,&uStack_44);
  local_40 = 0x40000000;
  if (param_2 == 0x80000008) {
    local_3c = 0x40000000;
  }
  else {
    local_30 = FUN_00419b00(param_2);
  }
  FUN_0042dec8(param_1,(LPARAM)&uStack_44);
  return;
}

