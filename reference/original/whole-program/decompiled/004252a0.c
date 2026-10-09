/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004252a0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004252a0(int param_1)

{
  int *piVar1;
  HANDLE pvVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  int local_18;
  uint *local_14;
  char local_d;
  tagPOINT local_c;
  
  puStack_28 = &stack0xfffffffc;
  local_14 = (uint *)0x0;
  local_18 = 0;
  puStack_2c = &LAB_004253b9;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  GetCursorPos(&local_c);
  piVar1 = FUN_00412be8(&local_c,1);
  if ((piVar1 != (int *)0x0) && ((*(byte *)(piVar1 + 7) & 0x10) != 0)) {
    piVar1 = (int *)0x0;
  }
  pvVar2 = FUN_00412488();
  if (piVar1 != *(int **)(param_1 + 0x2c)) {
    if (((*(int *)(param_1 + 0x2c) != 0) && (pvVar2 == (HANDLE)0x0)) ||
       ((pvVar2 != (HANDLE)0x0 && (pvVar2 == *(HANDLE *)(param_1 + 0x2c))))) {
      FUN_00413cb8(*(int **)(param_1 + 0x2c),0xb014,0,0);
    }
    *(int **)(param_1 + 0x2c) = piVar1;
    if (((*(int *)(param_1 + 0x2c) != 0) && (pvVar2 == (HANDLE)0x0)) ||
       ((pvVar2 != (HANDLE)0x0 && (pvVar2 == *(HANDLE *)(param_1 + 0x2c))))) {
      FUN_00413cb8(*(int **)(param_1 + 0x2c),0xb013,0,0);
    }
  }
  if ((*(char *)(param_1 + 100) != '\0') &&
     ((*(int *)(param_1 + 0x2c) == 0 || (*(int *)(param_1 + 0x2c) == *(int *)(param_1 + 0x60))))) {
    FUN_00425618(param_1);
  }
  FUN_00423dd8((int)piVar1,&local_18);
  FUN_00412444(local_18,(int *)&local_14);
  FUN_00425454(DAT_0048a6f8,local_14);
  local_d = '\x01';
  if (*(short *)(param_1 + 0xae) != 0) {
    (**(code **)(param_1 + 0xac))(*(undefined4 *)(param_1 + 0xb0),param_1,&local_d);
  }
  if (local_d != '\0') {
    WaitMessage();
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_004253c0;
  puStack_2c = (undefined *)0x4253b8;
  FUN_004034fc(&local_18,2);
  return;
}

