/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c698.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042c698(int *param_1)

{
  int *piVar1;
  LONG LVar2;
  LPCSTR lpchText;
  HDC hdc;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  uint uVar3;
  undefined4 *in_FS_OFFSET;
  int cchText;
  tagRECT *lprc;
  undefined4 uStack_38;
  undefined *puStack_34;
  undefined *puStack_30;
  undefined *puStack_20;
  tagRECT tStack_1c;
  undefined4 uStack_8;
  
  puStack_30 = &stack0xfffffffc;
  puStack_20 = (undefined *)0x0;
  puStack_34 = &LAB_0042c7db;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  (**(code **)(*param_1 + 0x2c))(param_1,&tStack_1c);
  if (*(char *)((int)param_1 + 0x105) != '\0') {
    FUN_0042c660(*(char *)((int)param_1 + 0x105),extraout_EDX,extraout_ECX,(int)&stack0xfffffffc);
    FUN_0042bf20(param_1[0x40],&tStack_1c,uStack_8,param_1[0x42]);
  }
  FUN_0042bf20(param_1[0x40],&tStack_1c,param_1[0x12],param_1[0x43]);
  if (*(char *)(param_1 + 0x41) != '\0') {
    FUN_0042c660(*(char *)(param_1 + 0x41),extraout_EDX_00,extraout_ECX_00,(int)&stack0xfffffffc);
    FUN_0042bf20(param_1[0x40],&tStack_1c,uStack_8,param_1[0x42]);
  }
  piVar1 = (int *)param_1[0x40];
  FUN_0041a154((int *)piVar1[5],param_1[0x12]);
  FUN_0041a664(piVar1,&tStack_1c);
  FUN_0041a20c((int *)piVar1[5],'\x01');
  FUN_0041a8bc((int)piVar1);
  LVar2 = FUN_0041a874(piVar1,&DAT_0042c7f4);
  uVar3 = (tStack_1c.bottom + tStack_1c.top) - LVar2;
  tStack_1c.top = (int)uVar3 >> 1;
  if (tStack_1c.top < 0) {
    tStack_1c.top = tStack_1c.top + (uint)((uVar3 & 1) != 0);
  }
  tStack_1c.bottom = LVar2 + tStack_1c.top;
  uVar3 = (uint)(*(ushort *)(&DAT_00489738 + (uint)*(byte *)(param_1 + 0x47) * 2) | 0x44);
  lprc = &tStack_1c;
  cchText = -1;
  FUN_004135a4(param_1,(int *)&puStack_20);
  lpchText = FUN_00403814(puStack_20);
  hdc = (HDC)FUN_0041a950(piVar1);
  DrawTextA(hdc,lpchText,cchText,lprc,uVar3);
  *in_FS_OFFSET = uStack_38;
  puStack_30 = &LAB_0042c7e2;
  puStack_34 = (undefined *)0x42c7da;
  FUN_004034dc((int *)&puStack_20);
  return;
}

