/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421dec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421dec(int param_1,char param_2)

{
  char cVar1;
  
  cVar1 = root_00421de0(param_1);
  if ((param_2 != cVar1) && (*(undefined4 *)(param_1 + 0x13c) = 0, param_2 != '\0')) {
    *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(DAT_0048a6fc + 0x24);
  }
  return;
}

