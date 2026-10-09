/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d458.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040d458(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  
  *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) | 4;
  if (*(int *)(param_1 + 0x2c) != 0) {
    iVar1 = FUN_0040d408((undefined *)param_2[2],param_2,param_3,(int)&stack0xfffffffc);
    *(int *)(param_1 + 0x1c) = iVar1;
  }
  (**(code **)(*param_2 + 0x20))(param_2,param_1);
  *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) & 0xfb;
  return;
}

