/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417fdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417fdc(int *param_1,int *param_2)

{
  HIMAGELIST p_Var1;
  
  if (param_2 != (int *)0x0) {
    p_Var1 = (HIMAGELIST)FUN_00417984(param_2);
    FUN_00417eb4(param_1,p_Var1);
  }
  return;
}

