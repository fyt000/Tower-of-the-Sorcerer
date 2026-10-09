/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422704.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422704(int **param_1,byte param_2)

{
  int **ppiVar1;
  undefined4 extraout_ECX;
  
  *(byte *)((int)param_1 + 0x119) = param_2;
  if (param_1[0x57] != (int *)0x0) {
    FUN_00413cb8(param_1[0x57],0xb02b,(uint)param_2,0);
  }
  if (param_2 != 0) {
    if ((param_1[0x43] == (int *)0x0) && ((*(byte *)(param_1 + 7) & 0x10) == 0)) {
      ppiVar1 = (int **)root_00416f68(param_1,0,1,0,1);
      FUN_004223a4(param_1,ppiVar1,extraout_ECX);
    }
    FUN_004227b8((int *)param_1,'\x01');
    FUN_004226b4((int *)param_1);
  }
  return;
}

