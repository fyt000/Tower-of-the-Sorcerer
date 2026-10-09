/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a05c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a05c(int param_1,undefined4 param_2,LONG *param_3,undefined param_4)

{
  int iVar1;
  RECT *pRVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffc8;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined *local_18;
  RECT local_14;
  
  puStack_28 = &stack0xfffffffc;
  local_18 = (undefined *)0x0;
  pRVar2 = &local_14;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    pRVar2->left = *param_3;
    param_3 = param_3 + 1;
    pRVar2 = (RECT *)&pRVar2->top;
  }
  puStack_2c = &LAB_0042a0f8;
  puStack_30 = (undefined *)*in_FS_OFFSET;
  *in_FS_OFFSET = &puStack_30;
  if (*(short *)(param_1 + 0x14a) == 0) {
    FUN_0041a664(*(int **)(param_1 + 0x104),&local_14);
    (**(code **)(**(int **)(param_1 + 0x100) + 0xc))(*(int **)(param_1 + 0x100),param_2,&local_18);
    FUN_0041a7c0(*(int **)(param_1 + 0x104),local_14.left + 2,local_14.top,local_18);
  }
  else {
    in_stack_ffffffc8 = CONCAT31((int3)((uint)&local_14 >> 8),param_4);
    puStack_28 = &stack0xfffffffc;
    (**(code **)(param_1 + 0x148))
              (*(undefined4 *)(param_1 + 0x14c),param_1,param_2,in_stack_ffffffc8,&local_14);
  }
  *in_FS_OFFSET = in_stack_ffffffc8;
  puStack_30 = &LAB_0042a0ff;
  FUN_004034dc((int *)&local_18);
  return;
}

