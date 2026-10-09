/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402f10.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402f10(undefined4 param_1,ULONG_PTR param_2)

{
  ULONG_PTR UStack_4;
  
  if (1 < DAT_00489004) {
    UStack_4 = param_2;
    RaiseException(0xeedfad2,0,1,&UStack_4);
  }
  return;
}

