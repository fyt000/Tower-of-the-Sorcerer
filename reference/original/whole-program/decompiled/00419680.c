/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419680.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419680(int param_1,undefined4 *param_2)

{
  int *piVar1;
  int *piVar2;
  
  if ((param_2 != (undefined4 *)0x0) && (param_2[1] = param_2[1] + -1, param_2[1] == 0)) {
    if ((HGDIOBJ)param_2[2] != (HGDIOBJ)0x0) {
      DeleteObject((HGDIOBJ)param_2[2]);
    }
    piVar1 = *(int **)(param_1 + 4);
    if (param_2 == *(int **)(param_1 + 4)) {
      *(undefined4 *)(param_1 + 4) = *param_2;
    }
    else {
      do {
        piVar2 = piVar1;
        piVar1 = (int *)*piVar2;
      } while (param_2 != piVar1);
      *piVar2 = *param_2;
    }
    FUN_00402668((int)param_2);
  }
  return;
}

