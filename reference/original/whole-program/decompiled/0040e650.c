/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e650.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e650(int *param_1,int param_2)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  (**(code **)(*param_1 + 0x1c))(param_1,param_2,0,*(undefined4 *)(param_2 + 8));
  FUN_0040e5fc((int)param_1,param_2,extraout_ECX);
  FUN_0040eb1c(param_2,'\x01');
  if ((*(byte *)(param_1 + 7) & 0x10) != 0) {
    FUN_0040eadc(param_2,CONCAT31((int3)((uint)extraout_EDX >> 8),1));
  }
  (**(code **)(*param_1 + 0x10))(param_1,param_2,0);
  return;
}

