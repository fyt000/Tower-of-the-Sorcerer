/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416df4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416df4(int *param_1,char param_2)

{
  bool bVar1;
  uint uVar2;
  
  if (param_2 != *(char *)(param_1 + 0x31)) {
    *(char *)(param_1 + 0x31) = param_2;
    bVar1 = FUN_00416e54((int)param_1);
    if (bVar1) {
      uVar2 = GetWindowLongA((HWND)param_1[0x30],-0x10);
      uVar2 = uVar2 & 0xfffeffff;
      if (param_2 != '\0') {
        uVar2 = uVar2 | 0x10000;
      }
      SetWindowLongA((HWND)param_1[0x30],-0x10,uVar2);
    }
    FUN_00413cb8(param_1,0xb028,0,0);
  }
  return;
}

