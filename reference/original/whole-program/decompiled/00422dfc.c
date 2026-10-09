/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422dfc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422dfc(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x11a) != '\x02') || ((*(byte *)(param_1 + 0x1c) & 0x10) != 0)) {
    root_00422704(param_1,*(short *)(param_2 + 4) != 0);
  }
  return;
}

