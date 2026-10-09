/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040352c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040352c(int *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != (undefined4 *)0x0) {
    iVar2 = param_2[-2] + 1;
    if (iVar2 == 0 || SCARRY4(param_2[-2],1) != iVar2 < 0) {
      puVar1 = FUN_00403598(param_2[-1]);
      FUN_00402870(param_2,puVar1,param_2[-1]);
      param_2 = puVar1;
    }
    else {
      param_2[-2] = iVar2;
    }
  }
  LOCK();
  iVar2 = *param_1;
  *param_1 = (int)param_2;
  UNLOCK();
  if (iVar2 != 0) {
    iVar3 = *(int *)(iVar2 + -8) + -1;
    if ((0 < *(int *)(iVar2 + -8)) && (*(int *)(iVar2 + -8) = iVar3, iVar3 == 0)) {
      FUN_00402668(iVar2 + -8);
    }
  }
  return;
}

