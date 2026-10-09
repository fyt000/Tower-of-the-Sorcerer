/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424c34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424c34(int param_1,undefined4 *param_2)

{
  LPCSTR lpString;
  
  if (*(char *)(param_1 + 0x7e) != '\0') {
    lpString = FUN_00403814((undefined *)param_2);
    SetWindowTextA(*(HWND *)(param_1 + 0x20),lpString);
    return;
  }
  FUN_0040352c((int *)(param_1 + 0x6c),param_2);
  return;
}

