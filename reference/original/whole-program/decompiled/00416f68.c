/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416f68.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00416f68(int *param_1,int param_2,undefined4 param_3,char param_4,char param_5)

{
  int *piVar1;
  int **ppiVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  int iStack_10;
  int **ppiStack_c;
  
  ppiStack_c = (int **)0x0;
  puStack_24 = (undefined *)0x416f89;
  piVar1 = (int *)FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  puStack_28 = &UNK_00417057;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  puStack_24 = &stack0xfffffffc;
  FUN_00402cdc(param_1,piVar1,extraout_ECX);
  if (0 < piVar1[2]) {
    iStack_10 = FUN_00409a88((int)piVar1,param_2);
    iVar4 = iStack_10;
    if (iStack_10 == -1) {
      if ((char)param_3 == '\0') {
        iStack_10 = 0;
        iVar4 = iStack_10;
      }
      else {
        iStack_10 = piVar1[2] + -1;
        iVar4 = iStack_10;
      }
    }
    do {
      if ((char)param_3 == '\0') {
        if (iVar4 == 0) {
          iVar4 = piVar1[2];
        }
        iVar4 = iVar4 + -1;
      }
      else {
        iVar4 = iVar4 + 1;
        if (iVar4 == piVar1[2]) {
          iVar4 = 0;
        }
      }
      ppiVar2 = (int **)FUN_00409a40(piVar1,iVar4);
      uVar3 = FUN_00416c2c(ppiVar2);
      if ((((char)uVar3 != '\0') && ((param_5 == '\0' || (*(char *)(ppiVar2 + 0x31) != '\0')))) &&
         ((param_4 == '\0' || (param_1 == ppiVar2[8])))) {
        ppiStack_c = ppiVar2;
      }
    } while ((ppiStack_c == (int **)0x0) && (iVar4 != iStack_10));
  }
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &UNK_0041705e;
  puStack_28 = (undefined *)0x417056;
  (**(code **)(*piVar1 + -4))(piVar1,1);
  return;
}

