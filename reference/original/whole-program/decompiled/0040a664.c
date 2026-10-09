/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a664.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a664(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int iStack_c;
  int iStack_8;
  
  puStack_1c = &stack0xfffffffc;
  iStack_c = 0;
  puStack_20 = &LAB_0040a6d0;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  iStack_8 = param_3;
  if (param_2 != param_3) {
    (**(code **)(*param_1 + 0xc))(param_1,param_2,&iStack_c);
    uVar1 = (**(code **)(*param_1 + 0x14))(param_1,param_2);
    (**(code **)(*param_1 + 0x3c))(param_1,param_2);
    FUN_0040a534(param_1,iStack_8,iStack_c,uVar1);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0040a6d7;
  puStack_20 = (undefined *)0x40a6cf;
  FUN_004034dc(&iStack_c);
  return;
}

