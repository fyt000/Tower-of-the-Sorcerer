/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00417d74.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00417d74(int *param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  HIMAGELIST himl;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar4;
  
  iVar2 = FUN_00417b3c(param_1);
  if (iVar2 <= param_2) {
    uVar3 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf029);
    FUN_004031f8(uVar3);
  }
  bVar1 = FUN_00417800((int)param_1);
  uVar3 = extraout_ECX;
  uVar4 = extraout_EDX_00;
  if (bVar1) {
    himl = (HIMAGELIST)FUN_00417984(param_1);
    ImageList_Remove(himl,param_2);
    uVar3 = extraout_ECX_00;
    uVar4 = extraout_EDX_01;
  }
  FUN_00402cdc(param_1,uVar4,uVar3);
  return;
}

