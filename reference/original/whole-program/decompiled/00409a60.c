/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409a60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00409a60(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1[3];
  if (iVar1 < 9) {
    if (iVar1 < 5) {
      iVar2 = 4;
    }
    else {
      iVar2 = 8;
    }
  }
  else {
    iVar2 = 0x10;
  }
  FUN_00409b4c(param_1,iVar2 + iVar1);
  return;
}

