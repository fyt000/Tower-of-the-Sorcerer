/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420e98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00420e98(int *param_1,int **param_2,undefined4 param_3)

{
  int *piVar1;
  char cVar2;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  
  cVar2 = (char)param_3;
  FUN_00412f9c((int)param_1,(int)param_2,cVar2);
  if (cVar2 == '\0') {
    if (((((*(byte *)(param_1 + 7) & 1) == 0) && (param_1[0x4a] == 0)) && (param_1 == param_2[1]))
       && (piVar1 = FUN_00402c7c(param_2,(int *)&PTR_FUN_0040f538), (char)piVar1 != '\0')) {
      FUN_00421bfc(param_1,(int *)param_2,extraout_ECX_00);
    }
  }
  else if (cVar2 == '\x01') {
    uVar3 = extraout_ECX;
    if (param_2 == (int **)param_1[0x4a]) {
      FUN_00421bfc(param_1,(int *)0x0,extraout_ECX);
      uVar3 = extraout_ECX_01;
    }
    if (param_2 == (int **)param_1[0x4e]) {
      FUN_00421bd4(param_1,0,uVar3);
    }
  }
  piVar1 = (int *)param_1[0x4c];
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1,param_2,param_3);
  }
  return;
}

