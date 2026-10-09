/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402218.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00402218(int param_1)

{
  char cVar1;
  uint *puVar2;
  undefined4 uVar3;
  undefined extraout_CL;
  undefined extraout_CL_00;
  undefined extraout_CL_01;
  undefined uVar4;
  undefined in_DL;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined extraout_DL_01;
  undefined extraout_DL_02;
  uint *puVar5;
  uint **ppuVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar7;
  code *pcVar8;
  
  DAT_0048a41c = 0;
  if ((DAT_0048a419 == '\0') && (cVar1 = FUN_004019d4(), in_DL = extraout_DL, cVar1 == '\0')) {
    DAT_0048a41c = 8;
    return 8;
  }
  uVar4 = 0;
  pcVar8 = thunk_FUN_00403140;
  uVar7 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffe0;
  if (DAT_0048a036 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
    in_DL = extraout_DL_00;
    uVar4 = extraout_CL;
  }
  ppuVar6 = (uint **)(param_1 + -4);
  puVar5 = *ppuVar6;
  if (((uint)puVar5 & 2) == 0) {
    DAT_0048a41c = 9;
    goto LAB_00402381;
  }
  _DAT_0048a400 = _DAT_0048a400 + -1;
  _DAT_0048a404 = _DAT_0048a404 - (((uint)puVar5 & 0x7ffffffc) - 4);
  if (((uint)puVar5 & 1) != 0) {
    puVar2 = *(uint **)(param_1 + -8);
    if (((int)puVar2 < 0xc) || (((uint)puVar2 & 0x80000003) != 0)) {
      DAT_0048a41c = 10;
      goto LAB_00402381;
    }
    ppuVar6 = (uint **)((int)ppuVar6 - (int)puVar2);
    if (puVar2 != ppuVar6[2]) {
      DAT_0048a41c = 10;
      goto LAB_00402381;
    }
    puVar5 = (uint *)((int)puVar5 + (int)puVar2);
    FUN_00401b7c((int *)ppuVar6);
    uVar4 = extraout_CL_00;
    in_DL = extraout_DL_01;
  }
  puVar5 = (uint *)((uint)puVar5 & 0x7ffffffc);
  puVar2 = (uint *)((int)ppuVar6 + (int)puVar5);
  if (puVar2 == DAT_0048a474) {
    DAT_0048a474 = (uint *)((int)DAT_0048a474 - (int)puVar5);
    DAT_0048a470 = DAT_0048a470 + (int)puVar5;
    if (0x3c00 < DAT_0048a470) {
      FUN_00401e3c();
      uVar4 = extraout_CL_01;
      in_DL = extraout_DL_02;
    }
    FUN_00403298(0,in_DL,uVar4,uVar7,pcVar8);
    return 0;
  }
  if ((*puVar2 & 2) == 0) {
    if (((puVar2[1] == 0) || (*puVar2 == 0)) || ((int)puVar2[2] < 0xc)) {
      DAT_0048a41c = 0xb;
      goto LAB_00402381;
    }
    puVar5 = (uint *)((int)puVar5 + puVar2[2]);
    FUN_00401b7c((int *)puVar2);
  }
  else {
    if ((*puVar2 & 0x7ffffffc) < 4) {
      DAT_0048a41c = 0xb;
      goto LAB_00402381;
    }
    *puVar2 = *puVar2 | 1;
  }
  FUN_00401dbc(ppuVar6,puVar5);
LAB_00402381:
  uVar3 = 0;
  *in_FS_OFFSET = uVar7;
  if (DAT_0048a036 != '\0') {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  return uVar3;
}

