/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004123c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_004123c8(undefined *param_1,int *param_2)

{
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  
  iVar3 = 0x14;
  ppuVar2 = &PTR_s_crDefault_00489284;
  do {
    iVar1 = FUN_00405a34(*ppuVar2,param_1);
    if (iVar1 == 0) {
      *param_2 = (int)*(short *)(ppuVar2 + -1);
      return 1;
    }
    ppuVar2 = ppuVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0;
}

