/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a480.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a480(int **param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  if (((*(short *)(param_2 + 4) == 0xd) && (*(char *)((int)param_1 + 0x106) != '\0')) ||
     ((*(short *)(param_2 + 4) == 0x1b && (*(char *)((int)param_1 + 0x105) != '\0')))) {
    bVar1 = FUN_0041ff20(*(uint *)(param_2 + 8));
    if (DAT_0042a4e4 == bVar1) {
      uVar2 = FUN_00416c2c(param_1);
      if ((char)uVar2 != '\0') {
        FUN_00402cdc((int *)param_1,extraout_EDX,extraout_ECX);
        *(undefined4 *)(param_2 + 0xc) = 1;
        return;
      }
    }
  }
  FUN_004162d4((int)param_1,param_2);
  return;
}

