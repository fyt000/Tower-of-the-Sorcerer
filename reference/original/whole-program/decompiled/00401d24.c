/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401d24.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00401d24(uint *param_1,int param_2)

{
  int *piVar1;
  int **ppiVar2;
  undefined4 uVar3;
  uint *puVar4;
  int *local_18;
  int local_14;
  
  ppiVar2 = (int **)FUN_00401bd0((uint)param_1);
  piVar1 = ppiVar2[2];
  if (((int)piVar1 + (int)ppiVar2[3]) - (param_2 + (int)param_1) < 0xd) {
    param_2 = ((int)piVar1 + (int)ppiVar2[3]) - (int)param_1;
  }
  if ((int)param_1 - (int)piVar1 < 0xc) {
    FUN_00401948((int)piVar1,(int)param_1 + (param_2 - (int)ppiVar2[2]),&local_18);
  }
  else {
    FUN_00401948((int)(param_1 + 1),param_2 + -4,&local_18);
  }
  if (local_18 == (int *)0x0) {
    uVar3 = 0;
  }
  else {
    FUN_00401c00(param_1,(int)local_18 - (int)param_1);
    puVar4 = (uint *)((int)local_18 + local_14);
    if (puVar4 < (uint *)((int)ppiVar2[2] + (int)ppiVar2[3])) {
      FUN_00401c54(puVar4,(int)param_1 + (param_2 - (int)puVar4));
    }
    uVar3 = FUN_0040145c(ppiVar2,&local_18);
    uVar3 = CONCAT31((int3)((uint)uVar3 >> 8),1);
  }
  return uVar3;
}

