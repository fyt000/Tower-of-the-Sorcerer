/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c38c.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Type propagation algorithm not settling */

void root_0041c38c(int param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  bool bVar2;
  undefined4 uStack_164;
  code *pcStack_160;
  undefined *puStack_15c;
  int aiStack_14c [64];
  undefined4 uStack_4c;
  int *piStack_c;
  undefined4 *puStack_8;
  
  puStack_15c = (undefined *)0x41c3ac;
  puStack_8 = param_2;
  (**(code **)*param_2)(param_2,&uStack_4c,1);
  puStack_15c = (undefined *)0x41c3bb;
  (**(code **)*puStack_8)(puStack_8,(undefined *)((int)&uStack_4c + 1),(undefined)uStack_4c);
  piVar1 = (int *)PTR_PTR_0048956c;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return;
    }
    puStack_15c = (undefined *)0x41c3d7;
    FUN_00402b7c(*piVar1,(byte *)aiStack_14c);
    bVar2 = (byte)aiStack_14c[0] + 1 == 0;
    puStack_15c = (undefined *)0x41c3ea;
    FUN_00402948(aiStack_14c,&uStack_4c,(byte)aiStack_14c[0] + 1);
    if (bVar2) break;
    piVar1 = (int *)piVar1[4];
  }
  puStack_15c = (undefined *)0x41c3f8;
  piStack_c = (int *)(**(code **)(*piVar1 + 0xc))(*piVar1,1);
  pcStack_160 = thunk_FUN_00402f4c;
  uStack_164 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_164;
  puStack_15c = &stack0xfffffffc;
  (**(code **)(*piStack_c + 0x24))(piStack_c,puStack_8);
  *in_FS_OFFSET = uStack_164;
  puStack_15c = (undefined *)0x41c43d;
  FUN_00402c34(*(int **)(param_1 + 4));
  *(int **)(param_1 + 4) = piStack_c;
  piStack_c[2] = param_1;
  piStack_c[1] = (int)FUN_0041c378;
  puStack_15c = (undefined *)0x41c456;
  FUN_0041c378(param_1);
  return;
}

