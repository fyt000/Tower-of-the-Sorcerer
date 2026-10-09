/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e384.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e384(int param_1)

{
  if (*(HICON *)(param_1 + 0xc) != (HICON)0x0) {
    DestroyIcon(*(HICON *)(param_1 + 0xc));
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}

