/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004282d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004282d8(int *param_1)

{
  int *piVar1;
  uint uVar2;
  tagRECT tStack_28;
  RECT RStack_18;
  
  piVar1 = (int *)param_1[0x2a];
  uVar2 = FUN_0042842c((int)param_1);
  if ((char)uVar2 == '\0') {
    FUN_0041a154((int *)piVar1[5],param_1[0x12]);
    FUN_0041a20c((int *)piVar1[5],'\0');
    (**(code **)(*param_1 + 0x2c))(param_1,&RStack_18);
    FUN_0041a664(piVar1,&RStack_18);
  }
  FUN_0041a20c((int *)piVar1[5],'\x01');
  (**(code **)(*param_1 + 0x2c))(param_1,&tStack_28);
  FUN_004281f0(param_1,&tStack_28,
               *(ushort *)(&DAT_00489674 + (uint)*(byte *)((int)param_1 + 0xb2) * 2) | 0x40 |
               *(ushort *)(&DAT_0048966c + (uint)*(byte *)(param_1 + 0x2c) * 2));
  return;
}

