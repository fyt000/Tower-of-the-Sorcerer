/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004106d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004106d8(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  iVar1 = FUN_004106a4((int)param_1,param_2);
  if (iVar1 == -1) {
    uVar2 = FUN_004074cc(0x40f184,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf037);
    iVar1 = FUN_004031f8(uVar2);
  }
  FUN_0041061c(param_1,iVar1);
  return;
}

