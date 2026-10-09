/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ba7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint root_0040ba7c(int param_1,undefined4 param_2,uint param_3)

{
  uint uStack_8;
  
  uStack_8 = param_3 & 0xffffff00;
  if (*(short *)(param_1 + 0x46) != 0) {
    (**(code **)(param_1 + 0x44))(*(undefined4 *)(param_1 + 0x48),param_1,param_2,&uStack_8);
  }
  return uStack_8 & 0xff;
}

