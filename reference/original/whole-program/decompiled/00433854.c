/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433854.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00433854(int *param_1,int param_2)

{
  uint uVar1;
  HDC hDC;
  undefined4 *in_FS_OFFSET;
  bool bVar2;
  tagRECT *lprc;
  undefined4 uStack_48;
  undefined *puStack_44;
  undefined *puStack_40;
  undefined *local_30;
  tagRECT local_2c;
  tagRECT local_1c;
  uint local_c;
  byte local_5;
  
  puStack_40 = &stack0xfffffffc;
  local_30 = (undefined *)0x0;
  puStack_44 = &LAB_00433aa8;
  uStack_48 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_48;
  FUN_0041a9d0((int *)param_1[0x43],*(int *)(param_2 + 0x18));
  (**(code **)(*param_1 + 0x2c))(param_1,&local_1c);
  uVar1 = *(uint *)(param_2 + 0x10);
  bVar2 = (uVar1 & 1) == 0;
  if (*(char *)(param_1 + 0xe) == '\0') {
    local_5 = 1;
  }
  else if (bVar2) {
    local_5 = 0;
  }
  else {
    local_5 = 2;
  }
  local_c = 0x2010;
  if (!bVar2) {
    local_c = 0x2210;
  }
  if ((uVar1 & 4) != 0) {
    local_c = local_c | 0x100;
  }
  if (((uVar1 & 0x10) != 0 | *(byte *)(param_1 + 0x48)) != 0) {
    FUN_00419fa8(*(int **)(param_1[0x43] + 0x10),0x80000006);
    FUN_0041a060(*(int **)(param_1[0x43] + 0x10),1);
    FUN_0041a20c(*(int **)(param_1[0x43] + 0x14),'\x01');
    FUN_0041a73c((int *)param_1[0x43],local_1c.left,local_1c.top,local_1c.bottom,local_1c.right);
    InflateRect(&local_1c,-1,-1);
  }
  if (bVar2) {
    DrawFrameControl(*(HDC *)(param_2 + 0x18),&local_1c,4,local_c);
  }
  else {
    FUN_00419fa8(*(int **)(param_1[0x43] + 0x10),0x80000010);
    FUN_0041a060(*(int **)(param_1[0x43] + 0x10),1);
    FUN_0041a154(*(int **)(param_1[0x43] + 0x14),0x8000000f);
    FUN_0041a73c((int *)param_1[0x43],local_1c.left,local_1c.top,local_1c.bottom,local_1c.right);
    InflateRect(&local_1c,-1,-1);
  }
  if (*(char *)(param_1 + 0x48) != '\0') {
    (**(code **)(*param_1 + 0x2c))(param_1,&local_1c);
    InflateRect(&local_1c,-1,-1);
  }
  FUN_0041a8bc(param_1[0x43]);
  if (!bVar2) {
    OffsetRect(&local_1c,1,1);
  }
  FUN_004135a4(param_1,(int *)&local_30);
  FUN_0043365c(param_1[0x44],(int *)param_1[0x43],&local_1c.left,&local_2c,local_5,param_1[0x46],
               param_1[0x47],*(byte *)((int)param_1 + 0x116),local_30);
  if (*(char *)(param_1 + 0x48) != '\0') {
    (**(code **)(*param_1 + 0x2c))(param_1,&local_1c);
    InflateRect(&local_1c,-4,-4);
    FUN_00419fa8(*(int **)(param_1[0x43] + 0x10),0x80000006);
    FUN_0041a154(*(int **)(param_1[0x43] + 0x14),0x8000000f);
    lprc = &local_1c;
    hDC = (HDC)FUN_0041a950((int *)param_1[0x43]);
    DrawFocusRect(hDC,lprc);
  }
  FUN_0041a9d0((int *)param_1[0x43],0);
  *in_FS_OFFSET = uStack_48;
  puStack_40 = &LAB_00433aaf;
  puStack_44 = (undefined *)0x433aa7;
  FUN_004034dc((int *)&local_30);
  return;
}

