/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409500.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409500(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = param_2;
  do {
    iVar1 = iVar1 + -1;
    puVar2 = (undefined4 *)&stack0xfffffff4;
  } while (-1 < iVar1);
  if (-1 < param_2) {
    iVar1 = param_2 + 1;
    do {
      FUN_00409438((undefined **)*puVar2);
      puVar2 = puVar2 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return;
}

