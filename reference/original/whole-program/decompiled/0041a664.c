/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a664.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a664(int *param_1,RECT *param_2)

{
  HBRUSH hbr;
  
  (**(code **)(*param_1 + 0x10))();
  FUN_0041aa24(param_1,DAT_0041a69c);
  hbr = (HBRUSH)FUN_0041a188(param_1[5]);
  FillRect((HDC)param_1[1],param_2,hbr);
  (**(code **)(*param_1 + 0xc))();
  return;
}

