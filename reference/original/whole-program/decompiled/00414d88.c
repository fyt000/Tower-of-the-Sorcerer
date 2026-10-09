/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414d88.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414d88(int *param_1,int *param_2)

{
  int iVar1;
  HCURSOR pHVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_120;
  undefined *puStack_11c;
  undefined *puStack_118;
  byte local_108 [256];
  undefined *local_8;
  
  puStack_118 = &stack0xfffffffc;
  local_8 = (undefined *)0x0;
  puStack_11c = &LAB_00414e81;
  uStack_120 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_120;
  FUN_004029b8(param_2,0x8c,0);
  *param_2 = param_1[0x10];
  param_2[1] = 0x44000000;
  if ((*(byte *)(param_1 + 0xd) & 1) != 0) {
    param_2[1] = param_2[1] | 0x2000000;
  }
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) && (*(char *)(param_1 + 0xe) == '\0')) {
    param_2[1] = param_2[1] | 0x8000000;
  }
  if (*(char *)(param_1 + 0x31) != '\0') {
    param_2[1] = param_2[1] | 0x10000;
  }
  param_2[3] = param_1[9];
  param_2[4] = param_1[10];
  param_2[5] = param_1[0xb];
  param_2[6] = param_1[0xc];
  param_2[7] = 0;
  if ((int *)param_1[8] != (int *)0x0) {
    iVar1 = FUN_00416cbc((int *)param_1[8]);
    param_2[7] = iVar1;
  }
  param_2[9] = 0xb;
  param_2[10] = (int)DefWindowProcA;
  pHVar2 = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
  param_2[0xf] = (int)pHVar2;
  param_2[0x10] = 0;
  FUN_00402b7c(*param_1,local_108);
  FUN_004035fc((int *)&local_8,local_108);
  FUN_0040619c(param_2 + 0x13,local_8);
  *in_FS_OFFSET = uStack_120;
  puStack_118 = &LAB_00414e88;
  puStack_11c = (undefined *)0x414e80;
  FUN_004034dc((int *)&local_8);
  return;
}

