/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413794.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413794(int **param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  if (param_1[8] != (int *)0x0) {
    iVar2 = FUN_00409a88(param_1[8][0x2c],(int)param_1);
    if (-1 < iVar2) {
      iVar1 = ((undefined4 *)param_1[8][0x2c])[2];
      if (param_2 < 0) {
        param_2 = 0;
      }
      if (iVar1 <= param_2) {
        param_2 = iVar1 + -1;
      }
      if (iVar2 != param_2) {
        FUN_004099e4((undefined4 *)param_1[8][0x2c],iVar2);
        FUN_00409aa8((int *)param_1[8][0x2c],param_2,param_1);
        FUN_00413924((int)param_1,*(char *)((int)param_1 + 0x37),'\x01');
        piVar3 = (int *)FUN_00420024(param_1);
        if ((*(byte *)((int)piVar3 + 0x36) & 4) != 0) {
          FUN_00402cdc(piVar3,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
        }
      }
    }
  }
  return;
}

