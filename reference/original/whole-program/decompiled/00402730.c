/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402730.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402730(undefined4 param_1)

{
  LPVOID pvVar1;
  
  pvVar1 = FUN_00403498();
  *(undefined4 *)((int)pvVar1 + 4) = param_1;
  return;
}

