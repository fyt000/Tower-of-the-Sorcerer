/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430e1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00430e1c(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x1d5) == '\0') {
    uVar1 = FUN_004074cc(0x42fa18,CONCAT31((int3)((uint)param_2 >> 8),1),0xf0d0);
    FUN_004031f8(uVar1);
  }
  return;
}

