/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004142f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004142f0(int param_1)

{
  char cVar1;
  
  if (((*(byte *)(param_1 + 0x1c) & 0x10) == 0) || ((*(byte *)(param_1 + 0x35) & 4) != 0)) {
    if ((*(char *)(param_1 + 0x37) == '\0') || ((*(byte *)(param_1 + 0x34) & 0x40) == 0)) {
      cVar1 = '\0';
    }
    else {
      cVar1 = '\x01';
    }
    FUN_00413924(param_1,'\x01',cVar1);
  }
  return;
}

