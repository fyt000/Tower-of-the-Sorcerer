/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c2ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c2ac(int param_1,int *param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 extraout_EDX;
  uint local_c;
  
  local_c = param_3;
  uVar2 = FUN_0040ce90(param_1,param_2,param_3);
  cVar1 = (char)uVar2;
  if (cVar1 == '\a') {
    FUN_0040bc08(param_1,&local_c,1);
    FUN_004035bc(param_2,(undefined4 *)0x0,local_c & 0xff);
    puVar3 = (undefined4 *)FUN_00403820(param_2);
    FUN_0040bc08(param_1,puVar3,local_c & 0xff);
  }
  else if (cVar1 == '\b') {
    FUN_00403570(param_2,0x40c33c);
  }
  else if (cVar1 == '\t') {
    FUN_00403570(param_2,0x40c34c);
  }
  else if ((char)(cVar1 + -0xd) == '\0') {
    FUN_00403570(param_2,0x40c35c);
  }
  else {
    FUN_0040b8e0(CONCAT31((int3)(uVar2 >> 8),cVar1 + -0xd),extraout_EDX);
  }
  return;
}

