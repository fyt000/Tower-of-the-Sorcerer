/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f860.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041f860(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  DWORD dwThreadId;
  undefined4 *in_FS_OFFSET;
  code *lpfn;
  LPARAM lParam;
  undefined4 uStack_34;
  code *pcStack_30;
  undefined *puStack_2c;
  undefined4 local_28;
  code *pcStack_24;
  undefined *puStack_20;
  
  uVar2 = DAT_00489598;
  uVar1 = DAT_0048958c;
  puStack_20 = &stack0xfffffffc;
  puStack_2c = &stack0xfffffffc;
  DAT_00489598 = 0;
  pcStack_24 = thunk_FUN_00403140;
  local_28 = *in_FS_OFFSET;
  DAT_0048958c = param_1;
  *in_FS_OFFSET = &local_28;
  pcStack_30 = thunk_FUN_00402f4c;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  lParam = 0;
  lpfn = root_0041f810;
  dwThreadId = GetCurrentThreadId();
  EnumThreadWindows(dwThreadId,lpfn,lParam);
  *in_FS_OFFSET = uStack_34;
  *in_FS_OFFSET = local_28;
  DAT_00489598 = uVar2;
  DAT_0048958c = uVar1;
  return;
}

