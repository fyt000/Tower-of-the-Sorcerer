/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402f2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00402f2c(undefined4 param_1,ULONG_PTR param_2)

{
  ULONG_PTR UStack_8;
  undefined4 uStack_4;
  
  if (1 < DAT_00489004) {
    UStack_8 = param_2;
    uStack_4 = param_1;
    RaiseException(0xeedfad3,0,2,&UStack_8);
    param_1 = uStack_4;
  }
  return param_1;
}

