/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004026d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004026d0(uint param_1)

{
  uint uVar1;
  UINT UVar2;
  LPVOID pvVar3;
  undefined4 in_stack_00000000;
  
  uVar1 = param_1 & 0x7f;
  if (DAT_0048a004 != (code *)0x0) {
    uVar1 = (*DAT_0048a004)(uVar1,in_stack_00000000);
  }
  UVar2 = CONCAT31((int3)(uVar1 - 1 >> 8),*(undefined *)(uVar1 + 0x4026f8));
  if ((int)(uVar1 - 1) < 0) {
    pvVar3 = FUN_00403498();
    UVar2 = *(UINT *)((int)pvVar3 + 4);
  }
  FUN_00404431(UVar2);
  return;
}

