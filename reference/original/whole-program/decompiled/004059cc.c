/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004059cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004059cc(undefined *param_1,LPSTR *param_2)

{
  uint cchLength;
  undefined4 *puVar1;
  
  cchLength = FUN_00403650((int)param_1);
  puVar1 = (undefined4 *)FUN_00403814(param_1);
  FUN_004035bc((int *)param_2,puVar1,cchLength);
  CharLowerBuffA(*param_2,cchLength);
  return;
}

