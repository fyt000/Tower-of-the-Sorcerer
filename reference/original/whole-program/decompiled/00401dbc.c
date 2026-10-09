/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401dbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401dbc(uint **param_1,uint *param_2)

{
  uint **ppuVar1;
  uint *puVar2;
  uint **ppuVar3;
  undefined4 uVar4;
  
  param_1[2] = param_2;
  *(uint **)((int)param_1 + (int)param_2 + -4) = param_2;
  if ((int)param_2 < 0x1001) {
    ppuVar1 = *(uint ***)(DAT_0048a478 + -0xc + ((uint)param_2 & 0xfffffffc));
    if (ppuVar1 == (uint **)0x0) {
      *(uint ***)(DAT_0048a478 + -0xc + ((uint)param_2 & 0xfffffffc)) = param_1;
      param_1[1] = (uint *)param_1;
      *param_1 = (uint *)param_1;
    }
    else {
      puVar2 = *ppuVar1;
      param_1[1] = (uint *)ppuVar1;
      *param_1 = puVar2;
      *ppuVar1 = (uint *)param_1;
      puVar2[1] = (uint)param_1;
    }
  }
  else {
    if ((0x3bff < (int)param_2) &&
       (uVar4 = FUN_00401d24((uint *)param_1,(int)param_2), (char)uVar4 != '\0')) {
      return;
    }
    ppuVar1 = DAT_0048a46c;
    puVar2 = *DAT_0048a46c;
    ppuVar3 = param_1;
    param_1[1] = (uint *)DAT_0048a46c;
    DAT_0048a46c = ppuVar3;
    *param_1 = puVar2;
    *ppuVar1 = (uint *)param_1;
    puVar2[1] = (uint)param_1;
  }
  return;
}

