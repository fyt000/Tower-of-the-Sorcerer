/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f188.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** FUN_0042f188(int **param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  HDC hdc;
  int *extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe0;
  undefined4 in_stack_ffffffe4;
  
  if ((char)param_2 != '\0') {
    param_1 = (int **)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe0,in_stack_ffffffe4)
    ;
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_0042905c((int *)param_1,0,param_3);
  piVar1 = (int *)FUN_0042de28(0x42d3e0,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),param_1,0);
  param_1[0x4c] = piVar1;
  piVar1 = (int *)FUN_0042de28(0x42d3e0,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),param_1,1);
  param_1[0x4d] = piVar1;
  piVar1 = (int *)FUN_0042e360(0x42d458,CONCAT31((int3)((uint)extraout_EDX_02 >> 8),1),param_1);
  param_1[0x4e] = piVar1;
  piVar1 = (int *)FUN_00402c0c(0x42e76c,CONCAT31((int3)((uint)extraout_EDX_03 >> 8),1),
                               extraout_ECX_00);
  param_1[0x50] = piVar1;
  piVar1[2] = (int)param_1;
  FUN_00416df4((int *)param_1,'\x01');
  FUN_004130d8((int *)param_1,0xb9);
  FUN_004130f8((int *)param_1,0x59);
  FUN_00428648((int *)param_1,'\0');
  *(undefined *)(param_1 + 0x54) = 1;
  FUN_0042f530(param_1,'\x01');
  hdc = GetDC((HWND)0x0);
  piVar1 = (int *)GetDeviceCaps(hdc,0x5a);
  param_1[0x4f] = piVar1;
  param_1[0x55] = (int *)&PTR_FUN_0042d5d0;
  ReleaseDC((HWND)0x0,hdc);
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe0;
  }
  return param_1;
}

