/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409d00.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_00409d00(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  int local_10;
  
  local_10 = *(int *)(param_1 + 4) + 0x1f;
  if (local_10 < 0) {
    local_10 = *(int *)(param_1 + 4) + 0x3e;
  }
  local_10 = local_10 >> 5;
  if (-1 < local_10 + -1) {
    iVar2 = 0;
    do {
      if (DAT_00409d74 != *(int *)(*(int *)(param_1 + 8) + iVar2 * 4)) {
        uVar1 = 0;
        do {
          bVar3 = (byte)uVar1 < 0x1f;
          if ((byte)uVar1 < 0x20) {
            bVar3 = (*(uint *)(*(int *)(param_1 + 8) + iVar2 * 4) >> (uVar1 & 0x1f) & 1) != 0;
          }
          if (!bVar3) {
            iVar2 = iVar2 * 0x20 + (uVar1 & 0x7f);
            if (iVar2 < *(int *)(param_1 + 4)) {
              return iVar2;
            }
            return *(int *)(param_1 + 4);
          }
          uVar1 = uVar1 + 1;
        } while ((char)uVar1 != ' ');
      }
      iVar2 = iVar2 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  return *(int *)(param_1 + 4);
}

