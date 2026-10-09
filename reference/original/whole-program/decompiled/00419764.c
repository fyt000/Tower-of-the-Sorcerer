/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419764.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00419764(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_0048a6f4[2];
  if (-1 < iVar2 + -1) {
    iVar3 = 0;
    do {
      iVar1 = FUN_00409a40(DAT_0048a6f4,iVar3);
      FUN_0041a970(iVar1);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  root_00419738(*(undefined4 *)(DAT_0048a6ec + 4));
  root_00419738(*(undefined4 *)(DAT_0048a6f0 + 4));
  return;
}

