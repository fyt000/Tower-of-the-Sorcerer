/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004014ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004014ec(int param_1,int **param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_1 < 0x100000) {
    piVar2 = (int *)0x100000;
  }
  else {
    piVar2 = (int *)(param_1 + 0xffffU & 0xffff0000);
  }
  param_2[1] = piVar2;
  piVar2 = (int *)VirtualAlloc((LPVOID)0x0,(SIZE_T)piVar2,0x2000,1);
  *param_2 = piVar2;
  if (piVar2 != (int *)0x0) {
    uVar1 = FUN_004013a0((int **)&DAT_0048a440,param_2);
    if ((char)uVar1 == '\0') {
      VirtualFree(*param_2,0,0x8000);
      *param_2 = (int *)0x0;
    }
  }
  return;
}

