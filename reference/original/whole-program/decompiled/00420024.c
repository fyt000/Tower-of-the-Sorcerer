/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420024.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00420024(int **param_1)

{
  int **ppiVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  int *local_c;
  undefined local_8;
  
  ppiVar1 = FUN_0041fffc(param_1);
  if (ppiVar1 == (int **)0x0) {
    local_c = param_1[2];
    local_8 = 0xb;
    uVar2 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf02f,0,&local_c);
    FUN_004031f8(uVar2);
  }
  return;
}

