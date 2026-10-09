/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422ac8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422ac8(int *param_1,int param_2)

{
  HBRUSH hbr;
  RECT RStack_18;
  
  if (*(char *)((int)param_1 + 0x11a) == '\x01') {
    if ((*(char *)((int)param_1 + 0x11a) == '\x01') && ((*(byte *)(param_1 + 7) & 0x10) == 0)) {
      hbr = (HBRUSH)FUN_0041a188(*(int *)(*(int *)(DAT_0048a6f8 + 0x28) + 0xbc));
      (**(code **)(*param_1 + 0x2c))(param_1,&RStack_18);
      FillRect(*(HDC *)(param_2 + 4),&RStack_18,hbr);
    }
    else {
      (**(code **)(*param_1 + -0x10))(param_1,param_2);
    }
  }
  return;
}

