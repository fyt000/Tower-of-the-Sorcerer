/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042b074.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042b074(int param_1,int param_2,LONG *param_3,undefined param_4)

{
  int iVar1;
  RECT *pRVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffc8;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined *puStack_18;
  RECT RStack_14;
  
  puStack_28 = &stack0xfffffffc;
  puStack_18 = (undefined *)0x0;
  pRVar2 = &RStack_14;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    pRVar2->left = *param_3;
    param_3 = param_3 + 1;
    pRVar2 = (RECT *)&pRVar2->top;
  }
  puStack_2c = &LAB_0042b11f;
  puStack_30 = (undefined *)*in_FS_OFFSET;
  *in_FS_OFFSET = &puStack_30;
  if (*(short *)(param_1 + 0x12e) == 0) {
    FUN_0041a664(*(int **)(param_1 + 0x108),&RStack_14);
    iVar1 = (**(code **)(**(int **)(param_1 + 0x100) + 0x10))();
    if (param_2 < iVar1) {
      (**(code **)(**(int **)(param_1 + 0x100) + 0xc))
                (*(int **)(param_1 + 0x100),param_2,&puStack_18);
      FUN_0041a7c0(*(int **)(param_1 + 0x108),RStack_14.left + 2,RStack_14.top,puStack_18);
    }
  }
  else {
    in_stack_ffffffc8 = CONCAT31((int3)((uint)&RStack_14 >> 8),param_4);
    puStack_28 = &stack0xfffffffc;
    (**(code **)(param_1 + 300))
              (*(undefined4 *)(param_1 + 0x130),param_1,param_2,in_stack_ffffffc8,&RStack_14);
  }
  *in_FS_OFFSET = in_stack_ffffffc8;
  puStack_30 = &LAB_0042b126;
  FUN_004034dc((int *)&puStack_18);
  return;
}

