/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414018.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414018(int **param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  int **ppiVar3;
  int iStack_1c;
  undefined4 uStack_18;
  int aiStack_14 [2];
  
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) &&
     (uVar2 = param_2, ppiVar3 = param_1, param_1 != (int **)0x0)) {
    do {
      piVar1 = (int *)FUN_00402cdc((int *)ppiVar3,uVar2,param_3);
      if ((piVar1 != (int *)0x0) && (*(char *)((int)piVar1 + 0x2d) != '\0')) {
        FUN_004132a4(param_1,0);
        piVar1[0xc] = (int)ppiVar3;
        FUN_004052e0(param_2,aiStack_14);
        FUN_0041324c((int *)param_1,aiStack_14,&iStack_1c);
        (**(code **)(*piVar1 + 0x30))(piVar1,iStack_1c,uStack_18);
        return;
      }
      ppiVar3 = (int **)ppiVar3[8];
      param_3 = extraout_ECX;
      uVar2 = extraout_EDX;
    } while (ppiVar3 != (int **)0x0);
  }
  return;
}

