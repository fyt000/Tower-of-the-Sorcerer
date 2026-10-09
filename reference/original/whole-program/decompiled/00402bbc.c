/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402bbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00402bbc(int param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  byte bVar5;
  
  bVar5 = 0;
  piVar1 = (int *)FUN_00402650(*(int *)(param_1 + -0x18));
  *piVar1 = param_1;
  uVar3 = *(uint *)(param_1 + -0x18);
  uVar2 = uVar3 >> 2;
  piVar4 = piVar1 + (uint)bVar5 * -2 + 1;
  while (uVar2 = uVar2 - 1, uVar2 != 0) {
    *piVar4 = 0;
    piVar4 = piVar4 + (uint)bVar5 * -2 + 1;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined *)piVar4 = 0;
    piVar4 = (int *)((int)piVar4 + (uint)bVar5 * -2 + 1);
  }
  return piVar1;
}

