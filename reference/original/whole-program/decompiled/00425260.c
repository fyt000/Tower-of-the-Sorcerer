/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00425260.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00425260(int param_1,char param_2)

{
  int *piVar1;
  undefined3 in_register_00000009;
  
  if (param_2 != *(char *)(param_1 + 100)) {
    *(char *)(param_1 + 100) = param_2;
    if (param_2 == '\0') {
      FUN_00402c34(*(int **)(param_1 + 0x60));
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
    else {
      piVar1 = (int *)(**(code **)(PTR_PTR_FUN_00489580 + 0x24))
                                (PTR_PTR_FUN_00489580,CONCAT31(in_register_00000009,1),param_1);
      *(int **)(param_1 + 0x60) = piVar1;
      FUN_004136e8(piVar1,*(int *)(param_1 + 0x3c));
    }
  }
  return;
}

