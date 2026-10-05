/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00480ee0. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00480ee0(int param_1)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;

  FUN_00450758(param_1);
  DAT_00489ba0 = 0;
  if (*(char *)(*(int *)(param_1 + 0x41c) + 0x20) == '\0') {
    FUN_00413500(*(int **)(param_1 + 0x450),CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                );
    FUN_00413500(*(int **)(param_1 + 0x454),CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                 extraout_ECX_00);
    FUN_00413500(*(int **)(param_1 + 0x458),CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),
                 extraout_ECX_01);
    FUN_00413500(*(int **)(param_1 + 0x45c),CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),
                 extraout_ECX_02);
  }
  FUN_004102f0(*(int *)(param_1 + 0x350),1);
  FUN_004102f0(*(int *)(param_1 + 0x354),0);
  *(undefined *)(DAT_0048c510 + 0x118) = 0;
  FUN_00450880(param_1);
  return;
}
