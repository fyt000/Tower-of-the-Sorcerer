/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a234.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a234(int **param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0xf) == '\x01') && (*(char *)((int)param_1 + 0x109) == '\x02')) {
    iVar2 = GetSystemMetrics(0x15);
    if ((int)*(short *)(param_2 + 8) < (int)param_1[0xb] - iVar2) {
      (*(code *)(*param_1)[0x20])();
      FUN_00413ad4(param_1,'\0');
      return;
    }
  }
  FUN_00413f58(param_1,param_2);
  bVar1 = FUN_00413748(param_1);
  if (bVar1) {
    iVar2 = FUN_00420024(param_1);
    if (param_1 != *(int ***)(iVar2 + 0x10c)) {
      FUN_00413758(param_1,'\0');
    }
  }
  return;
}

