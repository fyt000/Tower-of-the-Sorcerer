/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e8f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e8f0(int param_1,int param_2,undefined *param_3,undefined *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined *local_10;
  undefined local_c;
  undefined *local_8;
  
  local_8 = param_3;
  if (param_2 != 0) {
    iVar1 = FUN_00405a34(param_3,param_4);
    if (iVar1 != 0) {
      iVar1 = FUN_0040e968(param_1,param_4);
      if (iVar1 != 0) {
        local_10 = param_4;
        local_c = 0xb;
        uVar2 = FUN_0040753c(0x408a84,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf010,0,&local_10
                            );
        FUN_004031f8(uVar2);
      }
    }
  }
  if (((*(byte *)(param_1 + 0x1c) & 0x10) != 0) && (*(int *)(param_1 + 4) != 0)) {
    (**(code **)(**(int **)(param_1 + 4) + 0x1c))(*(int **)(param_1 + 4),param_2,local_8,param_4);
  }
  return;
}

