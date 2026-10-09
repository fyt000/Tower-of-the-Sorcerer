/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ff20.
 * Inferred types, shared tails and runtime effects require assembly review. */

byte FUN_0041ff20(uint param_1)

{
  SHORT SVar1;
  byte bVar2;
  
  bVar2 = DAT_0041ff58;
  SVar1 = GetKeyState(0x10);
  if (SVar1 < 0) {
    bVar2 = bVar2 | 1;
  }
  SVar1 = GetKeyState(0x11);
  if (SVar1 < 0) {
    bVar2 = bVar2 | 4;
  }
  if ((param_1 & 0x20000000) != 0) {
    bVar2 = bVar2 | 2;
  }
  return bVar2;
}

