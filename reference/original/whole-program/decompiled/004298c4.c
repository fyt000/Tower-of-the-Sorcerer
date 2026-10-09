/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004298c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004298c4(int *param_1,int param_2)

{
  HBRUSH hbr;
  RECT RStack_18;
  
  if (*(byte *)((int)param_1 + 0x109) < 2) {
    hbr = (HBRUSH)FUN_0041a188(*(int *)(param_1[8] + 0xbc));
    (**(code **)(*param_1 + 0x2c))(param_1,&RStack_18);
    FillRect(*(HDC *)(param_2 + 4),&RStack_18,hbr);
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return;
}

