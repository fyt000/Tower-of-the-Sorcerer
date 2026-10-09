/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418394.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00418394(int param_1,int param_2,int param_3)

{
  bool bVar1;
  BOOL BVar2;
  int local_14;
  int local_10;
  
  bVar1 = FUN_00417800(param_1);
  if (bVar1) {
    FUN_0041765c(*(HWND *)(param_1 + 0x40),param_2,param_3,&local_14);
    BVar2 = ImageList_DragMove(local_14,local_10);
    bVar1 = BVar2 != 0;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

