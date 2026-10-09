/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430c9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430c9c(int *param_1,short *param_2)

{
  short sVar1;
  byte bVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  sVar1 = *param_2;
  if (sVar1 == 0x20) {
    if (*(char *)((int)param_1 + (uint)*(byte *)(param_1 + 0x75) * 0x10 + 0x105) != '\0') {
      *(byte *)((int)param_1 + 0x19e) = *(byte *)(param_1 + 0x75);
      root_00430b24(param_1);
      if (*(char *)(param_1 + 0x84) != '\0') {
        FUN_00402cdc(param_1,CONCAT31((int3)((uint)extraout_EDX >> 8),
                                      *(undefined *)((int)param_1 + 0x19e)),extraout_ECX);
        FUN_0043025c(param_1);
      }
    }
  }
  else if (sVar1 == 0x25) {
    bVar2 = *(byte *)(param_1 + 0x75);
    do {
      if (bVar2 != 0) {
        bVar2 = bVar2 - 1;
      }
    } while ((bVar2 != 0) && (*(char *)(param_1 + (uint)bVar2 * 4 + 0x41) == '\0'));
    if (bVar2 != *(byte *)(param_1 + 0x75)) {
      *(byte *)(param_1 + 0x75) = bVar2;
      (**(code **)(*param_1 + 0x44))();
      return;
    }
  }
  else if (sVar1 == 0x27) {
    bVar2 = *(byte *)(param_1 + 0x75);
    do {
      if (bVar2 < 8) {
        bVar2 = bVar2 + 1;
      }
    } while ((bVar2 != 8) && (*(char *)(param_1 + (uint)bVar2 * 4 + 0x41) == '\0'));
    if (bVar2 != *(byte *)(param_1 + 0x75)) {
      *(byte *)(param_1 + 0x75) = bVar2;
      (**(code **)(*param_1 + 0x44))();
      return;
    }
  }
  return;
}

