/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004072b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_004072b8(void)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00403498();
  if (*piVar1 != 0) {
    piVar1 = (int *)FUN_00403498();
    return *(undefined4 *)(*piVar1 + 4);
  }
  return 0;
}

