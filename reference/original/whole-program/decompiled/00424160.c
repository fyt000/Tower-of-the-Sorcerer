/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00424160.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_00424160(int *param_1,char param_2)

{
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  *(undefined *)((int)param_1 + 0x7d) = 0;
  FUN_00425618((int)param_1);
  FUN_0040e4fc(param_1,'\0');
  FUN_00424e8c((int)param_1,extraout_EDX,extraout_ECX,0x4244d8,(int)param_1);
  if (((HWND)param_1[8] != (HWND)0x0) && (*(char *)((int)param_1 + 0x7e) != '\0')) {
    if (DAT_0048a694 != '\0') {
      SendMessageA((HWND)param_1[8],0x80,1,0);
    }
    DestroyWindow((HWND)param_1[8]);
  }
  if (param_1[9] != 0) {
    FUN_0041fde4(param_1[9]);
  }
  FUN_0041fd00();
  FUN_00402c34((int *)param_1[0x20]);
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

