/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040aba4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_0040aba4(int param_1,undefined *param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined local_14;
  
  local_14 = 0;
  uVar3 = 0;
  iVar4 = *(int *)(param_1 + 0xc) + -1;
  if (-1 < iVar4) {
    do {
      uVar2 = iVar4 + uVar3 >> 1;
      iVar1 = FUN_00405a34(*(undefined **)(*(int *)(param_1 + 8) + uVar2 * 8),param_2);
      if (iVar1 < 0) {
        uVar3 = uVar2 + 1;
      }
      else {
        iVar4 = uVar2 - 1;
        if ((iVar1 == 0) && (local_14 = 1, *(char *)(param_1 + 0x15) != '\x01')) {
          uVar3 = uVar2;
        }
      }
    } while ((int)uVar3 <= iVar4);
  }
  *param_3 = uVar3;
  return local_14;
}

