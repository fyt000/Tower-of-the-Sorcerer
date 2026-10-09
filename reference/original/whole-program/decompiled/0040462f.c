/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040462f.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined * FUN_0040462f(undefined *param_1,int param_2)

{
  int iVar1;
  LPVOID pvVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  while (0x40 < param_2) {
    param_2 = param_2 + -0x40;
    FUN_004045c4(param_1,&DAT_0048903c,0x40);
    pvVar2 = FUN_00403498();
    if (*(int *)((int)pvVar2 + 4) != 0) {
      return param_1;
    }
  }
  if (0 < param_2) {
    puVar4 = &DAT_0048903c;
    if ((*(int *)(param_1 + 4) == 0xd7b2) ||
       ((param_1 == &DAT_0048a208 && (FUN_0040447e(&DAT_0048a208), iRam0048a20c == 0xd7b2)))) {
      do {
        iVar1 = *(int *)(param_1 + 0xc);
        iVar3 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc);
        if (param_2 < iVar3) {
          *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_2;
          puVar5 = (undefined *)(*(int *)(param_1 + 0x14) + iVar1);
          for (; param_2 != 0; param_2 = param_2 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
            puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
          }
          return param_1;
        }
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + iVar3;
        param_2 = param_2 - iVar3;
        puVar5 = (undefined *)(*(int *)(param_1 + 0x14) + iVar1);
        for (; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
          puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
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
  return param_1;
}

