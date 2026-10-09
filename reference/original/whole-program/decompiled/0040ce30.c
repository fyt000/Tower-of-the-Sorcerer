/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ce30.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ce30(int param_1,int *param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 extraout_EDX;
  uint local_c;
  
  local_c = 0;
  uVar2 = FUN_0040ce90(param_1,param_2,param_3);
  if ((char)uVar2 == '\x06') {
    FUN_0040bc08(param_1,&local_c,1);
  }
  else {
    cVar1 = (char)uVar2 + -0xc;
    if (cVar1 == '\0') {
      FUN_0040bc08(param_1,&local_c,4);
    }
    else {
      FUN_0040b8e0(CONCAT31((int3)(uVar2 >> 8),cVar1),extraout_EDX);
    }
  }
  FUN_004035bc(param_2,(undefined4 *)0x0,local_c);
  FUN_0040bc08(param_1,(undefined4 *)*param_2,local_c);
  return;
}

