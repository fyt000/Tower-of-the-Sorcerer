/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d084.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d084(int param_1,undefined4 param_2,uint param_3)

{
  uint extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  int local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = 0;
  puStack_1c = &LAB_0040d0c3;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_0040cdf4(param_1,&local_8,param_3);
  FUN_0040cf94(param_1,extraout_EDX,extraout_ECX);
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040d0ca;
  puStack_1c = (undefined *)0x40d0c2;
  FUN_004034dc(&local_8);
  return;
}

