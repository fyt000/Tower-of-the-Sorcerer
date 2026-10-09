/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401f14.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00401f14(int param_1)

{
  undefined4 uVar1;
  int *local_c [2];
  
  FUN_00401794(param_1 + 4,local_c);
  if ((local_c[0] != (int *)0x0) && (uVar1 = FUN_00401e88(local_c), (char)uVar1 != '\0')) {
    return CONCAT31((int3)((uint)uVar1 >> 8),1);
  }
  return 0;
}

