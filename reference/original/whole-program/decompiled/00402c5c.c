/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402c5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00402c5c(int *param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = *param_1;
  do {
    piVar1 = (int *)(iVar2 + -0x30);
    iVar2 = *(int *)(iVar2 + -0x14);
    if (*piVar1 != 0) {
      FUN_00403a64((int)param_1,*piVar1);
    }
  } while (iVar2 != 0);
  return;
}

