/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431250.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431250(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  MCIERROR MVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int local_14;
  int local_10;
  int local_c;
  
  FUN_00430e1c((int)param_1,param_2);
  if (*(char *)((int)param_1 + 0x212) != '\0') {
    iVar1 = FUN_004320b0((int)param_1);
    iVar2 = FUN_00431fdc((int)param_1,extraout_EDX);
    if (((iVar1 == iVar2) && (*(char *)(param_1 + 0x79) == '\0')) &&
       (*(char *)((int)param_1 + 0x1e5) == '\0')) {
      FUN_00431bf8((int)param_1,extraout_EDX_00);
    }
  }
  param_1[0x77] = 0;
  if (*(char *)((int)param_1 + 0x1e3) == '\0') {
    param_1[0x77] = 1;
  }
  else {
    if (*(char *)((int)param_1 + 0x1e1) != '\0') {
      param_1[0x77] = 1;
    }
    *(undefined *)((int)param_1 + 0x1e3) = 0;
  }
  if (*(char *)((int)param_1 + 0x1e2) != '\0') {
    if (*(char *)(param_1 + 0x78) != '\0') {
      param_1[0x77] = param_1[0x77] | 2;
    }
    *(undefined *)((int)param_1 + 0x1e2) = 0;
  }
  if (*(char *)(param_1 + 0x79) != '\0') {
    param_1[0x77] = param_1[0x77] | 4;
    local_10 = param_1[0x7c];
    *(undefined *)(param_1 + 0x79) = 0;
  }
  if (*(char *)((int)param_1 + 0x1e5) != '\0') {
    param_1[0x77] = param_1[0x77] | 8;
    local_c = param_1[0x7b];
    *(undefined *)((int)param_1 + 0x1e5) = 0;
  }
  local_14 = FUN_00416cbc(param_1);
  MVar3 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x806,param_1[0x77],
                          (DWORD_PTR)&local_14);
  param_1[0x7e] = MVar3;
  return;
}

