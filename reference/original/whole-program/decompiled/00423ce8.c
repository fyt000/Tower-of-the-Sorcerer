/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423ce8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423ce8(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00402650(0xc);
  *puVar1 = *(undefined4 *)(param_1 + 0x34);
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  *(undefined4 **)(param_1 + 0x34) = puVar1;
  return;
}

