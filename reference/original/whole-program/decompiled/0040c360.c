/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c360.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040c360(int param_1,undefined4 param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 extraout_EDX;
  int local_c;
  char local_8;
  short local_6;
  
  uVar2 = FUN_0040ce90(param_1,param_2,param_3);
  cVar1 = (char)uVar2;
  if (cVar1 == '\x02') {
    FUN_0040bc08(param_1,(undefined4 *)&local_8,1);
    local_c = (int)local_8;
  }
  else if (cVar1 == '\x03') {
    FUN_0040bc08(param_1,(undefined4 *)&local_6,2);
    local_c = (int)local_6;
  }
  else if ((char)(cVar1 + -4) == '\0') {
    FUN_0040bc08(param_1,&local_c,4);
  }
  else {
    FUN_0040b8e0(CONCAT31((int3)(uVar2 >> 8),cVar1 + -4),extraout_EDX);
  }
  return local_c;
}

