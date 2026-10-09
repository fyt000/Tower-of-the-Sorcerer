/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432860.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00432860(int *param_1)

{
  uint uVar1;
  
  uVar1 = FUN_00409d00(param_1[0x15]);
  if (*(int *)(param_1[0x15] + 4) <= (int)uVar1) {
    uVar1 = FUN_00417ad0(param_1,(int *)0x0,(int *)0x0);
    FUN_00409c18(param_1[0x15],uVar1 + 1);
  }
  FUN_00409cbc(param_1[0x15],uVar1,'\x01');
  return uVar1;
}

