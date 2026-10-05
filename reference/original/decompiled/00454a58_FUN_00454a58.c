/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00454a58. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void FUN_00454a58(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  dword dVar5;

  iVar3 = original_hero.y * 0xb + original_hero.x;
  scratch_index = (iVar3 % 0xb) * *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  neighbor_index = (iVar3 / 0xb) * *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar3 = 5;
  dVar5 = neighbor_index;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,
               scratch_index - *(int *)(*(int *)(param_1 + 0x254) + 0x2c),iVar3,dVar5);
  iVar3 = 5;
  dVar5 = neighbor_index;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,
               *(int *)(*(int *)(param_1 + 0x254) + 0x2c) + scratch_index,iVar3,dVar5);
  iVar3 = *(int *)(param_1 + 0x254);
  iVar2 = neighbor_index - *(int *)(iVar3 + 0x30);
  iVar4 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,scratch_index - *(int *)(iVar3 + 0x2c),iVar4,iVar2)
  ;
  iVar3 = neighbor_index - *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  iVar2 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,scratch_index,iVar2,iVar3);
  iVar3 = *(int *)(param_1 + 0x254);
  iVar2 = neighbor_index - *(int *)(iVar3 + 0x30);
  iVar4 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,*(int *)(iVar3 + 0x2c) + scratch_index,iVar4,iVar2)
  ;
  iVar3 = *(int *)(param_1 + 0x254);
  iVar2 = neighbor_index + *(int *)(iVar3 + 0x30) * -2;
  iVar4 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,scratch_index - *(int *)(iVar3 + 0x2c),iVar4,iVar2)
  ;
  iVar3 = neighbor_index + *(int *)(*(int *)(param_1 + 0x254) + 0x30) * -2;
  iVar2 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,scratch_index,iVar2,iVar3);
  iVar3 = *(int *)(param_1 + 0x254);
  iVar2 = neighbor_index + *(int *)(iVar3 + 0x30) * -2;
  iVar4 = 5;
  piVar1 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_00417e44(*(int **)(param_1 + 0x1b0),piVar1,*(int *)(iVar3 + 0x2c) + scratch_index,iVar4,iVar2)
  ;
  return;
}
