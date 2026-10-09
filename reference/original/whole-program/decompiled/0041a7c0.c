/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a7c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a7c0(int *param_1,int param_2,int param_3,undefined *param_4)

{
  int c;
  LPCSTR lpString;
  LONG LVar1;
  
  (**(code **)(*param_1 + 0x10))();
  FUN_0041aa24(param_1,DAT_0041a82c);
  c = FUN_00403650((int)param_4);
  lpString = FUN_00403814(param_4);
  TextOutA((HDC)param_1[1],param_2,param_3,lpString,c);
  LVar1 = FUN_0041a830(param_1,param_4);
  FUN_0041a6d8(param_1,LVar1 + param_2,param_3);
  (**(code **)(*param_1 + 0xc))();
  return;
}

