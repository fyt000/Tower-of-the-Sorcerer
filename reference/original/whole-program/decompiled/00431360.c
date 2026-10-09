/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431360.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00431360(int *param_1,undefined4 param_2)

{
  MCIERROR MVar1;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  
  FUN_00430e1c((int)param_1,param_2);
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
    iStack_c = param_1[0x7c];
    *(undefined *)(param_1 + 0x79) = 0;
  }
  if (*(char *)((int)param_1 + 0x1e5) != '\0') {
    param_1[0x77] = param_1[0x77] | 8;
    iStack_8 = param_1[0x7b];
    *(undefined *)((int)param_1 + 0x1e5) = 0;
  }
  iStack_10 = FUN_00416cbc(param_1);
  MVar1 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x80f,param_1[0x77],
                          (DWORD_PTR)&iStack_10);
  param_1[0x7e] = MVar1;
  return;
}

