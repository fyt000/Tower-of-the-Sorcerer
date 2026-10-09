/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403658.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403658(int *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  if (param_2 == (undefined4 *)0x0) {
    return;
  }
  puVar2 = (undefined4 *)*param_1;
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = puVar2[-1];
    if (param_2 == puVar2) {
      FUN_00403924(param_1,param_2[-1] + uVar1);
      param_2 = (undefined4 *)*param_1;
      uVar5 = uVar1;
    }
    else {
      FUN_00403924(param_1,param_2[-1] + uVar1);
      uVar5 = param_2[-1];
    }
    FUN_00402870(param_2,(undefined4 *)(*param_1 + uVar1),uVar5);
    return;
  }
  if (param_2 != (undefined4 *)0x0) {
    iVar3 = param_2[-2] + 1;
    if (iVar3 == 0 || SCARRY4(param_2[-2],1) != iVar3 < 0) {
      puVar2 = FUN_00403598(param_2[-1]);
      FUN_00402870(param_2,puVar2,param_2[-1]);
      param_2 = puVar2;
    }
    else {
      param_2[-2] = iVar3;
    }
  }
  LOCK();
  iVar3 = *param_1;
  *param_1 = (int)param_2;
  UNLOCK();
  if (iVar3 != 0) {
    iVar4 = *(int *)(iVar3 + -8) + -1;
    if ((0 < *(int *)(iVar3 + -8)) && (*(int *)(iVar3 + -8) = iVar4, iVar4 == 0)) {
      FUN_00402668(iVar3 + -8);
    }
  }
  return;
}

