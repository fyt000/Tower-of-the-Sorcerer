/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040eadc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040eadc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((char)param_2 == '\0') {
    *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0xef;
  }
  else {
    *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) | 0x10;
  }
  iVar1 = FUN_0040ea78(param_1);
  if (-1 < iVar1 + -1) {
    iVar3 = 0;
    do {
      iVar2 = FUN_0040ea54(param_1,iVar3);
      FUN_0040eadc(iVar2,param_2);
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

