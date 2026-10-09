/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f688.
 * Inferred types, shared tails and runtime effects require assembly review. */

HCURSOR root_0042f688(int *param_1,int param_2)

{
  HCURSOR pHVar1;
  uint uVar2;
  int iVar3;
  undefined2 extraout_var;
  tagPOINT tStack_14;
  undefined4 uStack_c;
  
  pHVar1 = (HCURSOR)FUN_00415c98(param_1,param_2);
  if (*(int *)(param_2 + 0xc) == 0) {
    *(undefined4 *)(param_2 + 0xc) = 1;
    GetCursorPos(&tStack_14);
    uVar2 = FUN_004052f4((undefined2 *)&tStack_14);
    uStack_c._2_2_ = (undefined2)(uVar2 >> 0x10);
    iVar3 = CONCAT22(extraout_var,uStack_c._2_2_);
    uStack_c = uVar2;
    uVar2 = FUN_00405284(uVar2,iVar3);
    iVar3 = FUN_00413cb8(param_1,0x84,0,uVar2);
    if (iVar3 == 1) {
      pHVar1 = (HCURSOR)FUN_00423d24(DAT_0048a6fc,-4);
      pHVar1 = SetCursor(pHVar1);
    }
    else {
      pHVar1 = (HCURSOR)(iVar3 + -8);
      if (iVar3 - 6U < 2) {
        pHVar1 = (HCURSOR)FUN_00423d24(DAT_0048a6fc,-2);
        pHVar1 = SetCursor(pHVar1);
      }
    }
  }
  return pHVar1;
}

