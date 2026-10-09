/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0043416c.
 * Inferred types and shared tails require assembly review. */

void TAboutBox_formactivate(int param_1)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 uVar1;
  undefined4 extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar2;
  
  FUN_004130d8(DAT_0048a760,0x102);
  FUN_004130f8(DAT_0048a760,0xcb);
  FUN_004130b8(*(int **)(param_1 + 0x1b0),8);
  FUN_00413098(*(int **)(param_1 + 0x1b0),8);
  FUN_004130d8(*(int **)(param_1 + 0x1b0),0xea);
  FUN_004130f8(*(int **)(param_1 + 0x1b0),0x80);
  FUN_004130b8(*(int **)(param_1 + 0x1bc),10);
  FUN_00413098(*(int **)(param_1 + 0x1bc),2);
  FUN_004130d8(*(int **)(param_1 + 0x1bc),0xe6);
  FUN_004130f8(*(int **)(param_1 + 0x1bc),0x16);
  FUN_004130b8(*(int **)(param_1 + 0x1d0),0x24);
  FUN_00413098(*(int **)(param_1 + 0x1d0),0x14);
  FUN_004130d8(*(int **)(param_1 + 0x1d0),0x28);
  FUN_004130f8(*(int **)(param_1 + 0x1d0),0x28);
  FUN_004130d8(*(int **)(param_1 + 0x1cc),100);
  FUN_004130f8(*(int **)(param_1 + 0x1cc),0x14);
  FUN_004130b8(*(int **)(param_1 + 0x1cc),0x24);
  FUN_00413098(*(int **)(param_1 + 0x1cc),0x43);
  FUN_004130b8(*(int **)(param_1 + 0x1c0),0x3c);
  FUN_00413098(*(int **)(param_1 + 0x1c0),0x43);
  FUN_004130d8(*(int **)(param_1 + 0x1c0),100);
  FUN_004130f8(*(int **)(param_1 + 0x1c0),0x14);
  FUN_004130b8(*(int **)(param_1 + 0x1c4),0x54);
  FUN_00413098(*(int **)(param_1 + 0x1c4),0x11);
  FUN_004130d8(*(int **)(param_1 + 0x1c4),200);
  FUN_004130f8(*(int **)(param_1 + 0x1c4),0x10);
  FUN_004130b8(*(int **)(param_1 + 0x1c8),100);
  FUN_00413098(*(int **)(param_1 + 0x1c8),0x11);
  FUN_004130d8(*(int **)(param_1 + 0x1c8),200);
  FUN_004130f8(*(int **)(param_1 + 0x1c8),0x10);
  FUN_004130d8(*(int **)(param_1 + 0x1b4),0x60);
  FUN_004130f8(*(int **)(param_1 + 0x1b4),0x18);
  FUN_004130b8(*(int **)(param_1 + 0x1b4),0x90);
  FUN_00413098(*(int **)(param_1 + 0x1b4),0x4d);
  FUN_004130b8(*(int **)(param_1 + 0x1d8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x28));
  FUN_00413098(*(int **)(param_1 + 0x1d8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x24));
  FUN_004130d8(*(int **)(param_1 + 0x1d8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x1d8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x30));
  FUN_004130b8(*(int **)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x28));
  FUN_00413098(*(int **)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x24));
  FUN_004130d8(*(int **)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x2c));
  FUN_004130f8(*(int **)(param_1 + 0x1b8),*(undefined4 *)(*(int *)(param_1 + 0x1d0) + 0x30));
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1bc) + 0x44),0xe);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),0xc);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),0xc);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),10);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c8) + 0x44),10);
  uVar1 = extraout_ECX;
  uVar2 = extraout_EDX;
  if (*(char *)(*(int *)(DAT_0048c510 + 0x3c0) + 0x28) == '\x01') {
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1bc) + 0x44),0xd);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),10);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),10);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),8);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c8) + 0x44),8);
    uVar1 = extraout_ECX_00;
    uVar2 = extraout_EDX_00;
  }
  if (*(char *)(*(int *)(DAT_0048c510 + 0x3f4) + 0x28) == '\x01') {
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1bc) + 0x44),0xc);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),9);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c0) + 0x44),9);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c4) + 0x44),7);
    FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c8) + 0x44),7);
    uVar1 = extraout_ECX_01;
    uVar2 = extraout_EDX_01;
  }
  FUN_00413500(*(int **)(param_1 + 0x1b8),CONCAT31((int3)((uint)uVar2 >> 8),1),uVar1);
  FUN_00413500(*(int **)(param_1 + 0x1d0),0,extraout_ECX_02);
  FUN_00413500(*(int **)(param_1 + 0x1d8),0,extraout_ECX_03);
  FUN_0042c454(*(int *)(param_1 + 0x1d4),'\x01');
  return;
}

