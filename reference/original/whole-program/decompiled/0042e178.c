/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e178.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042e178(int param_1,char param_2)

{
  undefined4 auStack_44 [6];
  undefined local_2b;
  
  FUN_0042de6c(param_1,auStack_44);
  if (param_2 == '\x01') {
    local_2b = 2;
  }
  else if (param_2 == '\x02') {
    local_2b = 1;
  }
  else {
    local_2b = 0;
  }
  FUN_0042dec8(param_1,(LPARAM)auStack_44);
  return;
}

