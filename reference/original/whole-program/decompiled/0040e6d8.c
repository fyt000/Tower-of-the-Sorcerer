/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e6d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e6d8(int param_1)

{
  int *piVar1;
  
  while (*(undefined4 **)(param_1 + 0x10) != (undefined4 *)0x0) {
    piVar1 = (int *)FUN_00409afc(*(undefined4 **)(param_1 + 0x10));
    FUN_0040e628(param_1,(int)piVar1);
    (**(code **)(*piVar1 + -4))(piVar1,1);
  }
  return;
}

