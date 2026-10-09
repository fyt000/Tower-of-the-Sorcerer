/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a2c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a2c0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  int iStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  puStack_24 = &stack0xfffffffc;
  iStack_14 = 0;
  uStack_10 = 0;
  puStack_28 = &LAB_0040a361;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  uStack_8 = param_3;
  (**(code **)(*param_1 + 0xc))(param_1,param_2,&uStack_10);
  uStack_c = (**(code **)(*param_1 + 0x14))(param_1,param_2);
  (**(code **)(*param_1 + 0xc))(param_1,uStack_8,&iStack_14);
  (**(code **)(*param_1 + 0x1c))(param_1,param_2,iStack_14);
  uVar1 = (**(code **)(*param_1 + 0x14))(param_1,uStack_8);
  (**(code **)(*param_1 + 0x20))(param_1,param_2,uVar1);
  (**(code **)(*param_1 + 0x1c))(param_1,uStack_8,uStack_10);
  (**(code **)(*param_1 + 0x20))(param_1,uStack_8,uStack_c);
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_0040a368;
  puStack_28 = (undefined *)0x40a360;
  FUN_004034fc(&iStack_14,2);
  return;
}

