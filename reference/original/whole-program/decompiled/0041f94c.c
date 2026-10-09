/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f94c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041f94c(undefined param_1,undefined param_2,undefined param_3,HWND param_4)

{
  uint3 in_register_00000001;
  uint uVar1;
  
  uVar1 = (uint)in_register_00000001 << 8;
  if ((param_4 != DAT_0048958c) && (uVar1 = DAT_0048a6f8, param_4 != *(HWND *)(DAT_0048a6f8 + 0x20))
     ) {
    uVar1 = IsWindowVisible(param_4);
    if (uVar1 != 0) {
      uVar1 = IsWindowEnabled(param_4);
      if (uVar1 != 0) {
        uVar1 = GetWindowLongA(param_4,-0x14);
        if ((uVar1 & 8) == 0) {
          if (DAT_00489590 == (HWND)0x0) {
            DAT_00489590 = param_4;
          }
        }
        else if (DAT_00489594 == (HWND)0x0) {
          DAT_00489594 = param_4;
        }
      }
    }
  }
  return CONCAT22((short)(uVar1 >> 0x10),1);
}

