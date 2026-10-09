/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410988.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00410988(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  for (iVar1 = FUN_00410958(param_1); (iVar1 != 0 && (*(int *)(iVar1 + 0x34) == 0));
      iVar1 = *(int *)(iVar1 + 0x44)) {
  }
  if (iVar1 != 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0x34);
  }
  return uVar2;
}

