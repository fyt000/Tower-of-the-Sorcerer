/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416344.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416344(int **param_1)

{
  bool bVar1;
  
  if ((*(char *)(param_1 + 0xe) == '\0') && (param_1[8] != (int *)0x0)) {
    FUN_00414ae4(param_1,'\0');
  }
  bVar1 = FUN_00416e54((int)param_1);
  if ((bVar1) && ((*(byte *)(param_1 + 7) & 0x10) == 0)) {
    EnableWindow((HWND)param_1[0x30],(uint)*(byte *)(param_1 + 0xe));
  }
  return;
}

