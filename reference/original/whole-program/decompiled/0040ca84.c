/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ca84.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ca84(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int local_14;
  undefined local_10;
  int local_c;
  undefined local_8;
  
  iVar2 = 0;
  FUN_004034dc(param_2);
  if (DAT_0048a610 != (code *)0x0) {
    FUN_00403570(param_2,param_1);
    while( true ) {
      iVar1 = (*DAT_0048a610)(*param_2);
      if (iVar1 == 0) break;
      iVar2 = iVar2 + 1;
      local_10 = 0xb;
      local_8 = 0;
      local_14 = param_1;
      local_c = iVar2;
      FUN_0040661c((byte *)"%s_%d",&local_14,1,param_2);
    }
  }
  return;
}

