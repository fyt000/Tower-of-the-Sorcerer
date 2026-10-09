/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040af50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040af50(undefined4 *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  if (param_3 != 0) {
    iVar1 = (**(code **)*param_1)(param_1,param_2,param_3);
    if (param_3 != iVar1) {
      uVar2 = FUN_004074cc(0x4088b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf003);
      FUN_004031f8(uVar2);
    }
  }
  return;
}

