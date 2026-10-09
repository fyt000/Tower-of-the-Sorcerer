/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004099a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004099a4(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = param_1[2];
  if (iVar1 == param_1[3]) {
    (**(code **)(*param_1 + 4))();
  }
  *(undefined4 *)(param_1[1] + iVar1 * 4) = param_2;
  param_1[2] = param_1[2] + 1;
  return iVar1;
}

