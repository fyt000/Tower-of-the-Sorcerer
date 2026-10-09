/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fecc.
 * Inferred types, shared tails and runtime effects require assembly review. */

byte FUN_0041fecc(uint param_1)

{
  SHORT SVar1;
  byte bVar2;
  
  bVar2 = DAT_0041ff1c;
  if ((param_1 & 4) != 0) {
    bVar2 = DAT_0041ff1c | 1;
  }
  if ((param_1 & 8) != 0) {
    bVar2 = bVar2 | 4;
  }
  if ((param_1 & 1) != 0) {
    bVar2 = bVar2 | 8;
  }
  if ((param_1 & 2) != 0) {
    bVar2 = bVar2 | 0x10;
  }
  if ((param_1 & 0x10) != 0) {
    bVar2 = bVar2 | 0x20;
  }
  SVar1 = GetKeyState(0x12);
  if (SVar1 < 0) {
    bVar2 = bVar2 | 2;
  }
  return bVar2;
}

