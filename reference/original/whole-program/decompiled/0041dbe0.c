/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dbe0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041dbe0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  code *pcStack_24;
  undefined *puStack_20;
  LPVOID local_10;
  LPBITMAPINFO local_c;
  int *local_8;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(int *)(iVar1 + 8) == 0) {
    puStack_20 = (undefined *)0x41dc02;
    local_8 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    pcStack_24 = thunk_FUN_00402f4c;
    uStack_28 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_28;
    puStack_20 = &stack0xfffffffc;
    if (*(HBITMAP *)(iVar1 + 0xc) != (HBITMAP)0x0) {
      puStack_20 = &stack0xfffffffc;
      FUN_0041bae8(local_8,*(HBITMAP *)(iVar1 + 0xc),*(HPALETTE *)(iVar1 + 0x10),&local_10,&local_c,
                   0);
    }
    FUN_0040af10(local_8,0);
    *in_FS_OFFSET = uStack_28;
    *(int **)(iVar1 + 8) = local_8;
    *(LPBITMAPINFO *)(iVar1 + 0x1c) = local_c;
    *(LPVOID *)(iVar1 + 0x20) = local_10;
    if (**(int **)(iVar1 + 0x1c) == 0xc) {
      *(undefined *)(iVar1 + 0x25) = 2;
    }
    else if (**(int **)(iVar1 + 0x1c) == 0x28) {
      *(undefined *)(iVar1 + 0x25) = 1;
    }
    else {
      *(undefined *)(iVar1 + 0x25) = 0;
    }
  }
  return;
}

