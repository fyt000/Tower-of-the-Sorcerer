/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041aba8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041aba8(int param_1)

{
  if ((*(byte *)(param_1 + 8) & 2) != 0) {
    *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0xfd;
    SelectObject(*(HDC *)(param_1 + 4),DAT_0048a6e0);
  }
  return;
}

