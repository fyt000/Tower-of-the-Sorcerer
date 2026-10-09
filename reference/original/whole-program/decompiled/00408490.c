/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408490.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408490(int *param_1,int param_2,int *param_3)

{
  code *pcVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_2 + 0x10);
  if (*(int **)(param_2 + 0x10) == (int *)0x80000000) {
    piVar2 = param_3;
  }
  pcVar1 = *(code **)(param_2 + 4);
  if (*(byte *)(param_2 + 7) != 0xff) {
    if (0xfd < *(byte *)(param_2 + 7)) {
      (**(code **)((int)(short)pcVar1 + *param_1))();
      return;
    }
    (*pcVar1)(param_1,piVar2);
    return;
  }
  FUN_0040847c(param_3,*(undefined4 **)((int)param_1 + ((uint)pcVar1 & 0xffffff)));
  return;
}

