/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040627c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040627c(int param_1,undefined4 *param_2,uint param_3)

{
  undefined4 auStack_30 [8];
  undefined4 *local_10;
  undefined local_c;
  
  if (0x1f < (int)param_3) {
    param_3 = 0x1f;
  }
  FUN_004060d8(auStack_30,param_2,param_3);
  *(undefined *)((int)auStack_30 + param_3) = 0;
  local_c = 6;
  local_10 = auStack_30;
  FUN_0040592c(param_1 + 0xffa0,&local_10,0);
  return;
}

