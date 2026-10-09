/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004066ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_004066ec(uint param_1,ushort param_2,ushort param_3,double *param_4)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined local_7;
  
  local_7 = 0;
  puVar1 = FUN_004066d4(param_1);
  if (((((ushort)param_1 != 0) && ((ushort)param_1 < 10000)) && (param_2 != 0)) &&
     (((param_2 < 0xd && (param_3 != 0)) &&
      (param_3 <= *(ushort *)(puVar1 + (uint)param_2 * 2 + -2))))) {
    iVar2 = param_2 - 1;
    if (0 < iVar2) {
      iVar3 = 1;
      do {
        param_3 = param_3 + *(short *)(puVar1 + iVar3 * 2 + -2);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar3 = (param_1 & 0xffff) - 1;
    iVar2 = iVar3;
    if (iVar3 < 0) {
      iVar2 = (param_1 & 0xffff) + 2;
    }
    *param_4 = (double)(((iVar3 * 0x16d + (iVar2 >> 2)) - iVar3 / 100) + iVar3 / 400 + (uint)param_3
                       + -0xa955a);
    local_7 = 1;
  }
  return local_7;
}

