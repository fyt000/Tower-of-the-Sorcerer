/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043d634.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043d634(uint **param_1)

{
  char cVar1;
  int iVar2;
  undefined in_ZF;
  
  FUN_00403760(*param_1,(uint *)&DAT_0043d6dc);
  if (!(bool)in_ZF) {
    cVar1 = *(char *)*param_1;
    if (cVar1 == '\\') {
      FUN_00403894((int *)param_1,1,1);
    }
    if (*(char *)*param_1 == '.') {
      FUN_00403894((int *)param_1,1,4);
    }
    iVar2 = FUN_0040edcc((uint *)&DAT_0043d6dc,(int)*param_1);
    if (iVar2 == 0) {
      FUN_004034dc((int *)param_1);
    }
    else {
      FUN_00403894((int *)param_1,1,iVar2);
      FUN_0040369c((int *)param_1,(undefined4 *)&DAT_0043d6e8,*param_1);
    }
    if (cVar1 == '\\') {
      FUN_0040369c((int *)param_1,(undefined4 *)&DAT_0043d6dc,*param_1);
    }
    return;
  }
  FUN_004034dc((int *)param_1);
  return;
}

