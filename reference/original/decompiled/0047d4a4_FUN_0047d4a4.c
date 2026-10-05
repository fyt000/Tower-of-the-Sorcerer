/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0047d4a4. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_0047d4a4(int param_1)

{
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int iVar1;
  int extraout_ECX_04;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar2;
  undefined4 extraout_EDX_04;

  FUN_004102f0(*(int *)(param_1 + 0x3f4),0);
  FUN_004102f0(*(int *)(param_1 + 0x3c0),0);
  FUN_004102f0(*(int *)(param_1 + 0x3c4),0);
  FUN_004102f0(*(int *)(param_1 + 0x3bc),0);
  if (DAT_00489b9c == 8) {
    if (DAT_00489b9d == 10) {
      FUN_004102f0(*(int *)(param_1 + 0x3f4),1);
    }
  }
  else if (DAT_00489b9c == 9) {
    if (DAT_00489b9d == 0xb) {
      FUN_004102f0(*(int *)(param_1 + 0x3c0),1);
    }
  }
  else if (DAT_00489b9c == 10) {
    if (DAT_00489b9d == 0xc) {
      FUN_004102f0(*(int *)(param_1 + 0x3c4),1);
    }
  }
  else if ((DAT_00489b9c == 0xc) && (DAT_00489b9d == 0xe)) {
    FUN_004102f0(*(int *)(param_1 + 0x3bc),1);
  }
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3c8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3cc) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3d0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3d4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 1000) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3ec) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3e4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3d8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3dc) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3e0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x294) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x298) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x29c) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2a0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2a4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2a8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2ac) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2b0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2b4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2b8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 700) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2c0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2c4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2c8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2f0) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2f4) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2f8) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2fc) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x300) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x304) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x308) + 0x44),(uint)DAT_00489b9c);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x3f0) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1c8) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x1cc) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2dc) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2e0) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2e4) + 0x44),(uint)DAT_00489b9d);
  FUN_00419e4c(*(int **)(*(int *)(param_1 + 0x2e8) + 0x44),(uint)DAT_00489b9d);
  FUN_004102f0(*(int *)(param_1 + 0x3a8),0);
  FUN_004102f0(*(int *)(param_1 + 0x3ac),0);
  FUN_004102f0(*(int *)(param_1 + 0x3b0),0);
  if (DAT_00489b9f == '\x01') {
    FUN_004102f0(*(int *)(param_1 + 0x3a8),1);
  }
  else if (DAT_00489b9f == '\x02') {
    FUN_004102f0(*(int *)(param_1 + 0x3ac),1);
  }
  else if (DAT_00489b9f == '\x03') {
    FUN_004102f0(*(int *)(param_1 + 0x3b0),1);
  }
  FUN_0047f5a8(param_1);
  if (DAT_00489ba0 == '\0') {
    DAT_00489ba0 = '\0';
    FUN_004102f0(*(int *)(param_1 + 0x350),1);
    FUN_004102f0(*(int *)(param_1 + 0x354),0);
    FUN_00450758(param_1);
    *(undefined *)(DAT_0048c510 + 0x118) = 0;
    FUN_00450880(param_1);
    iVar1 = extraout_ECX_00;
    uVar2 = extraout_EDX_00;
  }
  else {
    iVar1 = extraout_ECX;
    uVar2 = extraout_EDX;
    if (DAT_00489ba0 == '\x01') {
      DAT_00489ba0 = '\x01';
      FUN_004102f0(*(int *)(param_1 + 0x350),0);
      FUN_004102f0(*(int *)(param_1 + 0x354),1);
      FUN_00450758(param_1);
      *(undefined *)(DAT_0048c510 + 0x118) = 1;
      FUN_00450880(param_1);
      iVar1 = extraout_ECX_01;
      uVar2 = extraout_EDX_01;
    }
  }
  if (DAT_00489ba1 == '\0') {
    FUN_004102f0(*(int *)(param_1 + 0x420),0);
    iVar1 = extraout_ECX_02;
    uVar2 = extraout_EDX_02;
  }
  else if (DAT_00489ba1 == '\x01') {
    FUN_004102f0(*(int *)(param_1 + 0x420),1);
    iVar1 = extraout_ECX_03;
    uVar2 = extraout_EDX_03;
  }
  if (DAT_00489ba2 == '\0') {
    FUN_00431188(*(int **)(param_1 + 0x2d8),uVar2,iVar1);
    original_hero._360_4_ = 0;
    DAT_00489ba2 = '\0';
    FUN_004102f0(*(int *)(param_1 + 0x330),0);
  }
  else if (DAT_00489ba2 == '\x01') {
    FUN_004102f0(*(int *)(param_1 + 0x330),1);
    FUN_0047c8f8();
    DAT_00489ba2 = '\x01';
    FUN_0047c2bc(param_1,extraout_EDX_04,extraout_ECX_04);
  }
  if (DAT_00489ba3 == '\0') {
    original_hero._356_4_ = 0;
    FUN_004102f0(*(int *)(param_1 + 0x32c),1);
  }
  else if (DAT_00489ba3 == '\x01') {
    original_hero._356_4_ = 1;
    FUN_004102f0(*(int *)(param_1 + 0x32c),0);
  }
  if (DAT_00489ba4 == '\0') {
    FUN_004102f0(*(int *)(param_1 + 0x47c),0);
    FUN_004102f0(*(int *)(param_1 + 0x478),1);
    return;
  }
  if (DAT_00489ba4 == '\x01') {
    FUN_004102f0(*(int *)(param_1 + 0x47c),1);
    FUN_004102f0(*(int *)(param_1 + 0x478),0);
  }
  return;
}
