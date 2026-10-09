/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403608.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403608(int *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  
  uVar1 = 0;
  puVar2 = param_2;
  if (param_2 != (undefined4 *)0x0) {
    for (; *(char *)puVar2 != '\0'; puVar2 = puVar2 + 1) {
      if (*(char *)((int)puVar2 + 1) == '\0') {
LAB_00403629:
        puVar2 = (undefined4 *)((int)puVar2 + 1);
        break;
      }
      if (*(char *)((int)puVar2 + 2) == '\0') {
LAB_00403628:
        puVar2 = (undefined4 *)((int)puVar2 + 1);
        goto LAB_00403629;
      }
      if (*(char *)((int)puVar2 + 3) == '\0') {
        puVar2 = (undefined4 *)((int)puVar2 + 1);
        goto LAB_00403628;
      }
    }
    uVar1 = (int)puVar2 - (int)param_2;
  }
  FUN_004035bc(param_1,param_2,uVar1);
  return;
}

