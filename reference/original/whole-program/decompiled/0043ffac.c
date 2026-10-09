/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043ffac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043ffac(int *param_1,int *param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int iStack_8;
  
  puStack_18 = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_1c = &LAB_0044000d;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004034dc(param_2);
  FUN_0043fa68(param_1,&iStack_8);
  if (iStack_8 != 0) {
    FUN_0043fa68(param_1,&iStack_8);
    FUN_0043d5cc((undefined *)param_1[0x4f],iStack_8,param_2);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_00440014;
  puStack_1c = (undefined *)0x44000c;
  FUN_004034dc(&iStack_8);
  return;
}

