/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406498.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406498(uint param_1)

{
  uint uVar1;
  ulonglong uVar2;
  uint uVar3;
  byte bVar4;
  int iVar6;
  int unaff_EBP;
  byte *pbVar7;
  char cVar5;
  
  pbVar7 = (byte *)(unaff_EBP + -0x38);
  do {
    uVar2 = (ulonglong)param_1;
    param_1 = param_1 / 10;
    cVar5 = (char)(uVar2 % 10);
    bVar4 = cVar5 + 0x30;
    if (0x39 < bVar4) {
      bVar4 = cVar5 + 0x37;
    }
    pbVar7 = pbVar7 + -1;
    *pbVar7 = bVar4;
  } while (param_1 != 0);
  uVar3 = (unaff_EBP + -0x38) - (int)pbVar7;
  uVar1 = *(uint *)(unaff_EBP + -0x1c);
  if (uVar1 < 0x10) {
    iVar6 = uVar1 - uVar3;
    if (uVar3 <= uVar1 && iVar6 != 0) {
      do {
        pbVar7 = pbVar7 + -1;
        *pbVar7 = 0x30;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    return;
  }
  return;
}

