/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417814.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417814(int param_1)

{
  HBITMAP pHVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  undefined4 *in_FS_OFFSET;
  RECT *pRVar6;
  undefined4 uVar7;
  RECT local_18;
  HDC local_8;
  
  local_8 = GetDC((HWND)0x0);
  uVar7 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffd4;
  piVar5 = *(int **)(param_1 + 0x48);
  pHVar1 = CreateCompatibleBitmap(local_8,*(int *)(param_1 + 0x24),*(int *)(param_1 + 0x20));
  FUN_0041e0ec((int)piVar5,pHVar1);
  iVar2 = FUN_0041dad8((int)piVar5);
  FUN_0041a154(*(int **)(iVar2 + 0x14),0);
  uVar3 = (**(code **)(*piVar5 + 0x1c))();
  pRVar6 = &local_18;
  uVar4 = (**(code **)(*piVar5 + 0x20))();
  FUN_0040923c(0,0,uVar4,&pRVar6->left,uVar3);
  pRVar6 = &local_18;
  piVar5 = (int *)FUN_0041dad8((int)piVar5);
  FUN_0041a664(piVar5,pRVar6);
  *in_FS_OFFSET = uVar7;
  ReleaseDC((HWND)0x0,local_8);
  return;
}

