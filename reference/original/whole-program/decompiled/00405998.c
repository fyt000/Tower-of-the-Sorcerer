/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405998.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405998(undefined4 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00402650(0xc);
  *puVar1 = DAT_00489084;
  puVar1[1] = DAT_0048a028;
  puVar1[2] = param_1;
  DAT_00489084 = puVar1;
  DAT_0048a028 = &LAB_00405970;
  return;
}

