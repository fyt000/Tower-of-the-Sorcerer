/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00432b48.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00432b48(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    uVar1 = *(uint *)(param_1 + 0xc + (uVar2 & 0x7f) * 4);
    if (uVar1 != 0xffffffff) {
      FUN_00432948(*(int *)(param_1 + 8),uVar1);
    }
    *(undefined4 *)(param_1 + 0xc + (uVar2 & 0x7f) * 4) = 0xffffffff;
    uVar2 = uVar2 + 1;
  } while ((char)uVar2 != '\x04');
  FUN_00432a38(DAT_004898d4,*(int **)(param_1 + 8));
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

