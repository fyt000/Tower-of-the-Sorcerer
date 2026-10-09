/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041ce20.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041ce20(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  HENHMETAFILE pHVar2;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    FUN_0041c954(param_1);
  }
  else if (1 < *(int *)(*(int *)(param_1 + 0x10) + 4)) {
    iVar1 = FUN_00402c0c(0x41922c,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    pHVar2 = *(HENHMETAFILE *)(*(int *)(param_1 + 0x10) + 8);
    if (pHVar2 != (HENHMETAFILE)0x0) {
      pHVar2 = CopyEnhMetaFileA(pHVar2,(LPCSTR)0x0);
      *(HENHMETAFILE *)(iVar1 + 8) = pHVar2;
    }
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x10);
    *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0xc);
    *(undefined2 *)(iVar1 + 0x18) = *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x18);
    *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x1c);
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(*(int *)(param_1 + 0x10) + 0x20);
    FUN_0041c5b0(*(int **)(param_1 + 0x10));
    *(int *)(param_1 + 0x10) = iVar1;
    FUN_0041c5ac(iVar1);
  }
  return;
}

