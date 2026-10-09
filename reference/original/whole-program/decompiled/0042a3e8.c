/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a3e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a3e8(int **param_1,undefined param_2)

{
  bool bVar1;
  int **ppiVar2;
  
  *(undefined *)(param_1 + 0x41) = param_2;
  bVar1 = FUN_00416e54((int)param_1);
  if (bVar1) {
    ppiVar2 = FUN_0041fffc(param_1);
    FUN_00413cb8((int *)ppiVar2,0xb007,0,ppiVar2[0x43]);
  }
  return;
}

