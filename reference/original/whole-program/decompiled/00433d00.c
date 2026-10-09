/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433d00.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_00433d00(int param_1)

{
  byte bVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 0x115) != '\0') {
    bVar1 = *(byte *)(param_1 + 0x115);
    if ((bVar1 == 1) || (bVar1 == 4)) {
      cVar2 = '\x01';
    }
    else {
      cVar2 = '\0';
    }
    if (cVar2 == *(char *)(param_1 + 0x104)) {
      if ((bVar1 == 2) || (bVar1 == 5)) {
        cVar2 = '\x01';
      }
      else {
        cVar2 = '\0';
      }
      if (((cVar2 == *(char *)(param_1 + 0x105)) &&
          (*(int *)(&DAT_004898a8 + (bVar1 & 0x7f) * 4) == *(int *)(param_1 + 0x108))) &&
         (*(char *)(param_1 + 0x121) == '\0')) goto LAB_00433d65;
    }
    *(undefined *)(param_1 + 0x115) = 0;
  }
LAB_00433d65:
  return *(undefined *)(param_1 + 0x115);
}

