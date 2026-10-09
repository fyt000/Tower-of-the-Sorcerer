/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042548c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042548c(int param_1,UINT param_2,undefined param_3)

{
  UINT_PTR UVar1;
  
  FUN_004254d0(param_1);
  UVar1 = SetTimer((HWND)0x0,1,param_2,FUN_00423e24);
  *(short *)(param_1 + 0x68) = (short)UVar1;
  *(bool *)(param_1 + 0x65) = (short)UVar1 != 0;
  *(undefined *)(param_1 + 0x66) = param_3;
  if (*(char *)(param_1 + 0x65) == '\0') {
    FUN_00425618(param_1);
  }
  return;
}

