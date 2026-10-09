/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e04c.
 * Inferred types, shared tails and runtime effects require assembly review. */

byte FUN_0042e04c(int param_1)

{
  byte bVar1;
  undefined4 auStack_44 [2];
  uint local_3c;
  
  bVar1 = DAT_0042e098;
  FUN_0042de88(param_1,auStack_44);
  if ((local_3c & 1) != 0) {
    bVar1 = bVar1 | 1;
  }
  if ((local_3c & 2) != 0) {
    bVar1 = bVar1 | 2;
  }
  if ((local_3c & 4) != 0) {
    bVar1 = bVar1 | 4;
  }
  if ((local_3c & 8) != 0) {
    bVar1 = bVar1 | 8;
  }
  return bVar1;
}

