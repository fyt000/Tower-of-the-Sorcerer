/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424b04.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00424b04(int param_1)

{
  BOOL BVar1;
  
  BVar1 = IsIconic(*(HWND *)(param_1 + 0x20));
  if (BVar1 == 0) {
    FUN_004243f4(param_1);
    SetActiveWindow(*(HWND *)(param_1 + 0x20));
    FUN_00423fbc(*(HWND *)(param_1 + 0x20),6);
    if (*(short *)(param_1 + 0xce) != 0) {
      (**(code **)(param_1 + 0xcc))(*(undefined4 *)(param_1 + 0xd0),param_1);
    }
  }
  return;
}

