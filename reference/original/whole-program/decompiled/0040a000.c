/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a000.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0040a000(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x2c))();
  (**(code **)(*param_1 + 0x20))(param_1,uVar1,param_3);
  return uVar1;
}

