/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004178bc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004178bc(int param_1,HIMAGELIST param_2)

{
  int local_c;
  int local_8;
  
  local_8 = *(int *)(param_1 + 0x24);
  local_c = *(int *)(param_1 + 0x20);
  ImageList_GetIconSize(param_2,&local_8,&local_c);
  *(int *)(param_1 + 0x24) = local_8;
  *(int *)(param_1 + 0x20) = local_c;
  FUN_00417814(param_1);
  return;
}

