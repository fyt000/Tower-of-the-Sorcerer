/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410a80.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00410a80(int param_1)

{
  char cVar1;
  int *piVar2;
  int extraout_ECX;
  undefined4 extraout_EDX;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)(param_1 + 0x24) != 0) {
    GetKeyState(0x10);
    GetKeyState(0x11);
    do {
      cVar1 = '\0';
      piVar2 = (int *)FUN_00410958(param_1);
      if (piVar2 != (int *)0x0) {
        cVar1 = FUN_004109f4(piVar2,extraout_EDX,extraout_ECX,(int)&stack0xfffffffc);
      }
    } while (cVar1 == '\x02');
    bVar3 = piVar2 != (int *)0x0;
  }
  return bVar3;
}

