/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432948.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00432948(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00409ce8(*(int *)(param_1 + 0x54),param_2);
  if ((char)uVar1 != '\0') {
    *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
    FUN_00409cbc(*(int *)(param_1 + 0x54),param_2,'\0');
  }
  return;
}

