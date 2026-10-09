/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004045c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined * FUN_004045c4(undefined *param_1,undefined *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  byte bVar4;
  
  bVar4 = 0;
  if ((*(int *)(param_1 + 4) == 0xd7b2) ||
     ((param_1 == &DAT_0048a208 && (FUN_0040447e(&DAT_0048a208), iRam0048a20c == 0xd7b2)))) {
    do {
      iVar1 = *(int *)(param_1 + 0xc);
      iVar2 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc);
      if (param_3 < iVar2) {
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_3;
        puVar3 = (undefined *)(*(int *)(param_1 + 0x14) + iVar1);
        for (; param_3 != 0; param_3 = param_3 + -1) {
          *puVar3 = *param_2;
          param_2 = param_2 + (uint)bVar4 * -2 + 1;
          puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
        }
        return param_1;
      }
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + iVar2;
      param_3 = param_3 - iVar2;
      puVar3 = (undefined *)(*(int *)(param_1 + 0x14) + iVar1);
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *param_2;
        param_2 = param_2 + (uint)bVar4 * -2 + 1;
        puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
      }
      iVar1 = (**(code **)(param_1 + 0x1c))();
    } while (iVar1 == 0);
    FUN_00402730(iVar1);
  }
  else {
    param_1 = (undefined *)FUN_00402730(0x69);
  }
  return param_1;
}

