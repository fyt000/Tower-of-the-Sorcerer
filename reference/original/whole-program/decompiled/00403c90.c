/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403c90.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403c90(VARIANT *param_1,VARIANTARG *param_2)

{
  int iVar1;
  HRESULT HVar2;
  int iVar3;
  
  if (param_1 != param_2) {
    if (7 < (param_1->n1).n2.vt) {
      if ((param_1->n1).n2.vt == 0x100) {
        FUN_004034dc((int *)((int)&param_1->n1 + 8));
      }
      else {
        VariantClear(param_1);
      }
    }
    if (*(ushort *)param_2 < 8) {
      *(undefined4 *)&param_1->n1 = *(undefined4 *)param_2;
      *(undefined4 *)((int)&param_1->n1 + 8) = *(undefined4 *)&param_2->field_0x8;
      *(undefined4 *)((int)&param_1->n1 + 0xc) = *(undefined4 *)&param_2->field_0xc;
      return;
    }
    if (*(short *)param_2 == 0x100) {
      iVar1 = *(int *)&param_2->field_0x8;
      if ((iVar1 != 0) &&
         (iVar3 = *(int *)(iVar1 + -8) + 1,
         iVar3 != 0 && SCARRY4(*(int *)(iVar1 + -8),1) == iVar3 < 0)) {
        *(int *)(iVar1 + -8) = iVar3;
      }
      (param_1->n1).n2.vt = 0x100;
      *(int *)((int)&param_1->n1 + 8) = iVar1;
      return;
    }
    (param_1->n1).n2.vt = 0;
    HVar2 = VariantCopyInd(param_1,param_2);
    if (HVar2 != 0) {
      FUN_004026d0(CONCAT31((int3)((uint)HVar2 >> 8),0x10));
      return;
    }
  }
  return;
}

