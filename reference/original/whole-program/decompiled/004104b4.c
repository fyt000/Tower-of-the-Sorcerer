/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004104b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004104b4(int param_1,undefined4 param_2,undefined4 param_3,code *param_4,
                  undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_0041040c(param_1);
  if (-1 < iVar1 + -1) {
    iVar3 = 0;
    do {
      uVar2 = FUN_0041041c(param_1,iVar3);
      (*param_4)(param_5,uVar2);
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

