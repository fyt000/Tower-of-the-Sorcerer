/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004162ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004162ec(int **param_1)

{
  if ((*(char *)((int)param_1 + 0x37) == '\0') && (param_1[8] != (int *)0x0)) {
    FUN_00414ae4(param_1,'\0');
  }
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) || ((*(byte *)((int)param_1 + 0x35) & 4) != 0)) {
    FUN_004152ac(param_1);
  }
  return;
}

