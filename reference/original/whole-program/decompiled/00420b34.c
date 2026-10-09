/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420b34.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00420b34(int *param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  undefined **ppuVar2;
  undefined4 uVar3;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_fffffebc;
  undefined4 uStack_13c;
  undefined *puStack_138;
  undefined *puStack_134;
  undefined4 in_stack_fffffed0;
  undefined4 in_stack_fffffed4;
  byte local_114 [256];
  byte *local_14;
  undefined local_10;
  char local_9;
  int *local_8;
  
  if ((char)param_2 != '\0') {
    puStack_134 = (undefined *)0x420b4c;
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_fffffed0,in_stack_fffffed4);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  local_9 = (char)param_2;
  puStack_134 = (undefined *)0x420b5c;
  local_8 = param_1;
  FUN_00420c70(param_1,0,param_3);
  puStack_134 = (undefined *)0x420b64;
  ppuVar2 = (undefined **)FUN_00402b78(local_8);
  if (ppuVar2 != &PTR_FUN_0041edfc) {
    *(byte *)((int)local_8 + 0x11d) = *(byte *)((int)local_8 + 0x11d) | 1;
    puStack_138 = &LAB_00420be9;
    uStack_13c = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_13c;
    puStack_134 = &stack0xfffffffc;
    cVar1 = FUN_0040976c(local_8,&PTR_FUN_0041edfc);
    if (cVar1 == '\0') {
      FUN_00402b7c(*local_8,local_114);
      local_14 = local_114;
      local_10 = 4;
      in_stack_fffffebc = 0;
      uVar3 = FUN_0040753c(0x408978,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xf00a,0,
                           &local_14);
      FUN_004031f8(uVar3);
    }
    *in_FS_OFFSET = in_stack_fffffebc;
    *(byte *)((int)local_8 + 0x11d) = *(byte *)((int)local_8 + 0x11d) & 0xfe;
    return local_8;
  }
  if (local_9 != '\0') {
    *in_FS_OFFSET = in_stack_fffffed0;
  }
  return local_8;
}

