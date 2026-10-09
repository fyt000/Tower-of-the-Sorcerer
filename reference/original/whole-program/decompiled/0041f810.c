/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041f810.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_0041f810(void)

{
  BOOL BVar1;
  undefined4 *puVar2;
  HWND in_stack_00000004;
  
  if (in_stack_00000004 != DAT_0048958c) {
    BVar1 = IsWindowVisible(in_stack_00000004);
    if (BVar1 != 0) {
      BVar1 = IsWindowEnabled(in_stack_00000004);
      if (BVar1 != 0) {
        puVar2 = (undefined4 *)FUN_00402650(8);
        *puVar2 = DAT_00489598;
        puVar2[1] = in_stack_00000004;
        DAT_00489598 = puVar2;
        EnableWindow(in_stack_00000004,0);
      }
    }
  }
  return 1;
}

