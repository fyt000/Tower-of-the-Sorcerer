/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403924.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403924(int *param_1,uint param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iStack_10;
  
  puVar3 = (undefined4 *)0x0;
  if (param_2 != 0) {
    iStack_10 = *param_1;
    if ((iStack_10 != 0) && (*(int *)(iStack_10 + -8) == 1)) {
      iStack_10 = iStack_10 + -8;
      FUN_00402680(&iStack_10,param_2 + 9);
      *param_1 = iStack_10 + 8;
      *(uint *)(iStack_10 + 4) = param_2;
      *(undefined *)(iStack_10 + 8 + param_2) = 0;
      return;
    }
    iStack_10 = 0x403961;
    puVar3 = FUN_00403598(param_2);
    puVar1 = (undefined4 *)*param_1;
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = puVar1[-1];
      if ((int)param_2 <= (int)puVar1[-1]) {
        uVar2 = param_2;
      }
      iStack_10 = 0x403979;
      FUN_00402870(puVar1,puVar3,uVar2);
    }
  }
  iStack_10 = 0x403980;
  FUN_004034dc(param_1);
  *param_1 = (int)puVar3;
  return;
}

