/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423fbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423fbc(HWND param_1,int param_2)

{
  bool bVar1;
  BOOL BVar2;
  
  bVar1 = FUN_00423f68();
  if (bVar1) {
    FUN_00423f98(0);
  }
  BVar2 = ShowWindow(param_1,param_2);
  if (bVar1) {
    FUN_00423f98(CONCAT31((int3)((uint)BVar2 >> 8),1));
  }
  return;
}

