/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420f20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00420f20(int **param_1,int param_2)

{
  bool bVar1;
  int nNumber;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  
  puStack_14 = (undefined *)0x420f33;
  FUN_00414aa0((int)param_1);
  puStack_18 = &LAB_004210f2;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  param_1[0x52] = (int *)0x0;
  param_1[0x53] = (int *)0x0;
  param_1[0x54] = (int *)0x0;
  bVar1 = false;
  puStack_14 = &stack0xfffffffc;
  FUN_004145b0(param_1,param_2);
  if ((param_1[0x4f] != (int *)0x0) && (0 < (int)param_1[0x54])) {
    if (((*(byte *)(param_1 + 0x17) & 0x10) != 0) &&
       (*(int **)(DAT_0048a6fc + 0x24) != param_1[0x4f])) {
      piVar3 = param_1[0x4f];
      iVar2 = *(int *)(DAT_0048a6fc + 0x24);
      piVar4 = param_1[0x11];
      nNumber = FUN_00419da4((int)piVar4);
      iVar2 = MulDiv(nNumber,iVar2,(int)piVar3);
      FUN_00419dac(piVar4,iVar2);
    }
    param_1[0x4f] = *(int **)(DAT_0048a6fc + 0x24);
    piVar3 = (int *)FUN_004211d0((int)param_1);
    if (piVar3 != param_1[0x54]) {
      bVar1 = true;
      FUN_004209e8((int)param_1,(int)piVar3,(int)param_1[0x54]);
      FUN_0041687c((int)param_1,piVar3,param_1[0x54]);
      if ((*(byte *)(param_1 + 0x17) & 4) != 0) {
        piVar4 = (int *)MulDiv((int)param_1[0x52],(int)piVar3,(int)param_1[0x54]);
        param_1[0x52] = piVar4;
      }
      if ((*(byte *)(param_1 + 0x17) & 8) != 0) {
        piVar3 = (int *)MulDiv((int)param_1[0x53],(int)piVar3,(int)param_1[0x54]);
        param_1[0x53] = piVar3;
      }
    }
  }
  if (0 < (int)param_1[0x52]) {
    FUN_00413190((int *)param_1,param_1[0x52]);
  }
  if (0 < (int)param_1[0x53]) {
    FUN_004131d4((int *)param_1,param_1[0x53]);
  }
  *(undefined *)(param_1 + 0x17) = DAT_00421100;
  if (!bVar1) {
    FUN_004209e8((int)param_1,1,1);
    FUN_0041687c((int)param_1,1,1);
  }
  *in_FS_OFFSET = uStack_1c;
  puStack_14 = &LAB_004210f9;
  puStack_18 = (undefined *)0x4210f1;
  FUN_00414aa8((int)param_1);
  return;
}

