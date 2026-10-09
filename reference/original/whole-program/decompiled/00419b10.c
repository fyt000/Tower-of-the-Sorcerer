/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419b10.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00419b10(int param_1,int *param_2)

{
  int iVar1;
  undefined4 unaff_EBX;
  int *piVar2;
  
  iVar1 = 0x2a;
  piVar2 = &DAT_0048934c;
  do {
    if (param_1 == *piVar2) {
      FUN_0040352c(param_2,(undefined4 *)piVar2[1]);
      return CONCAT31((int3)((uint)unaff_EBX >> 8),1);
    }
    piVar2 = piVar2 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}

