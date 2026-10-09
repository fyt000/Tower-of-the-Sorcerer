/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417b60.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417b60(int *param_1,int param_2,int *param_3,int *param_4)

{
  bool bVar1;
  HBITMAP hbmMask;
  HBITMAP hbmImage;
  HIMAGELIST himl;
  BOOL BVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar4;
  
  bVar1 = FUN_00417800((int)param_1);
  uVar3 = extraout_ECX;
  uVar4 = extraout_EDX;
  if (bVar1) {
    hbmMask = (HBITMAP)FUN_00417994((int)param_1,param_4);
    hbmImage = (HBITMAP)FUN_00417994((int)param_1,param_3);
    himl = (HIMAGELIST)FUN_00417984(param_1);
    BVar2 = ImageList_Replace(himl,param_2,hbmImage,hbmMask);
    uVar3 = extraout_ECX_00;
    uVar4 = extraout_EDX_00;
    if (BVar2 == 0) {
      uVar3 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xf028);
      FUN_004031f8(uVar3);
      uVar3 = extraout_ECX_01;
      uVar4 = extraout_EDX_01;
    }
  }
  FUN_00402cdc(param_1,uVar4,uVar3);
  return;
}

