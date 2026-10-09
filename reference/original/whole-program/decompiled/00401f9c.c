/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401f9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * FUN_00401f9c(uint param_1)

{
  uint *puVar1;
  uint *puVar2;
  undefined4 uVar3;
  uint uVar4;
  
  while ((puVar1 = DAT_0048a46c, puVar2 = DAT_0048a464, (int)DAT_0048a464[2] < (int)param_1 &&
         (uVar4 = DAT_0048a46c[2], puVar2 = DAT_0048a46c, (int)uVar4 < (int)param_1))) {
    DAT_0048a46c[2] = param_1;
    puVar2 = puVar1;
    do {
      puVar2 = (uint *)puVar2[1];
    } while ((int)puVar2[2] < (int)param_1);
    DAT_0048a46c[2] = uVar4;
    puVar1 = puVar2;
    if ((puVar2 != DAT_0048a46c) ||
       (((int)param_1 < 0x1001 &&
        (puVar2 = (uint *)FUN_00401f74(param_1), puVar1 = DAT_0048a46c, puVar2 != (uint *)0x0))))
    break;
    uVar3 = FUN_00401f14(param_1);
    puVar2 = DAT_0048a474;
    if ((char)uVar3 == '\0') {
      return (uint *)0x0;
    }
    if ((int)param_1 <= DAT_0048a470) {
      DAT_0048a470 = DAT_0048a470 - param_1;
      if (DAT_0048a470 < 0xc) {
        param_1 = param_1 + DAT_0048a470;
        DAT_0048a470 = 0;
      }
      DAT_0048a474 = (uint *)((int)DAT_0048a474 + param_1);
      *puVar2 = param_1 | 2;
      _DAT_0048a400 = _DAT_0048a400 + 1;
      _DAT_0048a404 = _DAT_0048a404 + (param_1 - 4);
      return puVar2 + 1;
    }
  }
  DAT_0048a46c = puVar1;
  FUN_00401b7c((int *)puVar2);
  uVar4 = puVar2[2];
  if ((int)(uint *)(uVar4 - param_1) < 0xc) {
    if (puVar2 == DAT_0048a46c) {
      DAT_0048a46c = (uint *)puVar2[1];
    }
    *(uint *)((int)puVar2 + uVar4) = *(uint *)((int)puVar2 + uVar4) & 0xfffffffe;
  }
  else {
    FUN_00401dbc((uint **)((int)puVar2 + param_1),(uint *)(uVar4 - param_1));
    uVar4 = param_1;
  }
  *puVar2 = uVar4 | 2;
  _DAT_0048a400 = _DAT_0048a400 + 1;
  _DAT_0048a404 = _DAT_0048a404 + (uVar4 - 4);
  return puVar2 + 1;
}

