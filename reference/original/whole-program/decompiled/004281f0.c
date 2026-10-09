/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004281f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004281f0(int *param_1,LPRECT param_2,ushort param_3)

{
  int cchText;
  LPCSTR lpchText;
  HDC hdc;
  uint format;
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  char *local_8;
  
  format = (uint)param_3;
  puStack_18 = &stack0xfffffffc;
  local_8 = (char *)0x0;
  puStack_1c = &LAB_004282bd;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  (**(code **)(*param_1 + 0x58))(param_1,&local_8);
  if (((param_3 & 0x400) != 0) &&
     ((local_8 == (char *)0x0 ||
      (((*(char *)((int)param_1 + 0xb3) != '\0' && (*local_8 == '&')) && (local_8[1] == '\0')))))) {
    FUN_00403658((int *)&local_8,(undefined4 *)&LAB_004282d4);
  }
  if (*(char *)((int)param_1 + 0xb3) == '\0') {
    format = (uint)(param_3 | 0x800);
  }
  FUN_0041a8bc(param_1[0x2a]);
  if (*(char *)(param_1 + 0xe) == '\0') {
    FUN_00419c7c(*(int **)(param_1[0x2a] + 0xc),-0x7fffffef,extraout_ECX);
  }
  cchText = FUN_00403650((int)local_8);
  lpchText = FUN_00403814(local_8);
  hdc = (HDC)FUN_0041a950((int *)param_1[0x2a]);
  DrawTextA(hdc,lpchText,cchText,param_2,format);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_004282c4;
  puStack_1c = (undefined *)0x4282bc;
  FUN_004034dc((int *)&local_8);
  return;
}

