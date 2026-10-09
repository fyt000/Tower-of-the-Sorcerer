/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401b7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401b7c(int *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if (param_1 == DAT_0048a46c) {
    DAT_0048a46c = (int *)param_1[1];
  }
  piVar1 = (int *)param_1[1];
  uVar2 = param_1[2];
  if ((int)uVar2 < 0x1001) {
    if (param_1 != piVar1) {
      *(int **)(DAT_0048a478 + -0xc + (uVar2 & 0xfffffffc)) = piVar1;
      iVar3 = *param_1;
      *piVar1 = iVar3;
      *(int **)(iVar3 + 4) = piVar1;
      return;
    }
    *(undefined4 *)(DAT_0048a478 + -0xc + (uVar2 & 0xfffffffc)) = 0;
  }
  else {
    iVar3 = *param_1;
    *piVar1 = iVar3;
    *(int **)(iVar3 + 4) = piVar1;
  }
  return;
}

