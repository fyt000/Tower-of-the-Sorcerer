/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413e2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00413e2c(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_4 + -4) + 0x1c);
  if (iVar1 != 0) {
    return CONCAT31((int3)((uint)iVar1 >> 8),
                    *(char *)(iVar1 + 0x3d) != *(char *)(*(int *)(param_4 + -8) + 0x3d));
  }
  return CONCAT31((int3)((uint)*(int *)(param_4 + -8) >> 8),
                  *(undefined *)(*(int *)(param_4 + -8) + 0x3d));
}

