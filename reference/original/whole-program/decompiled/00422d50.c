/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422d50.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422d50(int param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  uint *puStack_8;
  
  puStack_18 = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_1c = &UNK_00422dee;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  if (*(int *)(param_1 + 0x128) != 0) {
    iVar2 = 0;
    if ((*(short *)(param_2 + 6) != -1) || (puVar1 = &stack0xfffffffc, *(short *)(param_2 + 4) != 0)
       ) {
      puVar1 = &stack0xfffffffc;
      if ((*(byte *)(param_2 + 6) & 0x10) != 0) {
        GetSubMenu(*(HMENU *)(param_2 + 8),(uint)*(ushort *)(param_2 + 4));
        puVar1 = puStack_18;
      }
      puStack_18 = puVar1;
      iVar2 = FUN_00410958(*(int *)(param_1 + 0x128));
      puVar1 = puStack_18;
    }
    puStack_18 = puVar1;
    if (iVar2 == 0) {
      FUN_00425454(DAT_0048a6f8,(uint *)0x0);
    }
    else {
      FUN_00412444(*(int *)(iVar2 + 0x38),(int *)&puStack_8);
      FUN_00425454(DAT_0048a6f8,puStack_8);
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &UNK_00422df5;
  puStack_1c = (undefined *)0x422ded;
  FUN_004034dc((int *)&puStack_8);
  return;
}

