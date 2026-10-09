/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040753c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040753c(int param_1,undefined4 param_2,UINT param_3,undefined4 param_4,undefined4 param_5)

{
  UINT extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 **ppuVar1;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined4 in_stack_ffffffd8;
  undefined4 in_stack_ffffffdc;
  byte *local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  local_c = (byte *)0x0;
  if ((char)param_2 != '\0') {
    puStack_2c = (undefined *)0x407552;
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffd8,in_stack_ffffffdc);
    param_3 = extraout_ECX;
  }
  puStack_30 = &LAB_004075a8;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  ppuVar1 = &local_8;
  puStack_2c = &stack0xfffffffc;
  FUN_00405bf0(param_3,(int *)&local_c);
  FUN_0040661c(local_c,param_5,param_4,(int *)ppuVar1);
  FUN_0040352c((int *)(param_1 + 4),local_8);
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_004075af;
  puStack_30 = (undefined *)0x4075a7;
  FUN_004034fc((int *)&local_c,2);
  return;
}

