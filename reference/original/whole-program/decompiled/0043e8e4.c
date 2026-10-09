/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043e8e4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043e8e4(undefined4 param_1,undefined *param_2,int *param_3)

{
  DWORD DVar1;
  undefined4 *in_FS_OFFSET;
  bool bVar2;
  undefined4 uStack_188;
  undefined *puStack_184;
  undefined *puStack_180;
  undefined4 uStack_17c;
  undefined *puStack_178;
  undefined *puStack_174;
  undefined *local_164;
  WORD local_160 [4];
  uint local_158;
  uint *local_154;
  int local_8;
  
  local_164 = (undefined *)0x0;
  puStack_174 = (undefined *)0x43e90c;
  FUN_004039ac((int)local_160,0x405340);
  puStack_178 = &LAB_0043e9f3;
  uStack_17c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_17c;
  local_8 = 0;
  puStack_180 = (undefined *)0x43e931;
  puStack_174 = &stack0xfffffffc;
  FUN_0043d5cc(param_2,&DAT_0043ea0c,(int *)&local_164);
  puStack_180 = (undefined *)0x43e947;
  DVar1 = FUN_00405e30(local_164,0x10,local_160);
  puStack_184 = &LAB_0043e9c3;
  uStack_188 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_188;
  puStack_180 = &stack0xfffffffc;
  while (DVar1 == 0) {
    bVar2 = (local_158 & 0x10) == 0x10;
    if (((bVar2) && (FUN_00403760(local_154,(uint *)&DAT_0043ea18), !bVar2)) &&
       (FUN_00403760(local_154,(uint *)&DAT_0043ea24), !bVar2)) {
      (**(code **)(*param_3 + 0x2c))(param_3,local_154);
      local_8 = local_8 + 1;
    }
    DVar1 = FUN_00405e7c(local_160);
  }
  *in_FS_OFFSET = uStack_188;
  puStack_180 = &LAB_0043e9ca;
  puStack_184 = (undefined *)0x43e9c2;
  FUN_00405ea0((int)local_160);
  return;
}

