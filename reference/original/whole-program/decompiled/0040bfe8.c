/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040bfe8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040bfe8(int param_1,int *param_2)

{
  uint extraout_ECX;
  uint extraout_ECX_00;
  undefined *extraout_ECX_01;
  undefined *puVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_44;
  code *pcStack_40;
  undefined4 local_38;
  code *pcStack_34;
  undefined *puStack_30;
  int local_20;
  int local_1c;
  int local_18;
  int *local_14;
  int local_10;
  int *local_c;
  byte local_5;
  
  puStack_30 = &stack0xfffffffc;
  local_18 = 0;
  local_1c = 0;
  pcStack_34 = thunk_FUN_00403140;
  local_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_38;
  local_10 = param_1;
  local_c = param_2;
  FUN_0040c3dc(param_1,&local_5,&local_20);
  FUN_0040cdf4(local_10,&local_18,extraout_ECX);
  FUN_0040cdf4(local_10,&local_1c,extraout_ECX_00);
  local_14 = local_c;
  puVar1 = extraout_ECX_01;
  uVar2 = extraout_EDX;
  if (local_c == (int *)0x0) {
    if ((local_5 & 1) == 0) {
      pcStack_40 = (code *)0x40c052;
      puVar1 = &stack0xfffffffc;
      FUN_0040be60(0,(char)extraout_EDX,(char)extraout_ECX_01,&stack0xfffffffc);
      uVar2 = extraout_EDX_01;
    }
    else {
      pcStack_40 = (code *)0x40c049;
      puVar1 = &stack0xfffffffc;
      FUN_0040bf50(0,(char)extraout_EDX,(char)extraout_ECX_01,&stack0xfffffffc);
      uVar2 = extraout_EDX_00;
    }
  }
  if (local_14 != (int *)0x0) {
    pcStack_40 = thunk_FUN_00402f4c;
    uStack_44 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_44;
    *(byte *)(local_14 + 7) = *(byte *)(local_14 + 7) | 1;
    if ((local_5 & 1) == 0) {
      FUN_0040bed8(local_14,uVar2,puVar1,(int)&stack0xfffffffc);
    }
    if (local_14 == (int *)0x0) {
      *in_FS_OFFSET = uStack_44;
    }
    else {
      *(byte *)(local_14 + 7) = *(byte *)(local_14 + 7) | 2;
      (**(code **)(*local_14 + 0x14))(local_14,local_10);
      *(byte *)(local_14 + 7) = *(byte *)(local_14 + 7) & 0xfd;
      if ((local_5 & 2) != 0) {
        FUN_00402cdc(*(int **)(local_10 + 0x28),local_14,local_20);
      }
      FUN_004099a4(*(int **)(local_10 + 0x30),local_14);
      *in_FS_OFFSET = uStack_44;
    }
  }
  *in_FS_OFFSET = local_38;
  puStack_30 = &LAB_0040c11f;
  pcStack_34 = (code *)0x40c117;
  FUN_004034fc(&local_1c,2);
  return;
}

