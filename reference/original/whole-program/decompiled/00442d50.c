/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00442d50.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_buttonfocus(int param_1)

{
  if (_DAT_0048c590 == 1) {
    if (*(char *)((int)*(int **)(param_1 + 0x450) + 0x37) == '\x01') {
      (**(code **)(**(int **)(param_1 + 0x450) + 0x80))();
      return;
    }
  }
  else if (_DAT_0048c590 == 2) {
    if (*(char *)((int)*(int **)(param_1 + 0x454) + 0x37) == '\x01') {
      (**(code **)(**(int **)(param_1 + 0x454) + 0x80))();
      return;
    }
  }
  else if (_DAT_0048c590 == 3) {
    if (*(char *)((int)*(int **)(param_1 + 0x458) + 0x37) == '\x01') {
      (**(code **)(**(int **)(param_1 + 0x458) + 0x80))();
      return;
    }
  }
  else if ((_DAT_0048c590 == 4) && (*(char *)((int)*(int **)(param_1 + 0x45c) + 0x37) == '\x01')) {
    (**(code **)(**(int **)(param_1 + 0x45c) + 0x80))();
  }
  return;
}

