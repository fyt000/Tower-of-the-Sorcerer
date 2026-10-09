/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424c88.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00424c88(int param_1,LPMSG param_2)

{
  int iVar1;
  BOOL BVar2;
  bool bVar3;
  
  bVar3 = false;
  iVar1 = *(int *)(param_1 + 0x28);
  if ((((iVar1 != 0) && (*(char *)(iVar1 + 0x11a) == '\x02')) &&
      (*(int *)(DAT_0048a6fc + 0x40) != 0)) &&
     (*(char *)(*(int *)(DAT_0048a6fc + 0x40) + 0x11a) == '\x01')) {
    BVar2 = TranslateMDISysAccel(*(HWND *)(iVar1 + 0x134),param_2);
    bVar3 = BVar2 != 0;
  }
  return bVar3;
}

