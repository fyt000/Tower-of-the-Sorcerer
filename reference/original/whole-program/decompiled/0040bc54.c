/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bc54.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bc54(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  iVar1 = (**(code **)**(undefined4 **)(param_1 + 4))
                    (*(undefined4 **)(param_1 + 4),*(undefined4 *)(param_1 + 8),
                     *(undefined4 *)(param_1 + 0xc));
  *(int *)(param_1 + 0x14) = iVar1;
  if (iVar1 == 0) {
    uVar2 = FUN_004074cc(0x4088b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf003);
    FUN_004031f8(uVar2);
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}

