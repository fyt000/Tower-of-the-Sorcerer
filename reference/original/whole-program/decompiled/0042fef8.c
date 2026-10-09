/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042fef8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_0042fef8(int *param_1,undefined4 param_2,int *param_3)

{
  byte bVar1;
  int *extraout_ECX;
  undefined4 extraout_EDX;
  uint uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffe4;
  undefined4 in_stack_ffffffe8;
  
  if ((char)param_2 != '\0') {
    param_1 = (int *)FUN_00402e0c((int)param_1,param_2,param_3,in_stack_ffffffe4,in_stack_ffffffe8);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  FUN_00417538((int)param_1,0,param_3);
  *(ushort *)(param_1 + 0xd) = DAT_0042ffd4 | *(ushort *)(param_1 + 0xd);
  FUN_00430048((int)param_1);
  *(undefined2 *)(param_1 + 0x65) = DAT_0042ffd8;
  *(undefined2 *)((int)param_1 + 0x196) = DAT_0042ffd8;
  *(undefined2 *)(param_1 + 0x66) = DAT_0042ffd8;
  bVar1 = 0;
  do {
    uVar2 = (uint)bVar1;
    *(undefined *)(param_1 + uVar2 * 4 + 0x41) = 1;
    *(undefined *)((int)param_1 + uVar2 * 0x10 + 0x105) = 1;
    *(undefined *)((int)param_1 + uVar2 * 0x10 + 0x106) = 1;
    *(undefined *)((int)param_1 + uVar2 * 0x10 + 0x107) = 0;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 9);
  FUN_004130d8(param_1,0xf0);
  FUN_004130f8(param_1,0x1e);
  *(undefined *)(param_1 + 0x75) = 0;
  *(undefined *)(param_1 + 0x84) = 1;
  *(undefined *)((int)param_1 + 0x211) = 0;
  *(undefined *)((int)param_1 + 0x212) = 1;
  *(undefined *)(param_1 + 0x7a) = 0;
  if ((char)param_2 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffe4;
  }
  return param_1;
}

