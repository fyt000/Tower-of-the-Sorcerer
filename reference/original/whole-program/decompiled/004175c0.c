/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004175c0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004175c0(int *param_1,int param_2)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  int *piStack_8;
  
  puStack_c = (undefined *)0x4175d5;
  piStack_8 = param_1;
  FUN_0041a9d0((int *)param_1[0x40],param_2);
  puStack_10 = &LAB_0041760c;
  uStack_14 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_14;
  puStack_c = &stack0xfffffffc;
  (**(code **)(*piStack_8 + 0x84))();
  *in_FS_OFFSET = uStack_14;
  puStack_c = &LAB_00417613;
  puStack_10 = (undefined *)0x41760b;
  FUN_0041a9d0((int *)piStack_8[0x40],0);
  return;
}

