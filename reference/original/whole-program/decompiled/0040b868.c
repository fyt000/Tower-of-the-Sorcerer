/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b868.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b868(int param_1,undefined *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_0048a61c[2] + -1;
  if (-1 < iVar3) {
    do {
      piVar1 = (int *)FUN_00409a40(DAT_0048a61c,iVar3);
      if ((param_1 == 0) || (param_1 == piVar1[2])) {
        if (param_2 != (undefined *)0x0) {
          iVar2 = FUN_00405a34(param_2,(undefined *)piVar1[4]);
          if (iVar2 != 0) goto LAB_0040b8ba;
        }
        FUN_004099e4(DAT_0048a61c,iVar3);
        FUN_00402c34(piVar1);
      }
LAB_0040b8ba:
      iVar3 = iVar3 + -1;
    } while (iVar3 != -1);
  }
  return;
}

