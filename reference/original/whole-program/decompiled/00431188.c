/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431188.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431188(int *param_1,undefined4 param_2,int param_3)

{
  MCIERROR MVar1;
  int local_c;
  
  if (*(short *)((int)param_1 + 0x1e6) != 0) {
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
    local_c = param_3;
    local_c = FUN_00416cbc(param_1);
    MVar1 = mciSendCommandA((uint)*(ushort *)((int)param_1 + 0x1e6),0x804,param_1[0x77],
                            (DWORD_PTR)&local_c);
    param_1[0x7e] = MVar1;
    if (MVar1 == 0) {
      *(undefined *)((int)param_1 + 0x1d5) = 0;
      *(undefined2 *)((int)param_1 + 0x1e6) = 0;
      *(undefined2 *)((int)param_1 + 0x19a) = DAT_0043124c;
      FUN_0043025c(param_1);
    }
  }
  return;
}

