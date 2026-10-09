/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004131fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004131fc(int param_1,int *param_2)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined local_c;
  
  if (*(int *)(param_1 + 0x20) == 0) {
    local_10 = *(undefined4 *)(param_1 + 8);
    local_c = 0xb;
    uVar1 = FUN_0040753c(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf02f,0,&local_10);
    FUN_004031f8(uVar1);
  }
  (**(code **)(**(int **)(param_1 + 0x20) + 0x28))(*(int **)(param_1 + 0x20),param_2);
  *param_2 = *param_2 + *(int *)(param_1 + 0x24);
  param_2[1] = param_2[1] + *(int *)(param_1 + 0x28);
  return;
}

