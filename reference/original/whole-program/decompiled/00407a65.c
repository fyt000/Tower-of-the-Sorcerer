/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00407a65.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00407a65(void)

{
  char cVar1;
  int iVar2;
  int extraout_ECX;
  uint uVar3;
  uint extraout_EDX;
  int extraout_EDX_00;
  int iVar4;
  int unaff_EBP;
  char *unaff_EDI;
  char *pcVar5;
  byte bVar6;
  
  bVar6 = 0;
  uVar3 = *(uint *)(unaff_EBP + 8);
  if (0x11 < uVar3) {
    uVar3 = 0x12;
  }
  iVar2 = (int)*(short *)(unaff_EBP + -0x1c);
  if (iVar2 < 1) {
    pcVar5 = unaff_EDI + 1;
    *unaff_EDI = '0';
  }
  else {
    iVar4 = 0;
    if (*(char *)(unaff_EBP + 0x10) != '\x02') {
      iVar4 = (byte)((ushort)(*(short *)(unaff_EBP + -0x1c) - 1U) % 3) + 1;
    }
    while( true ) {
      cVar1 = FUN_00407978();
      pcVar5 = unaff_EDI + (uint)bVar6 * -2 + 1;
      *unaff_EDI = cVar1;
      iVar2 = extraout_ECX + -1;
      uVar3 = extraout_EDX;
      if (iVar2 == 0) break;
      iVar4 = iVar4 + -1;
      unaff_EDI = pcVar5;
      if (iVar4 == 0) {
        unaff_EDI = pcVar5 + (uint)bVar6 * -2 + 1;
        *pcVar5 = DAT_0048a54e;
        iVar4 = 3;
      }
    }
  }
  if (uVar3 != 0) {
    *pcVar5 = DAT_0048a54f;
    pcVar5 = pcVar5 + (uint)bVar6 * -2 + 1;
    for (; iVar2 != 0; iVar2 = iVar2 + 1) {
      *pcVar5 = '0';
      uVar3 = uVar3 - 1;
      if (uVar3 == 0) {
        return;
      }
      pcVar5 = pcVar5 + (uint)bVar6 * -2 + 1;
    }
    do {
      cVar1 = FUN_00407978();
      *pcVar5 = cVar1;
      pcVar5 = pcVar5 + (uint)bVar6 * -2 + 1;
    } while (extraout_EDX_00 != 1);
  }
  return;
}

