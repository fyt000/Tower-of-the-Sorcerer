/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dae4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040dae4(int param_1,int param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  int iVar4;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined *local_10;
  int local_c;
  int local_8;
  
  puStack_20 = &stack0xfffffffc;
  uVar3 = 0;
  local_10 = (undefined *)0x0;
  puStack_24 = &LAB_0040db71;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  iVar4 = DAT_004891c8[2];
  local_c = param_2;
  local_8 = param_1;
  if (-1 < iVar4 + -1) {
    iVar5 = 0;
    puStack_20 = &stack0xfffffffc;
    do {
      iVar2 = FUN_00409a40(DAT_004891c8,iVar5);
      if (local_8 == *(int *)(iVar2 + 4)) {
        cVar1 = (**(code **)(iVar2 + 0xc))(local_c,&local_10);
        uVar3 = extraout_ECX_00;
        if (cVar1 != '\0') {
          FUN_0040d784(*(int *)(param_4 + -4),local_10);
          goto LAB_0040db5b;
        }
        break;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + -1;
      uVar3 = extraout_ECX;
    } while (iVar4 != 0);
  }
  FUN_0040d820(*(int *)(param_4 + -4),local_c,uVar3);
LAB_0040db5b:
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0040db78;
  puStack_24 = (undefined *)0x40db70;
  FUN_004034dc((int *)&local_10);
  return;
}

