/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409fdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00409fdc(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x10))();
  (**(code **)(*param_1 + 0x4c))(param_1,uVar1,param_2);
  return uVar1;
}

