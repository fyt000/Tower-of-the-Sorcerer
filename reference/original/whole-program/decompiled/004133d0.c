/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004133d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004133d0(int *param_1,uint *param_2)

{
  int **ppiVar1;
  bool bVar2;
  undefined *puVar3;
  int *piVar4;
  undefined4 *in_FS_OFFSET;
  undefined uVar5;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  uint *puStack_c;
  uint *puStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_c = (uint *)0x0;
  puStack_20 = &LAB_0041345f;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  uVar5 = (*(byte *)(param_1 + 0xd) & 0x20) == 0;
  puVar3 = &stack0xfffffffc;
  puStack_8 = param_2;
  if (!(bool)uVar5) {
    FUN_004135a4(param_1,(int *)&puStack_c);
    FUN_00403760((uint *)param_1[2],puStack_c);
    puVar3 = puStack_1c;
    if ((bool)uVar5) {
      ppiVar1 = (int **)param_1[1];
      if (ppiVar1 != (int **)0x0) {
        piVar4 = FUN_00402c7c(ppiVar1,(int *)&PTR_FUN_004115fc);
        if (((char)piVar4 != '\0') && (puVar3 = puStack_1c, (*(byte *)(ppiVar1 + 7) & 1) != 0))
        goto LAB_0041342b;
      }
      bVar2 = true;
      goto LAB_00413431;
    }
  }
LAB_0041342b:
  puStack_1c = puVar3;
  bVar2 = false;
LAB_00413431:
  FUN_0040e9b8(param_1,puStack_8);
  if (bVar2) {
    FUN_004135d4(param_1,puStack_8);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00413466;
  puStack_20 = (undefined *)0x41345e;
  FUN_004034dc((int *)&puStack_c);
  return;
}

