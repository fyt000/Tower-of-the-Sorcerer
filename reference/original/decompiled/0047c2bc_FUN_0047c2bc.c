/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0047c2bc. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_0047c2bc(int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  int extraout_ECX_08;
  int extraout_ECX_09;
  int extraout_ECX_10;
  int extraout_ECX_11;
  int extraout_ECX_12;
  int extraout_ECX_13;
  int extraout_ECX_14;
  int extraout_ECX_15;
  int extraout_ECX_16;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  undefined4 extraout_EDX_08;
  undefined4 extraout_EDX_09;
  undefined4 extraout_EDX_10;
  undefined4 extraout_EDX_11;
  undefined4 extraout_EDX_12;
  undefined4 extraout_EDX_13;
  undefined4 extraout_EDX_14;
  undefined4 extraout_EDX_15;
  undefined4 extraout_EDX_16;
  undefined4 uVar3;
  undefined4 extraout_EDX_17;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;

  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0047c70c;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_00431188(*(int **)(param_1 + 0x2d8),param_2,param_3);
  FUN_00431c8c(*(int *)(param_1 + 0x2d8),'\t');
  iVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  switch(original_hero._360_4_) {
  case 5:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_067xgw.mid");
    iVar2 = extraout_ECX_00;
    uVar3 = extraout_EDX_00;
    break;
  case 6:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_058xgw.mid");
    iVar2 = extraout_ECX_01;
    uVar3 = extraout_EDX_01;
    break;
  case 7:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_008xgw.mid");
    iVar2 = extraout_ECX_02;
    uVar3 = extraout_EDX_02;
    break;
  case 8:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_118xgw.mid");
    iVar2 = extraout_ECX_03;
    uVar3 = extraout_EDX_03;
    break;
  case 9:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_019xgw.mid");
    iVar2 = extraout_ECX_04;
    uVar3 = extraout_EDX_04;
    break;
  case 10:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_018xgw.mid");
    iVar2 = extraout_ECX_05;
    uVar3 = extraout_EDX_05;
    break;
  case 0xb:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_050xgw.mid");
    iVar2 = extraout_ECX_06;
    uVar3 = extraout_EDX_06;
    break;
  case 0xc:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_085xgw.mid");
    iVar2 = extraout_ECX_07;
    uVar3 = extraout_EDX_07;
    break;
  case 0xd:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_032xgw.mid");
    iVar2 = extraout_ECX_08;
    uVar3 = extraout_EDX_08;
    break;
  case 0xe:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_046xgw.mid");
    iVar2 = extraout_ECX_09;
    uVar3 = extraout_EDX_09;
    break;
  case 0xf:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_005xgw.mid");
    iVar2 = extraout_ECX_10;
    uVar3 = extraout_EDX_10;
    break;
  case 0x10:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_007xgw.mid");
    iVar2 = extraout_ECX_11;
    uVar3 = extraout_EDX_11;
    break;
  case 0x11:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_110xgw.mid");
    iVar2 = extraout_ECX_12;
    uVar3 = extraout_EDX_12;
    break;
  case 0x12:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\a_023xgw.mid");
    iVar2 = extraout_ECX_13;
    uVar3 = extraout_EDX_13;
    break;
  case 0x13:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_117xgw.mid");
    iVar2 = extraout_ECX_14;
    uVar3 = extraout_EDX_14;
    break;
  case 0x14:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\b_014xgw.mid");
    iVar2 = extraout_ECX_15;
    uVar3 = extraout_EDX_15;
    break;
  case 0x15:
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,1,&local_8);
    FUN_0040369c((int *)(*(int *)(param_1 + 0x2d8) + 0x20c),local_8,
                 (undefined4 *)"\\midi\\A_027xgw.mid");
    iVar2 = extraout_ECX_16;
    uVar3 = extraout_EDX_16;
  }
  FUN_00430f20(*(int **)(param_1 + 0x2d8),uVar3,iVar2);
  FUN_00431c5c(*(int *)(param_1 + 0x2d8),'\x01');
  FUN_00431250(*(int **)(param_1 + 0x2d8),extraout_EDX_17);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0047c713;
  puStack_1c = (undefined *)0x47c70b;
  FUN_004034dc((int *)&local_8);
  return;
}
