/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004301b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004301b8(int param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = 0;
  do {
    bVar2 = 0;
    do {
      FUN_00402c34(*(int **)(param_1 + (uint)bVar1 * 0x10 + 0x108 + (uint)bVar2 * 4));
      bVar2 = bVar2 + 1;
    } while (bVar2 != 3);
    bVar1 = bVar1 + 1;
  } while (bVar1 != 9);
  return;
}

