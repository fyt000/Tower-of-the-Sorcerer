/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ab2c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ab2c(int param_1)

{
  HGDIOBJ pvVar1;
  undefined4 uVar2;
  uint uVar3;
  COLORREF color;
  
  pvVar1 = (HGDIOBJ)FUN_0041a188(*(int *)(param_1 + 0x14));
  UnrealizeObject(pvVar1);
  pvVar1 = (HGDIOBJ)FUN_0041a188(*(int *)(param_1 + 0x14));
  SelectObject(*(HDC *)(param_1 + 4),pvVar1);
  uVar2 = FUN_0041a204(*(int *)(param_1 + 0x14));
  if ((char)uVar2 == '\0') {
    uVar3 = FUN_0041a14c(*(int *)(param_1 + 0x14));
    color = FUN_00419b00(uVar3);
    SetBkColor(*(HDC *)(param_1 + 4),color);
    SetBkMode(*(HDC *)(param_1 + 4),2);
    return;
  }
  uVar3 = FUN_0041a14c(*(int *)(param_1 + 0x14));
  uVar3 = FUN_00419b00(uVar3);
  SetBkColor(*(HDC *)(param_1 + 4),~uVar3);
  SetBkMode(*(HDC *)(param_1 + 4),1);
  return;
}

