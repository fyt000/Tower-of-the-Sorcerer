/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414c9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414c9c(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0xb0);
  if (puVar1 == (undefined4 *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar2 = puVar1[2];
  }
  if (param_2 < iVar2) {
    FUN_00409a40(puVar1,param_2);
    return;
  }
  FUN_00409a40(*(undefined4 **)(param_1 + 0xb4),param_2 - iVar2);
  return;
}

