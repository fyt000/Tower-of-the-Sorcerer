/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dad8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041dad8(int param_1)

{
  int iVar1;
  undefined4 extraout_EDX;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    FUN_0041dbac(param_1);
    iVar1 = FUN_0041d268(0x41d1c0,CONCAT31((int3)((uint)extraout_EDX >> 8),1),param_1);
    *(int *)(param_1 + 0x14) = iVar1;
    *(int *)(iVar1 + 0x28) = param_1;
    *(code **)(iVar1 + 0x24) = FUN_0041bd8c;
    *(int *)(iVar1 + 0x30) = param_1;
    *(code **)(iVar1 + 0x2c) = FUN_0041d8c4;
  }
  return *(undefined4 *)(param_1 + 0x14);
}

