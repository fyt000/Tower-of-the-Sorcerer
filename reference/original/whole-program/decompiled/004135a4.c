/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004135a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004135a4(int *param_1,int *param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00413554(param_1);
  FUN_004035bc(param_2,(undefined4 *)0x0,uVar1);
  if (uVar1 != 0) {
    FUN_00413564(param_1,*param_2,uVar1 + 1);
  }
  return;
}

