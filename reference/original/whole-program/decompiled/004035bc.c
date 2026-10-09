/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004035bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004035bc(int *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 *puVar1;
  
  puVar1 = FUN_00403598(param_3);
  if (param_2 != (undefined4 *)0x0) {
    FUN_00402870(param_2,puVar1,param_3);
  }
  FUN_004034dc(param_1);
  *param_1 = (int)puVar1;
  return;
}

