/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; runtime boundary 0042c454. */

void FUN_0042c454(int param_1,char param_2)

{
  if (param_2 != *(char *)(param_1 + 0x20)) {
    *(char *)(param_1 + 0x20) = param_2;
    FUN_0042c404(param_1);
  }
  return;
}

