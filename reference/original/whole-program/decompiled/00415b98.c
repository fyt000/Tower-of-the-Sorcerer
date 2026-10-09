/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415b98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00415b98(int *param_1,int param_2)

{
  HBRUSH hbr;
  RECT RStack_18;
  
  hbr = (HBRUSH)FUN_0041a188(param_1[0x2f]);
  (**(code **)(*param_1 + 0x2c))(param_1,&RStack_18);
  FillRect(*(HDC *)(param_2 + 4),&RStack_18,hbr);
  *(undefined4 *)(param_2 + 0xc) = 1;
  return;
}

