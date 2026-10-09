/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402090.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * FUN_00402090(int param_1)

{
  uint *puVar1;
  char cVar2;
  uint uVar3;
  uint *puVar4;
  undefined in_CL;
  undefined extraout_CL;
  undefined extraout_CL_00;
  uint uVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar6;
  code *pcVar7;
  
  if ((DAT_0048a419 == '\0') && (cVar2 = FUN_004019d4(), in_CL = extraout_CL, cVar2 == '\0')) {
    return (uint *)0x0;
  }
  pcVar7 = thunk_FUN_00403140;
  uVar6 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffdc;
  if (DAT_0048a036 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
    in_CL = extraout_CL_00;
  }
  puVar4 = DAT_0048a474;
  uVar5 = param_1 + 7U & 0xfffffffc;
  if ((int)uVar5 < 0xc) {
    uVar5 = 0xc;
  }
  if ((int)uVar5 < 0x1001) {
    uVar3 = uVar5;
    if ((int)uVar5 < 0) {
      uVar3 = uVar5 + 3;
    }
    puVar1 = *(uint **)(DAT_0048a478 + -0xc + ((int)uVar3 >> 2) * 4);
    if (puVar1 != (uint *)0x0) {
      *(uint *)((int)puVar1 + uVar5) = *(uint *)((int)puVar1 + uVar5) & 0xfffffffe;
      puVar4 = (uint *)puVar1[1];
      if (puVar1 == puVar4) {
        uVar3 = uVar5;
        if ((int)uVar5 < 0) {
          uVar3 = uVar5 + 3;
        }
        *(undefined4 *)(DAT_0048a478 + -0xc + ((int)uVar3 >> 2) * 4) = 0;
      }
      else {
        uVar3 = uVar5;
        if ((int)uVar5 < 0) {
          uVar3 = uVar5 + 3;
        }
        *(uint **)(DAT_0048a478 + -0xc + ((int)uVar3 >> 2) * 4) = puVar4;
        uVar3 = *puVar1;
        *(uint **)(uVar3 + 4) = puVar4;
        *puVar4 = uVar3;
      }
      *puVar1 = puVar1[2] | 2;
      _DAT_0048a400 = _DAT_0048a400 + 1;
      _DAT_0048a404 = _DAT_0048a404 + (uVar5 - 4);
      FUN_00403298((char)(puVar1 + 1),(char)(puVar1[2] | 2),(char)puVar1,uVar6,pcVar7);
      return puVar1 + 1;
    }
  }
  if ((int)uVar5 <= DAT_0048a470) {
    DAT_0048a470 = DAT_0048a470 - uVar5;
    if (DAT_0048a470 < 0xc) {
      uVar5 = uVar5 + DAT_0048a470;
      DAT_0048a470 = 0;
    }
    DAT_0048a474 = (uint *)((int)DAT_0048a474 + uVar5);
    *puVar4 = uVar5 | 2;
    puVar4 = puVar4 + 1;
    _DAT_0048a400 = _DAT_0048a400 + 1;
    _DAT_0048a404 = _DAT_0048a404 + (uVar5 - 4);
    FUN_00403298((char)puVar4,(char)(uVar5 | 2),in_CL,uVar6,pcVar7);
    return puVar4;
  }
  FUN_00401f9c(uVar5);
  puVar4 = (uint *)0x0;
  *in_FS_OFFSET = uVar6;
  if (DAT_0048a036 != '\0') {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  return puVar4;
}

