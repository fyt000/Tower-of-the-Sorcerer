/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402c40.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00402c40(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  
  *param_2 = param_1;
  uVar2 = *(uint *)(param_1 + -0x18);
  uVar1 = uVar2 >> 2;
  piVar3 = param_2 + 1;
  while (uVar1 = uVar1 - 1, uVar1 != 0) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined *)piVar3 = 0;
    piVar3 = (int *)((int)piVar3 + 1);
  }
  return param_2;
}

