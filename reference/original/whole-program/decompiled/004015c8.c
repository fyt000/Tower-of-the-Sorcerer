/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004015c8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004015c8(LPVOID param_1,int param_2,LPVOID *param_3)

{
  int **ppiVar1;
  LPVOID lpAddress;
  BOOL BVar2;
  int **ppiVar3;
  LPVOID local_1c;
  uint local_18;
  
  local_1c = (LPVOID)0xffffffff;
  local_18 = 0;
  ppiVar1 = (int **)DAT_0048a440;
  while (ppiVar3 = ppiVar1, ppiVar3 != &DAT_0048a440) {
    ppiVar1 = (int **)*ppiVar3;
    lpAddress = ppiVar3[2];
    if ((param_1 <= lpAddress) &&
       ((uint)((int)lpAddress + (int)ppiVar3[3]) <= (uint)(param_2 + (int)param_1))) {
      if (lpAddress < local_1c) {
        local_1c = lpAddress;
      }
      if (local_18 < (uint)((int)lpAddress + (int)ppiVar3[3])) {
        local_18 = (int)lpAddress + (int)ppiVar3[3];
      }
      BVar2 = VirtualFree(lpAddress,0,0x8000);
      if (BVar2 == 0) {
        DAT_0048a41c = 1;
      }
      FUN_004013d0((int *)ppiVar3);
    }
  }
  *param_3 = (LPVOID)0x0;
  if (local_18 != 0) {
    *param_3 = local_1c;
    param_3[1] = (LPVOID)(local_18 - (int)local_1c);
  }
  return;
}

