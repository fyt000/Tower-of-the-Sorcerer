/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dc94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041dc94(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((*(char *)(param_1 + 0x18) == '\0') &&
     (iVar1 = *(int *)(param_1 + 0x10), *(int *)(iVar1 + 0x10) == 0)) {
    if (*(char *)(iVar1 + 0x25) == '\x01') {
      iVar2 = FUN_0041add0(*(int *)(iVar1 + 0x1c));
      *(int *)(iVar1 + 0x10) = iVar2;
    }
    else if (*(char *)(iVar1 + 0x25) == '\x02') {
      uVar3 = FUN_0041b138(*(int *)(iVar1 + 0x1c));
      *(undefined4 *)(iVar1 + 0x10) = uVar3;
    }
  }
  return;
}

