/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e09c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e09c(int param_1,byte param_2)

{
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  
  FUN_0042de6c(param_1,&local_40);
  local_3c = 0xf;
  if ((param_2 & 1) != 0) {
    local_38 = local_38 | 1;
  }
  if ((param_2 & 2) != 0) {
    local_38 = local_38 | 2;
  }
  if ((param_2 & 4) != 0) {
    local_38 = local_38 | 4;
  }
  if ((param_2 & 8) != 0) {
    local_38 = local_38 | 8;
  }
  FUN_0042dec8(param_1,(LPARAM)&local_40);
  return;
}

