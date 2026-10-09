/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b04c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040b04c(int param_1,undefined4 param_2,undefined *param_3,ushort param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined *extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 *in_FS_OFFSET;
  undefined4 in_stack_ffffffd4;
  undefined4 in_stack_ffffffd8;
  undefined *local_10;
  undefined local_c;
  char local_5;
  
  if ((char)param_2 != '\0') {
    param_1 = FUN_00402e0c(param_1,param_2,param_3,in_stack_ffffffd4,in_stack_ffffffd8);
    param_3 = extraout_ECX;
    param_2 = extraout_EDX;
  }
  local_5 = (char)param_2;
  local_10 = param_3;
  if (param_4 == 0xffff) {
    iVar1 = FUN_00405cc4(param_3);
    *(int *)(param_1 + 4) = iVar1;
    if (iVar1 < 0) {
      local_c = 0xb;
      uVar2 = FUN_0040753c(0x4087f0,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xf001,0,
                           &local_10);
      FUN_004031f8(uVar2);
    }
  }
  else {
    uVar2 = FUN_00405c84(param_3,(uint)param_4);
    *(undefined4 *)(param_1 + 4) = uVar2;
    if (*(int *)(param_1 + 4) < 0) {
      local_c = 0xb;
      uVar2 = FUN_0040753c(0x408834,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),0xf002,0,
                           &local_10);
      FUN_004031f8(uVar2);
    }
  }
  if (local_5 != '\0') {
    *in_FS_OFFSET = in_stack_ffffffd4;
  }
  return param_1;
}

