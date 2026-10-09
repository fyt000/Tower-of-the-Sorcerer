/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a188.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041a188(int param_1)

{
  byte bVar1;
  int iVar2;
  HBRUSH pHVar3;
  LOGBRUSH local_14;
  
  iVar2 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar2 + 8) == 0) {
    if (*(int **)(iVar2 + 0x18) == (int *)0x0) {
      local_14.lbHatch = 0;
      bVar1 = *(byte *)(iVar2 + 0x1c);
      if (bVar1 == 0) {
        local_14.lbStyle = 0;
      }
      else if (bVar1 == 1) {
        local_14.lbStyle = 1;
      }
      else {
        local_14.lbStyle = 2;
        local_14.lbHatch = (bVar1 & 0x7f) - 2;
      }
    }
    else {
      local_14.lbStyle = 3;
      local_14.lbHatch = (**(code **)(**(int **)(iVar2 + 0x18) + 0x4c))();
    }
    local_14.lbColor = FUN_00419b00(*(uint *)(iVar2 + 0x14));
    pHVar3 = CreateBrushIndirect(&local_14);
    *(HBRUSH *)(iVar2 + 8) = pHVar3;
  }
  return *(undefined4 *)(iVar2 + 8);
}

