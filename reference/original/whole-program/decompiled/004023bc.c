/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004023bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004023bc(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_18;
  uint local_14;
  
  uVar7 = param_2 + 7U & 0xfffffffc;
  if ((int)uVar7 < 0xc) {
    uVar7 = 0xc;
  }
  puVar6 = (uint *)(param_1 + -4);
  uVar9 = *puVar6 & 0x7ffffffc;
  piVar2 = (int *)((int)puVar6 + uVar9);
  uVar8 = uVar7;
  if (uVar9 < uVar7) {
    do {
      local_14 = uVar7 - uVar9;
      if ((int *)((int)puVar6 + uVar9) == DAT_0048a474) {
        if ((int)local_14 <= DAT_0048a470) {
          DAT_0048a470 = DAT_0048a470 - local_14;
          DAT_0048a474 = (int *)((int)DAT_0048a474 + local_14);
          if (DAT_0048a470 < 0xc) {
            DAT_0048a474 = (int *)((int)DAT_0048a474 + DAT_0048a470);
            uVar7 = uVar7 + DAT_0048a470;
            DAT_0048a470 = 0;
          }
          _DAT_0048a404 = _DAT_0048a404 + (uVar7 - uVar9);
          uVar8 = *puVar6;
          *puVar6 = uVar7 | uVar8 & 0x80000003;
          return CONCAT31((int3)((uVar8 & 0x80000003) >> 8),1);
        }
        FUN_00401e3c();
      }
      puVar4 = (uint *)((int)puVar6 + uVar9);
      if ((*(byte *)puVar4 & 2) == 0) {
        uVar1 = puVar4[2];
        if (local_14 <= uVar1) {
          FUN_00401b7c((int *)puVar4);
          puVar4 = (uint *)(uVar1 - local_14);
          if ((int)puVar4 < 0xc) {
            puVar5 = (uint *)((int)puVar6 + uVar7 + (int)puVar4);
            *puVar5 = *puVar5 & 0xfffffffe;
            uVar8 = uVar7 + (int)puVar4;
          }
          else {
            FUN_00401dbc((uint **)((int)puVar6 + uVar7),puVar4);
          }
          goto LAB_0040256b;
        }
        puVar4 = (uint *)((int)puVar4 + uVar1);
        local_14 = local_14 - uVar1;
      }
    } while (((*puVar4 & 0x80000000) != 0) &&
            (uVar3 = FUN_00401f40((LPVOID)((*puVar4 & 0x7ffffffc) + (int)puVar4),local_14),
            (char)uVar3 != '\0'));
    uVar3 = 0;
  }
  else {
    local_18 = uVar9 - uVar7;
    if (piVar2 == DAT_0048a474) {
      DAT_0048a474 = (int *)((int)DAT_0048a474 - local_18);
      DAT_0048a470 = DAT_0048a470 + local_18;
      if (DAT_0048a470 < 0xc) {
        DAT_0048a474 = (int *)((int)DAT_0048a474 + local_18);
        DAT_0048a470 = DAT_0048a470 - local_18;
        uVar8 = uVar9;
      }
    }
    else {
      if ((*(byte *)piVar2 & 2) == 0) {
        local_18 = local_18 + piVar2[2];
        FUN_00401b7c(piVar2);
      }
      uVar8 = uVar9;
      if (0xb < (int)local_18) {
        *(uint *)((int)puVar6 + uVar7) = local_18 | 2;
        FUN_00401c30((int)((uint *)((int)puVar6 + uVar7) + 1));
        uVar8 = uVar7;
      }
    }
LAB_0040256b:
    _DAT_0048a404 = _DAT_0048a404 + (uVar8 - uVar9);
    uVar7 = *puVar6;
    *puVar6 = uVar8 | uVar7 & 0x80000003;
    uVar3 = CONCAT31((int3)((uVar7 & 0x80000003) >> 8),1);
  }
  return uVar3;
}

