/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042194c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042194c(int **param_1,char param_2)

{
  char cVar1;
  
  if (param_2 != *(char *)((int)param_1 + 0x115)) {
    *(char *)((int)param_1 + 0x115) = param_2;
    if ((param_2 == '\x02') || (param_2 == '\x05')) {
      cVar1 = '\x01';
    }
    else {
      cVar1 = '\0';
    }
    FUN_00420730((int)param_1,cVar1);
    if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
      FUN_00415174(param_1);
    }
  }
  return;
}

