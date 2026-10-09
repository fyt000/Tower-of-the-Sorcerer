/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c848.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040c848(int *param_1,int *param_2,char **param_3)

{
  undefined *puVar1;
  byte bVar2;
  char cVar3;
  char *pcVar4;
  int *piVar5;
  undefined extraout_CL;
  char **extraout_ECX;
  char **ppcVar6;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  int *extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 *in_FS_OFFSET;
  undefined1 in_ST0 [10];
  undefined *puVar7;
  undefined4 uStack_30;
  code *pcStack_2c;
  undefined *puStack_28;
  undefined4 *puStack_18;
  int iStack_14;
  int iStack_10;
  int *piStack_c;
  int *piStack_8;
  
  puStack_28 = &stack0xfffffffc;
  puVar7 = &stack0xfffffffc;
  puStack_18 = (undefined4 *)0x0;
  pcStack_2c = thunk_FUN_00403140;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  ppcVar6 = param_3;
  puVar1 = &stack0xfffffffc;
  piStack_c = param_2;
  piStack_8 = param_1;
  if (param_3[2] == (char *)0x0) {
    FUN_0040b8c8(0xf018,param_2);
    ppcVar6 = extraout_ECX;
    param_2 = extraout_EDX;
    puVar1 = puStack_28;
  }
  puStack_28 = puVar1;
  pcVar4 = *param_3;
  switch(*pcVar4) {
  case '\x01':
    cVar3 = FUN_0040bbec((int)piStack_8,param_2,(uint)ppcVar6);
    if (cVar3 == '\a') {
      FUN_0040c2ac((int)piStack_8,(int *)&puStack_18,extraout_ECX_00);
      FUN_0040c6f4(piStack_c,param_3,puStack_18);
    }
    else {
      pcVar4 = (char *)FUN_0040c360((int)piStack_8,extraout_EDX_00,extraout_ECX_00);
      FUN_0040838c(piStack_c,param_3,pcVar4);
    }
    break;
  case '\x02':
    bVar2 = FUN_0040bca0((int)piStack_8,param_2,(uint)ppcVar6);
    FUN_0040838c(piStack_c,param_3,(char *)(uint)bVar2);
    break;
  case '\x03':
    FUN_0040c2ac((int)piStack_8,(int *)&puStack_18,(uint)ppcVar6);
    pcVar4 = (char *)FUN_0040b8f8((int)pcVar4,(int)puStack_18);
    FUN_0040838c(piStack_c,param_3,pcVar4);
    break;
  case '\x04':
    FUN_0040c26c((int)piStack_8,param_2,(uint)ppcVar6);
    FUN_004085f0(piStack_c,(int *)param_3,extraout_CL,in_ST0);
    break;
  case '\x05':
  case '\n':
    FUN_0040ce30((int)piStack_8,(int *)&puStack_18,(uint)ppcVar6);
    FUN_00408548(piStack_c,param_3,puStack_18);
    break;
  case '\x06':
    pcVar4 = (char *)FUN_0040cd18((int)piStack_8,(int)pcVar4);
    FUN_0040838c(piStack_c,param_3,pcVar4);
    break;
  case '\a':
    cVar3 = FUN_0040bbec((int)piStack_8,param_2,(uint)ppcVar6);
    if (cVar3 == '\r') {
      FUN_0040ce90((int)piStack_8,extraout_EDX_01,extraout_ECX_01);
      FUN_0040838c(piStack_c,param_3,(char *)0x0);
    }
    else if (cVar3 == '\x0e') {
      FUN_0040ce90((int)piStack_8,extraout_EDX_01,extraout_ECX_01);
      piVar5 = (int *)FUN_0040831c(piStack_c,param_3);
      FUN_0040bd28((int)piStack_8,piVar5);
    }
    else {
      FUN_0040c2ac((int)piStack_8,(int *)&puStack_18,extraout_ECX_01);
      FUN_0040c75c(piStack_c,param_3,(char *)puStack_18,(int)puVar7);
    }
    break;
  case '\b':
    cVar3 = FUN_0040bbec((int)piStack_8,param_2,(uint)ppcVar6);
    if (cVar3 == '\r') {
      FUN_0040ce90((int)piStack_8,extraout_EDX_02,extraout_ECX_02);
      FUN_004086c8(piStack_c,(int)param_3,(undefined4 *)&DAT_004891cc);
    }
    else {
      FUN_0040c2ac((int)piStack_8,(int *)&puStack_18,extraout_ECX_02);
      iStack_14 = (**(code **)(*piStack_8 + 0x10))(piStack_8,piStack_8[6],puStack_18);
      iStack_10 = piStack_8[6];
      if (iStack_14 != 0) {
        FUN_004086c8(piStack_c,(int)param_3,&iStack_14);
      }
    }
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0040ca7b;
  pcStack_2c = (code *)0x40ca73;
  FUN_004034dc((int *)&puStack_18);
  return;
}

