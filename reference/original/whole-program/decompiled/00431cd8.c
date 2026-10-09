/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431cd8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431cd8(int param_1,int *param_2)

{
  MCIERROR MVar1;
  undefined4 extraout_ECX;
  undefined auStack_1c [4];
  int local_18;
  
  if (((param_2 == (int *)0x0) || (*(char *)(param_1 + 0x1d5) == '\0')) ||
     (*(char *)(param_1 + 0x1db) == '\0')) {
    *(int **)(param_1 + 0x200) = param_2;
  }
  else {
    *(undefined4 *)(param_1 + 0x1dc) = 0x10002;
    local_18 = FUN_00416cbc(param_2);
    MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x841,*(DWORD_PTR *)(param_1 + 0x1dc)
                            ,(DWORD_PTR)auStack_1c);
    *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
    if (MVar1 == 0) {
      *(int **)(param_1 + 0x200) = param_2;
      FUN_0040e570((int)param_2,param_1,extraout_ECX);
    }
    else {
      *(undefined4 *)(param_1 + 0x200) = 0;
    }
  }
  return;
}

