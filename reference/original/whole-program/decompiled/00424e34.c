/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424e34.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424e34(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 *puVar1;
  
  if (*(char *)(param_1 + 0x7e) == '\0') {
    if (*(HWND *)(param_1 + 0x20) != (HWND)0x0) {
      SendMessageA(*(HWND *)(param_1 + 0x20),0xb020,0,(LPARAM)&param_4);
    }
  }
  else {
    FUN_00409a28(*(int **)(param_1 + 0x80));
    puVar1 = (undefined4 *)FUN_00402650(8);
    *puVar1 = param_4;
    puVar1[1] = param_5;
    FUN_004099a4(*(int **)(param_1 + 0x80),puVar1);
  }
  return;
}

