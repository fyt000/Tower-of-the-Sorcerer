/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004062e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004062e0(byte *param_1,byte *param_2,byte *param_3,undefined4 param_4,undefined4 param_5,
                 int param_6)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  undefined3 uVar5;
  undefined4 uVar4;
  byte *pbVar6;
  byte *extraout_ECX;
  byte *extraout_ECX_00;
  byte *extraout_ECX_01;
  byte *extraout_EDX;
  byte *extraout_EDX_00;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  bool bVar12;
  byte bVar13;
  int local_10;
  byte *local_c;
  byte *local_8;
  
  bVar13 = 0;
  pbVar6 = param_3 + param_6;
  uVar3 = 0;
  local_c = (byte *)0x0;
  local_10 = 0;
  local_8 = param_1;
LAB_004062fb:
  if (param_2 != (byte *)0x0) {
    do {
      if (param_3 == pbVar6) break;
      pbVar9 = param_3 + (uint)bVar13 * -2 + 1;
      bVar1 = *param_3;
      uVar5 = (undefined3)(uVar3 >> 8);
      uVar3 = CONCAT31(uVar5,bVar1);
      param_3 = pbVar9;
      if (bVar1 == 0x25) {
        if (pbVar9 == pbVar6) break;
        param_3 = pbVar9 + (uint)bVar13 * -2 + 1;
        uVar3 = CONCAT31(uVar5,*pbVar9);
        if (*pbVar9 != 0x25) goto code_r0x00406321;
      }
      *param_1 = (byte)uVar3;
      param_2 = param_2 + -1;
      param_1 = param_1 + (uint)bVar13 * -2 + 1;
      if (param_2 == (byte *)0x0) break;
    } while( true );
  }
LAB_0040630d:
  FUN_004065dc();
  return;
code_r0x00406321:
  pbVar9 = param_3 + -2;
  while( true ) {
    cVar2 = (char)uVar3;
    pbVar10 = param_3;
    if (cVar2 == '-') {
      if (param_3 == pbVar6) goto LAB_0040630d;
      pbVar10 = param_3 + (uint)bVar13 * -2 + 1;
      uVar3 = CONCAT31((int3)(uVar3 >> 8),*param_3);
    }
    uVar3 = FUN_004063b9(uVar3,param_2,pbVar6);
    uVar5 = (undefined3)(uVar3 >> 8);
    pbVar6 = extraout_ECX;
    if ((char)uVar3 != ':') break;
    local_c = pbVar9;
    if (pbVar10 == extraout_ECX) goto LAB_0040630d;
    param_3 = pbVar10 + (uint)bVar13 * -2 + 1;
    uVar3 = CONCAT31(uVar5,*pbVar10);
    param_2 = extraout_EDX;
  }
  pbVar7 = extraout_EDX;
  param_3 = pbVar10;
  if ((char)uVar3 == '.') {
    if (pbVar10 == extraout_ECX) goto LAB_0040630d;
    param_3 = pbVar10 + (uint)bVar13 * -2 + 1;
    uVar3 = FUN_004063b9(CONCAT31(uVar5,*pbVar10),extraout_EDX,extraout_ECX);
    pbVar6 = extraout_ECX_00;
    pbVar7 = extraout_EDX_00;
  }
  uVar4 = FUN_00406402((char)uVar3,pbVar7,pbVar6);
  pbVar9 = pbVar9 + -(int)extraout_ECX_01;
  if (pbVar9 < extraout_ECX_01) {
    pbVar9 = (byte *)0x0;
  }
  pbVar10 = extraout_ECX_01;
  pbVar11 = param_3;
  if (cVar2 == '-') {
    bVar12 = pbVar7 < extraout_ECX_01;
    pbVar7 = pbVar7 + -(int)extraout_ECX_01;
    if (bVar12) {
      pbVar10 = extraout_ECX_01 + (int)pbVar7;
      pbVar7 = (byte *)0x0;
    }
    for (; pbVar10 != (byte *)0x0; pbVar10 = pbVar10 + -1) {
      *param_1 = *pbVar11;
      pbVar11 = pbVar11 + (uint)bVar13 * -2 + 1;
      param_1 = param_1 + (uint)bVar13 * -2 + 1;
    }
  }
  pbVar8 = pbVar7 + -(int)pbVar9;
  if (pbVar7 < pbVar9) {
    pbVar9 = pbVar9 + (int)pbVar8;
    pbVar8 = (byte *)0x0;
  }
  uVar3 = CONCAT31((int3)((uint)uVar4 >> 8),0x20);
  for (; pbVar9 != (byte *)0x0; pbVar9 = pbVar9 + -1) {
    *param_1 = 0x20;
    param_1 = param_1 + (uint)bVar13 * -2 + 1;
  }
  param_2 = pbVar8 + -(int)pbVar10;
  if (pbVar8 < pbVar10) {
    pbVar10 = pbVar10 + (int)param_2;
    param_2 = (byte *)0x0;
  }
  for (; pbVar10 != (byte *)0x0; pbVar10 = pbVar10 + -1) {
    *param_1 = *pbVar11;
    pbVar11 = pbVar11 + (uint)bVar13 * -2 + 1;
    param_1 = param_1 + (uint)bVar13 * -2 + 1;
  }
  if (local_10 != 0) {
    uVar3 = FUN_004062d4(&local_10);
  }
  goto LAB_004062fb;
}

