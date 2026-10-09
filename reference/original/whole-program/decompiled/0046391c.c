/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0046391c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_Exit1Click(int param_1,undefined4 param_2,int param_3)

{
  if (*(char *)(*(int *)(param_1 + 0x330) + 0x28) == '\x01') {
    FUN_00431188(*(int **)(param_1 + 0x2d8),*(int *)(param_1 + 0x330),param_3);
  }
  FUN_00402c34(DAT_0048c514);
  FUN_00402c34(DAT_0048c518);
  FUN_00402c34(DAT_0048c51c);
  FUN_00402c34(DAT_0048c520);
  FUN_00402c34(DAT_0048c524);
  FUN_00402c34(DAT_0048c528);
  FUN_00425018();
  return;
}

