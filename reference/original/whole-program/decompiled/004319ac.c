/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004319ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004319ac(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  MCIERROR MVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iStack_10;
  int iStack_c;
  
  FUN_00430e1c((int)param_1,param_2);
  if (*(char *)((int)param_1 + 0x1db) != '\0') {
    if (*(char *)((int)param_1 + 0x212) != '\0') {
      iVar1 = FUN_004320b0((int)param_1);
      iVar2 = FUN_00431fdc((int)param_1,extraout_EDX);
      if (iVar1 == iVar2) {
        FUN_00431bf8((int)param_1,extraout_EDX_00);
      }
    }
    param_1[0x77] = 0;
    if (*(char *)((int)param_1 + 0x1e2) == '\0') {
      param_1[0x77] = 2;
    }
    else {
      if (*(char *)(param_1 + 0x78) != '\0') {
        param_1[0x77] = 2;
      }
      *(undefined *)((int)param_1 + 0x1e2) = 0;
    }
    if (*(char *)((int)param_1 + 0x1e3) != '\0') {
      if (*(char *)((int)param_1 + 0x1e1) != '\0') {
        param_1[0x77] = param_1[0x77] | 1;
      }
      *(undefined *)((int)param_1 + 0x1e3) = 0;
    }
    param_1[0x77] = param_1[0x77] | 0x20000;
    iStack_c = param_1[0x7d];
    iStack_10 = FUN_00416cbc(param_1);
    MVar3 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x80e,param_1[0x77],
                            (DWORD_PTR)&iStack_10);
    param_1[0x7e] = MVar3;
  }
  return;
}

