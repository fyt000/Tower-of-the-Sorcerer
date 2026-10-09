/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dc28.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0040dc28(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = FUN_0040d9ac((char)*(undefined4 *)(param_4 + 8),param_2,param_3,
                       *(undefined4 *)(param_4 + 8));
  if ((char)uVar1 != '\0') {
    uVar2 = FUN_0040831c(*(int **)(*(int *)(*(int *)(param_4 + 8) + -4) + 0x1c),
                         *(char ***)(*(int *)(param_4 + 8) + -0xc));
    return uVar2 == *(uint *)(param_4 + -4);
  }
  return *(int *)(param_4 + -4) == *(int *)(*(int *)(*(int *)(param_4 + 8) + -0xc) + 0x14);
}

