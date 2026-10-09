/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401550.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401550(LPVOID param_1,int param_2,int **param_3)

{
  int *piVar1;
  undefined4 uVar2;
  
  param_3[1] = (int *)0x100000;
  piVar1 = (int *)VirtualAlloc(param_1,0x100000,0x2000,4);
  *param_3 = piVar1;
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)(param_2 + 0xffffU & 0xffff0000);
    param_3[1] = piVar1;
    piVar1 = (int *)VirtualAlloc(param_1,(SIZE_T)piVar1,0x2000,4);
    *param_3 = piVar1;
  }
  if (*param_3 != (int *)0x0) {
    uVar2 = FUN_004013a0((int **)&DAT_0048a440,param_3);
    if ((char)uVar2 == '\0') {
      VirtualFree(*param_3,0,0x8000);
      *param_3 = (int *)0x0;
    }
  }
  return;
}

