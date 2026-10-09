/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402ee8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00402ee8(int param_1,undefined4 param_2,char *param_3)

{
  ULONG_PTR UStack_10;
  char *pcStack_c;
  undefined4 uStack_8;
  int iStack_4;
  
  if (1 < DAT_00489004) {
    UStack_10 = 0x402ef9;
    pcStack_c = param_3;
    uStack_8 = param_2;
    iStack_4 = param_1;
    FUN_00402ec8(param_1,param_2,param_3);
    RaiseException(0xeedfad1,0,1,&UStack_10);
    param_1 = iStack_4;
  }
  return param_1;
}

