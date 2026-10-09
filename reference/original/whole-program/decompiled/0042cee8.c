/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042cee8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042cee8(uint *param_1,undefined4 param_2,ushort param_3,int param_4,int param_5,
                 int param_6)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  
  puStack_1c = (undefined *)0x42cf09;
  piVar1 = (int *)FUN_0042ca6c(param_1,param_2,param_3);
  puStack_20 = &LAB_0042cf63;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  piVar1[0x34] = param_6;
  puStack_1c = &stack0xfffffffc;
  if (-1 < param_5) {
    puStack_1c = &stack0xfffffffc;
    FUN_00413098(piVar1,param_5);
  }
  if (-1 < param_4) {
    FUN_004130b8(piVar1,param_4);
  }
  FUN_004237dc(piVar1);
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0042cf6a;
  puStack_20 = (undefined *)0x42cf62;
  FUN_00402c34(piVar1);
  return;
}

