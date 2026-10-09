/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e810.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042e810(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  int *piStack_8;
  
  puStack_14 = &stack0xfffffffc;
  iVar1 = param_1[2];
  uStack_10 = *(undefined4 *)(iVar1 + 0x148);
  uStack_c = *(undefined4 *)(iVar1 + 0x14c);
  *(undefined4 *)(iVar1 + 0x148) = 0;
  *(undefined4 *)(iVar1 + 0x14c) = 0;
  puStack_18 = &LAB_0042e87b;
  uStack_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_1c;
  piStack_8 = param_1;
  FUN_0040a024(param_1,param_2);
  *in_FS_OFFSET = uStack_1c;
  iVar1 = piStack_8[2];
  *(undefined4 *)(iVar1 + 0x148) = uStack_10;
  *(undefined4 *)(iVar1 + 0x14c) = uStack_c;
  return;
}

