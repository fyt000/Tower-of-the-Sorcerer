/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004196d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004196d0(int param_1,int *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  puVar1 = (undefined4 *)param_2[3];
  puVar2 = FUN_00419604(param_1,param_3);
  param_2[3] = (int)puVar2;
  if (puVar1 != puVar2) {
    FUN_00402cdc(param_2,extraout_EDX,extraout_ECX);
  }
  FUN_00419680(param_1,puVar1);
  return;
}

