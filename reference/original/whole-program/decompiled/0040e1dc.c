/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e1dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040e1dc(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  byte local_10c [256];
  int local_c [2];
  
  uVar1 = FUN_0040d9ac((char)*(undefined4 *)(param_4 + 8),param_2,param_3,
                       *(undefined4 *)(param_4 + 8));
  iVar2 = 0;
  if ((char)uVar1 != '\0') {
    FUN_00408688(*(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x1c),
                 *(int *)(*(int *)(param_4 + 8) + -0xc),local_c);
    iVar2 = local_c[0];
  }
  if (iVar2 == *(int *)(param_4 + -8)) {
LAB_0040e257:
    uVar1 = CONCAT31((int3)((uint)param_4 >> 8),1);
  }
  else {
    if (*(int *)(param_4 + -8) != 0) {
      param_4 = FUN_00402d80(**(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x18),
                             *(int *)(param_4 + -8),local_10c);
      if (local_10c[0] == 0) goto LAB_0040e257;
    }
    uVar1 = 0;
  }
  return uVar1;
}

