/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00440a98.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TForm4_form4activate(int param_1)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 extraout_ECX_06;
  undefined4 extraout_ECX_07;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 extraout_EDX_05;
  undefined4 extraout_EDX_06;
  undefined4 extraout_EDX_07;
  
  FUN_004130d8(_DAT_0048c50c,0x1e0);
  FUN_004130f8(_DAT_0048c50c,0x106);
  FUN_004130d8(*(int **)(param_1 + 0x1b8),0x68);
  FUN_004130f8(*(int **)(param_1 + 0x1b8),0x19);
  FUN_00413098(*(int **)(param_1 + 0x1b8),0xf1);
  FUN_004130b8(*(int **)(param_1 + 0x1b8),200);
  FUN_004130d8(*(int **)(param_1 + 0x1bc),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x1bc),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  FUN_00413098(*(int **)(param_1 + 0x1bc),0x16b);
  FUN_004130b8(*(int **)(param_1 + 0x1bc),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x28));
  FUN_004130d8(*(int **)(param_1 + 0x1d0),0xe2);
  FUN_004130f8(*(int **)(param_1 + 0x1d0),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x30));
  FUN_00413098(*(int **)(param_1 + 0x1d0),*(undefined4 *)(*(int *)(param_1 + 0x1b8) + 0x24));
  FUN_004130b8(*(int **)(param_1 + 0x1d0),0xa8);
  FUN_004130d8(*(int **)(param_1 + 0x1c0),0x1cc);
  FUN_004130f8(*(int **)(param_1 + 0x1c0),0x15);
  FUN_00413098(*(int **)(param_1 + 0x1c0),5);
  FUN_004130b8(*(int **)(param_1 + 0x1c0),4);
  FUN_004130d8(*(int **)(param_1 + 0x1c4),0x5a);
  FUN_004130f8(*(int **)(param_1 + 0x1c4),0x15);
  FUN_00413098(*(int **)(param_1 + 0x1c4),5);
  FUN_004130b8(*(int **)(param_1 + 0x1c4),0x24);
  FUN_004130d8(*(int **)(param_1 + 0x1c8),
               *(int *)(*(int *)(param_1 + 0x1c0) + 0x2c) -
               *(int *)(*(int *)(param_1 + 0x1c4) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x1c8),0x19);
  FUN_00413098(*(int **)(param_1 + 0x1c8),
               *(int *)(*(int *)(param_1 + 0x1c4) + 0x24) +
               *(int *)(*(int *)(param_1 + 0x1c4) + 0x2c) + 2);
  FUN_004130b8(*(int **)(param_1 + 0x1c8),*(int *)(*(int *)(param_1 + 0x1c4) + 0x28) + -4);
  FUN_004130d8(*(int **)(param_1 + 0x1b4),0xe2);
  FUN_004130f8(*(int **)(param_1 + 0x1b4),0x89);
  FUN_00413098(*(int **)(param_1 + 0x1b4),*(undefined4 *)(*(int *)(param_1 + 0x1c4) + 0x24));
  FUN_004130b8(*(int **)(param_1 + 0x1b4),0x58);
  FUN_004130d8(*(int **)(param_1 + 0x1b0),0xe2);
  FUN_004130f8(*(int **)(param_1 + 0x1b0),0x14);
  FUN_00413098(*(int **)(param_1 + 0x1b0),*(undefined4 *)(*(int *)(param_1 + 0x1c4) + 0x24));
  FUN_004130b8(*(int **)(param_1 + 0x1b0),0x40);
  FUN_004130d8(*(int **)(param_1 + 0x1cc),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x1cc),0x61);
  FUN_00413098(*(int **)(param_1 + 0x1cc),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x24));
  FUN_004130b8(*(int **)(param_1 + 0x1cc),*(undefined4 *)(*(int *)(param_1 + 0x1b0) + 0x28));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),0xd);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),0xb);
  if (*(char *)(*(int *)(DAT_0048c510 + 0x3c0) + 0x28) == '\x01') {
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),0xb);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),9);
  }
  if (*(char *)(*(int *)(DAT_0048c510 + 0x3f4) + 0x28) == '\x01') {
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),10);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),8);
  }
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c8) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1b4) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1b0) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1b8) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1bc) + 0x44),iVar1);
  iVar1 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c4) + 0x44));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1d0) + 0x44),iVar1);
  FUN_00413500(*(int **)(param_1 + 0x1b8),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  FUN_00413500(*(int **)(param_1 + 0x1bc),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
               extraout_ECX_00);
  FUN_00413500(*(int **)(param_1 + 0x1d0),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
               extraout_ECX_01);
  FUN_00413500(*(int **)(param_1 + 0x1c0),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
               extraout_ECX_02);
  FUN_00413500(*(int **)(param_1 + 0x1c4),CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
               extraout_ECX_03);
  FUN_00413500(*(int **)(param_1 + 0x1c8),CONCAT31((int3)((uint)extraout_EDX_04 >> 8),1),
               extraout_ECX_04);
  FUN_00413500(*(int **)(param_1 + 0x1b4),CONCAT31((int3)((uint)extraout_EDX_05 >> 8),1),
               extraout_ECX_05);
  FUN_00413500(*(int **)(param_1 + 0x1b0),CONCAT31((int3)((uint)extraout_EDX_06 >> 8),1),
               extraout_ECX_06);
  FUN_00413500(*(int **)(param_1 + 0x1cc),CONCAT31((int3)((uint)extraout_EDX_07 >> 8),1),
               extraout_ECX_07);
  (**(code **)(**(int **)(param_1 + 0x1bc) + 0x80))();
  return;
}

