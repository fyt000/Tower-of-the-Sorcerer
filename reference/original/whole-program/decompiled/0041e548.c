/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e548.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e548(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  HICON pHVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  code *pcStack_24;
  undefined *puStack_20;
  undefined4 local_e;
  int *local_8;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(int *)(iVar1 + 8) == 0) {
    if (*(int *)(iVar1 + 0xc) == 0) {
      puStack_20 = (undefined *)0x41e56b;
      FUN_0041ac44(param_1,param_2);
      param_3 = extraout_ECX;
      param_2 = extraout_EDX;
    }
    puStack_20 = (undefined *)0x41e577;
    local_8 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    pcStack_24 = thunk_FUN_00402f4c;
    uStack_28 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_28;
    puStack_20 = &stack0xfffffffc;
    iVar2 = FUN_0041e4b8(param_1);
    if (iVar2 == DAT_0048a6e4) {
      FUN_004029b8(&local_e,6,0);
      FUN_0040af88(local_8,&local_e,6);
    }
    else {
      pHVar3 = (HICON)FUN_0041e4b8(param_1);
      FUN_0041bb60(local_8,pHVar3,'\0');
    }
    *in_FS_OFFSET = uStack_28;
    *(int **)(iVar1 + 8) = local_8;
  }
  return;
}

