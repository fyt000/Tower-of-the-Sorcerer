/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419738.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00419738(int *param_1)

{
  if (param_1 != (int *)0x0) {
    do {
      if (((HGDIOBJ)param_1[2] != (HGDIOBJ)0x0) && (param_1[5] < 0)) {
        DeleteObject((HGDIOBJ)param_1[2]);
        param_1[2] = 0;
      }
      param_1 = (int *)*param_1;
    } while (param_1 != (int *)0x0);
  }
  return;
}

