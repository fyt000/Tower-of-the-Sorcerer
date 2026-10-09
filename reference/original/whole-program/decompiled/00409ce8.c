/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409ce8.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00409ce8(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 < *(uint *)(param_1 + 4)) {
    return -(uint)((*(byte *)(*(int *)(param_1 + 8) + ((int)param_2 >> 3)) >> (param_2 & 7) & 1) !=
                  0) & 1;
  }
  uVar1 = FUN_004074cc(0x4089fc,CONCAT31((int3)(param_2 >> 8),1),0xf0b8);
  uVar2 = FUN_004031f8(uVar1);
  return uVar2;
}

