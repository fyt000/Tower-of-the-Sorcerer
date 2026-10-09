/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424bec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424bec(int param_1,int *param_2)

{
  uint uVar1;
  undefined4 local_108 [64];
  
  if (*(char *)(param_1 + 0x7e) == '\0') {
    FUN_00403570(param_2,*(int *)(param_1 + 0x6c));
  }
  else {
    uVar1 = GetWindowTextA(*(HWND *)(param_1 + 0x20),(LPSTR)local_108,0x100);
    FUN_004035bc(param_2,local_108,uVar1);
  }
  return;
}

