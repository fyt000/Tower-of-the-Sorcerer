/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004178f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004178f4(int *param_1,int param_2)

{
  bool bVar1;
  HIMAGELIST himl;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int cx;
  int cy;
  
  if (param_2 != param_1[9]) {
    param_1[9] = param_2;
    bVar1 = FUN_00417800((int)param_1);
    if (bVar1) {
      cy = param_1[8];
      cx = param_1[9];
      himl = (HIMAGELIST)FUN_00417984(param_1);
      ImageList_SetIconSize(himl,cx,cy);
    }
    FUN_00417dc4(param_1);
    FUN_00417814((int)param_1);
    FUN_00402cdc(param_1,extraout_EDX,extraout_ECX);
  }
  return;
}

