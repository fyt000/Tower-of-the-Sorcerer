/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041021c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041021c(int param_1)

{
  int *piVar1;
  HMENU pHVar2;
  undefined4 uVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    piVar1 = FUN_00402c7c(*(int ***)(param_1 + 4),(int *)&PTR_FUN_0040f624);
    if ((char)piVar1 == '\0') {
      pHVar2 = CreateMenu();
      *(HMENU *)(param_1 + 0x24) = pHVar2;
      uVar3 = extraout_EDX_00;
    }
    else {
      pHVar2 = CreatePopupMenu();
      *(HMENU *)(param_1 + 0x24) = pHVar2;
      uVar3 = extraout_EDX;
    }
    if (*(int *)(param_1 + 0x24) == 0) {
      uVar3 = FUN_004074cc(0x40f184,CONCAT31((int3)((uint)uVar3 >> 8),1),0xf022);
      FUN_004031f8(uVar3);
    }
    FUN_004100a8(param_1);
  }
  return *(undefined4 *)(param_1 + 0x24);
}

