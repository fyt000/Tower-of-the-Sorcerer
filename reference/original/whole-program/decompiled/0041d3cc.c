/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041d3cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041d3cc(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    FUN_0041d22c(*(int *)(param_1 + 0xc));
    DeleteObject(*(HGDIOBJ *)(param_1 + 0xc));
  }
  if (*(HGDIOBJ *)(param_1 + 0x10) != (HGDIOBJ)0x0) {
    DeleteObject(*(HGDIOBJ *)(param_1 + 0x10));
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}

