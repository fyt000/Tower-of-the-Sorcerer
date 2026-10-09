/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421e58.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421e58(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  FUN_00416428((int)param_1,param_2);
  if (*(char *)((int)param_1 + 0xc5) == '\0') {
    if (param_1[0x12] == -0x7ffffff1) {
      iVar1 = root_00421e40(param_1);
      FUN_004136e8(param_1,iVar1);
    }
  }
  else {
    iVar1 = root_00421e40(param_1);
    if (iVar1 == param_1[0x12]) {
      FUN_004136e8(param_1,-0x7ffffff1);
      return;
    }
  }
  return;
}

