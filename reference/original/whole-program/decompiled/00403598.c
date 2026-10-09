/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403598.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 * FUN_00403598(int param_1)

{
  undefined4 *puVar1;
  
  if (0 < param_1) {
    puVar1 = (undefined4 *)FUN_00402650(param_1 + 9);
    puVar1[1] = param_1;
    *puVar1 = 1;
    *(undefined *)((int)(puVar1 + 2) + param_1) = 0;
    return puVar1 + 2;
  }
  return (undefined4 *)0x0;
}

