/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419fd0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00419fd0(int param_1)

{
  int iVar1;
  HPEN pHVar2;
  LOGPEN local_14;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if (*(int *)(iVar1 + 8) == 0) {
    local_14.lopnStyle = (UINT)*(ushort *)(&DAT_004894d8 + (uint)*(byte *)(iVar1 + 0x1c) * 2);
    local_14.lopnWidth.x = *(LONG *)(iVar1 + 0x18);
    local_14.lopnColor = FUN_00419b00(*(uint *)(iVar1 + 0x14));
    pHVar2 = CreatePenIndirect(&local_14);
    *(HPEN *)(iVar1 + 8) = pHVar2;
  }
  return *(undefined4 *)(iVar1 + 8);
}

