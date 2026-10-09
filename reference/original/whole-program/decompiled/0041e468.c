/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e468.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e468(int param_1,int *param_2,int *param_3)

{
  HICON hIcon;
  
  FUN_0041aa24(param_2,DAT_0041e49c);
  hIcon = (HICON)FUN_0041e4b8(param_1);
  DrawIcon((HDC)param_2[1],*param_3,param_3[1],hIcon);
  return;
}

