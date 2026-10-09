/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a98c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int root_0042a98c(int *param_1)

{
  bool bVar1;
  int iVar2;
  undefined auStack_18 [4];
  int iStack_14;
  int iStack_c;
  
  iVar2 = param_1[0x44];
  bVar1 = FUN_00416e54((int)param_1);
  if ((bVar1) && (*(char *)(param_1 + 0x45) == '\0')) {
    FUN_00413cb8(param_1,0x198,0,auStack_18);
    iVar2 = iStack_c - iStack_14;
  }
  return iVar2;
}

