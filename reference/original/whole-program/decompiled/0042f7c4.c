/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f7c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0042f7c4(int param_1,undefined4 param_2,uint param_3)

{
  uint local_8;
  
  local_8 = param_3 & 0xffffff00;
  if (*(short *)(param_1 + 0x162) != 0) {
    param_1 = (**(code **)(param_1 + 0x160))
                        (*(undefined4 *)(param_1 + 0x164),param_1,param_2,&local_8,param_3);
  }
  return CONCAT31((int3)((uint)param_1 >> 8),(undefined)local_8);
}

