/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004036be.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004036be(int *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  puVar1 = FUN_00403598(param_2[-1] + param_3[-1]);
  FUN_00402870(param_2,puVar1,param_2[-1]);
  FUN_00402870(param_3,(undefined4 *)((int)puVar1 + param_2[-1]),param_3[-1]);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[-2] = puVar1[-2] + -1;
  }
  FUN_0040352c(param_1,puVar1);
  return;
}

