/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406ad8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406ad8(int param_1,char param_2,int *param_3)

{
  byte bVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  undefined4 *local_14;
  byte local_d;
  int *local_c;
  char local_5;
  
  puStack_24 = &stack0xfffffffc;
  local_14 = (undefined4 *)0x0;
  puStack_28 = &LAB_00406cc1;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  iVar5 = 1;
  local_c = param_3;
  local_5 = param_2;
  FUN_004034dc(param_3);
  local_d = 0;
  while( true ) {
    iVar3 = FUN_00403650(param_1);
    if (iVar3 < iVar5) break;
    bVar1 = *(byte *)(param_1 + -1 + iVar5);
    uVar4 = (uint)bVar1;
    bVar2 = FUN_00406054(bVar1);
    if ((short)CONCAT31(extraout_var,bVar2) == 0) {
      if (bVar1 == 0x27) {
        local_d = local_d ^ 1;
        FUN_004035ec((int *)&local_14,uVar4);
        FUN_00403658(local_c,local_14);
      }
      else if (local_d == 0) {
        FUN_00403854(param_1,iVar5,2,(int *)&local_14);
        iVar3 = FUN_00405a34((undefined *)local_14,&DAT_00406cd8);
        if (iVar3 == 0) {
          FUN_00403658(local_c,(undefined4 *)&DAT_00406ce4);
          iVar5 = iVar5 + 1;
        }
        else {
          FUN_00403854(param_1,iVar5,1,(int *)&local_14);
          iVar3 = FUN_00405a34((undefined *)local_14,&DAT_00406cf4);
          if (iVar3 == 0) {
            FUN_00403658(local_c,(undefined4 *)&DAT_00406d00);
          }
          else if (bVar1 == DAT_0048a55c) {
            FUN_00403854(param_1,iVar5 + 1,2,(int *)&local_14);
            iVar3 = FUN_00405a34((undefined *)local_14,&DAT_00406d0c);
            if (iVar3 == 0) {
              if (local_5 != '\0') {
                FUN_00403658(local_c,(undefined4 *)&DAT_00406d18);
              }
              iVar5 = iVar5 + 2;
            }
            else {
              FUN_00403658(local_c,(undefined4 *)&DAT_00406d24);
            }
          }
          else {
            FUN_00403854(param_1,iVar5,2,(int *)&local_14);
            iVar3 = FUN_00405a34((undefined *)local_14,&DAT_00406d0c);
            if (iVar3 == 0) {
              if (local_5 != '\0') {
                FUN_00403658(local_c,(undefined4 *)&DAT_00406d0c);
              }
              iVar5 = iVar5 + 1;
            }
            else {
              FUN_004035ec((int *)&local_14,uVar4);
              FUN_00403658(local_c,local_14);
            }
          }
        }
      }
      else {
        FUN_004035ec((int *)&local_14,uVar4);
        FUN_00403658(local_c,local_14);
      }
      iVar5 = iVar5 + 1;
    }
    else {
      FUN_00403854(param_1,iVar5,2,(int *)&local_14);
      FUN_00403658(local_c,local_14);
      iVar5 = iVar5 + 2;
    }
  }
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_00406cc8;
  puStack_28 = (undefined *)0x406cc0;
  FUN_004034dc((int *)&local_14);
  return;
}

