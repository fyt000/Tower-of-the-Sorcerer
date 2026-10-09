/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401bd0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 * FUN_00401bd0(uint param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_0048a47c;
  while( true ) {
    if ((undefined4 **)puVar1 == &DAT_0048a47c) {
      DAT_0048a41c = 3;
      return (undefined4 *)0x0;
    }
    if (((uint)puVar1[2] <= param_1) && (param_1 < (uint)(puVar1[2] + puVar1[3]))) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}

