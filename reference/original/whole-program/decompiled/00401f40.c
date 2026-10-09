/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401f40.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00401f40(LPVOID param_1,int param_2)

{
  undefined4 uVar1;
  int *local_10 [2];
  
  FUN_00401824(param_1,param_2 + 4,local_10);
  if ((local_10[0] != (int *)0x0) && (uVar1 = FUN_00401e88(local_10), (char)uVar1 != '\0')) {
    return CONCAT31((int3)((uint)uVar1 >> 8),1);
  }
  return 0;
}

