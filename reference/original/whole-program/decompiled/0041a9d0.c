/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a9d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a9d0(int *param_1,int param_2)

{
  tagPOINT local_10;
  
  if (param_2 != param_1[1]) {
    if (param_1[1] != 0) {
      FUN_0041a970((int)param_1);
      FUN_0041a8e0(param_1,&local_10);
      param_1[6] = local_10.x;
      param_1[7] = local_10.y;
      param_1[1] = 0;
      *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xfe;
    }
    if (param_2 != 0) {
      *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) | 1;
      param_1[1] = param_2;
      FUN_0041a904(param_1,param_1 + 6);
    }
  }
  return;
}

