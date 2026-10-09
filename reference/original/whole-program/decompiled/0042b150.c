/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042b150.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042b150(int *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 extraout_ECX;
  
  iVar2 = *(int *)(param_2 + 8);
  bVar1 = *(byte *)(iVar2 + 0x10);
  FUN_0041a9d0((int *)param_1[0x42],*(int *)(iVar2 + 0x18));
  FUN_0041a8bc(param_1[0x42]);
  FUN_0041a8d4(param_1[0x42]);
  if ((-1 < *(int *)(iVar2 + 8)) && ((bVar1 & 1) != 0)) {
    FUN_0041a154(*(int **)(param_1[0x42] + 0x14),0x8000000d);
    FUN_00419c7c(*(int **)(param_1[0x42] + 0xc),-0x7ffffff2,extraout_ECX);
  }
  if (*(int *)(iVar2 + 8) < 0) {
    FUN_0041a664((int *)param_1[0x42],(RECT *)(iVar2 + 0x1c));
  }
  else {
    (**(code **)(*param_1 + 0x84))(param_1,*(int *)(iVar2 + 8),iVar2 + 0x1c,bVar1);
  }
  if ((bVar1 & 0x10) != 0) {
    DrawFocusRect(*(HDC *)(iVar2 + 0x18),(RECT *)(iVar2 + 0x1c));
  }
  FUN_0041a9d0((int *)param_1[0x42],0);
  return;
}

