/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041830c.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_0041830c(int param_1,HWND param_2,int param_3,int param_4)

{
  bool bVar1;
  BOOL BVar2;
  bool bVar3;
  int local_10;
  int local_c;
  int local_8;
  
  bVar3 = false;
  local_8 = param_3;
  bVar1 = FUN_00417800(param_1);
  if ((bVar1) && (param_2 != *(HWND *)(param_1 + 0x40))) {
    FUN_00418370(param_1);
    *(HWND *)(param_1 + 0x40) = param_2;
    FUN_0041765c(param_2,local_8,param_4,&local_10);
    BVar2 = ImageList_DragEnter(*(HWND *)(param_1 + 0x40),local_10,local_c);
    bVar3 = BVar2 != 0;
  }
  return bVar3;
}

