/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bca0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bca0(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  uint extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_c;
  char local_5;
  
  puStack_1c = &stack0xfffffffc;
  local_c = 0;
  puStack_20 = &LAB_0040bd14;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_0040b944(param_1,6,param_3);
  FUN_0040bc08(param_1,(undefined4 *)&local_5,1);
  if (local_5 != '\x01') {
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    uVar1 = FUN_0040cdf4(param_1,&local_c,extraout_ECX);
    FUN_0040b8e0(uVar1,extraout_EDX);
  }
  FUN_0040bc08(param_1,(undefined4 *)&local_5,1);
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0040bd1b;
  puStack_20 = (undefined *)0x40bd13;
  FUN_004034dc(&local_c);
  return;
}

