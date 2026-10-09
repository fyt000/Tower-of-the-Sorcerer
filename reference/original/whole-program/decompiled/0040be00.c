/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040be00.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0040be00(int **param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int **ppiVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  ppiVar2 = (int **)root_00407298();
  piVar3 = FUN_00402c7c(ppiVar2,(int *)&DAT_00405390);
  if ((char)piVar3 != '\0') {
    cVar1 = root_0040bde0();
    if (cVar1 != '\0') {
      FUN_00402c34(*param_1);
    }
    *param_1 = (int *)0x0;
    root_0040d0d0(*(undefined4 *)(param_4 + -0xc),0);
    iVar4 = root_00407298();
    uVar5 = (**(code **)(**(int **)(param_4 + -0xc) + 0xc))
                      (*(int **)(param_4 + -0xc),*(undefined4 *)(iVar4 + 4));
  }
  return uVar5;
}

