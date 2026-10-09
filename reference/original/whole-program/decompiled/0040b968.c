/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b968.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b968(int param_1,undefined *param_2,undefined param_3,undefined param_4,
                 undefined param_5,code *param_6,undefined4 param_7)

{
  int iVar1;
  
  iVar1 = FUN_00405a34(param_2,*(undefined **)(param_1 + 0x50));
  if (iVar1 == 0) {
    (*param_6)(param_7,param_1);
    FUN_004034dc((int *)(param_1 + 0x50));
  }
  return;
}

