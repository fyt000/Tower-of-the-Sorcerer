/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041db60.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_0041db60(int *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  uVar1 = FUN_0041db44((int)param_1);
  if ((char)uVar1 == '\0') {
    iVar3 = (**(code **)(*param_1 + 0x1c))();
    piVar4 = (int *)FUN_0041dad8((int)param_1);
    uVar2 = FUN_0041a924(piVar4,0,iVar3 + -1);
  }
  else {
    uVar2 = 0xffffff;
  }
  return uVar2 | 0x2000000;
}

