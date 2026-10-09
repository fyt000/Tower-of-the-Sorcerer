/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040deec.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0040deec(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar1 = FUN_0040d9ac((char)*(undefined4 *)(param_4 + 8),param_2,param_3,
                       *(undefined4 *)(param_4 + 8));
  if ((char)uVar1 != '\0') {
    uVar3 = FUN_0040831c(*(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x1c),
                         *(char ***)(*(int *)(param_4 + 8) + -0xc));
    if ((((uVar3 != 0) &&
         (*(int *)(uVar3 + 4) == *(int *)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x24))) &&
        (*(int *)(param_4 + -4) != 0)) &&
       (*(int *)(*(int *)(param_4 + -4) + 4) ==
        *(int *)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x18))) {
      iVar2 = FUN_00405a34(*(undefined **)(uVar3 + 8),*(undefined **)(*(int *)(param_4 + -4) + 8));
      if (iVar2 == 0) {
        uVar3 = *(uint *)(param_4 + -4);
      }
    }
  }
  return uVar3 == *(uint *)(param_4 + -4);
}

