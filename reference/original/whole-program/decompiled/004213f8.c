/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004213f8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004213f8(int param_1,undefined4 param_2,undefined4 param_3,code *param_4,
                  undefined4 param_5)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int iStack_c;
  
  root_00417098(param_1,param_2,param_3,param_4,param_5);
  iVar2 = FUN_0040ea78(param_1);
  if (-1 < iVar2 + -1) {
    iStack_c = 0;
    do {
      piVar3 = (int *)FUN_0040ea54(param_1,iStack_c);
      cVar1 = FUN_00402cdc(piVar3,extraout_EDX,extraout_ECX);
      if (cVar1 == '\0') {
        (*param_4)(param_5,piVar3);
      }
      iStack_c = iStack_c + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

