/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419b40.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00419b40(undefined *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined **ppuVar2;
  int iVar3;
  
  iVar3 = 0x2a;
  ppuVar2 = &PTR_s_clBlack_00489350;
  do {
    iVar1 = FUN_00405a34(*ppuVar2,param_1);
    if (iVar1 == 0) {
      *param_2 = ppuVar2[-1];
      return 1;
    }
    ppuVar2 = ppuVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0;
}

