/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043d6f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043d6f0(int param_1,int *param_2,int param_3,int *param_4)

{
  int iVar1;
  LONG LVar2;
  int *in_FS_OFFSET;
  bool bVar3;
  int iStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  int local_14;
  uint *local_10;
  int local_c;
  int local_8;
  
  puStack_24 = &stack0xfffffffc;
  local_c = 0;
  local_10 = (uint *)0x0;
  local_14 = 0;
  puStack_28 = &LAB_0043d805;
  iStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = (int)&iStack_2c;
  local_8 = param_1;
  FUN_00403570(param_4,param_1);
  FUN_00405eb0(*param_4,(int *)&local_10);
  FUN_00405f98(*param_4,&local_14);
  iVar1 = FUN_00403650((int)local_10);
  if ((iVar1 < 2) || (*(char *)((int)local_10 + 1) != ':')) {
    FUN_004034dc(&local_c);
  }
  else {
    FUN_00403854((int)local_10,1,2,&local_c);
    FUN_00403894((int *)&local_10,1,2);
  }
  while ((local_10 != (uint *)0x0 || (local_c != 0))) {
    LVar2 = FUN_0041a830(param_2,(undefined *)*param_4);
    bVar3 = param_3 == LVar2;
    if (LVar2 <= param_3) break;
    FUN_00403760(local_10,(uint *)"\\...\\");
    if (bVar3) {
      FUN_004034dc(&local_c);
      FUN_00403570((int *)&local_10,0x43d830);
    }
    else if (local_10 == (uint *)0x0) {
      FUN_004034dc(&local_c);
    }
    else {
      FUN_0043d634(&local_10);
    }
    iStack_2c = local_14;
    FUN_00403710(param_4,3);
  }
  *in_FS_OFFSET = iStack_2c;
  puStack_24 = &LAB_0043d80c;
  puStack_28 = (undefined *)0x43d804;
  FUN_004034fc(&local_14,3);
  return;
}

