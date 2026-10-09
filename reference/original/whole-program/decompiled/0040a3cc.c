/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a3cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a3cc(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  int iStack_1c;
  undefined4 *puStack_18;
  int iStack_14;
  int iStack_10;
  int *piStack_c;
  int *piStack_8;
  
  puStack_2c = &stack0xfffffffc;
  iStack_1c = 0;
  puStack_18 = (undefined4 *)0x0;
  puStack_30 = &LAB_0040a4a3;
  uStack_34 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_34;
  piStack_c = param_2;
  piStack_8 = param_1;
  iVar1 = (**(code **)(*param_1 + 0x10))();
  uVar3 = 0;
  iStack_14 = iVar1;
  if (-1 < iVar1 + -1) {
    iStack_10 = 0;
    do {
      (**(code **)(*piStack_8 + 0xc))(piStack_8,iStack_10,&iStack_1c);
      iVar2 = FUN_00403650(iStack_1c);
      uVar3 = uVar3 + iVar2 + 2;
      iStack_10 = iStack_10 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  FUN_004035bc(piStack_c,(undefined4 *)0x0,uVar3);
  puVar4 = (undefined4 *)*piStack_c;
  if (-1 < iStack_14 + -1) {
    iStack_10 = 0;
    iVar1 = iStack_14;
    do {
      (**(code **)(*piStack_8 + 0xc))(piStack_8,iStack_10,&puStack_18);
      uVar3 = FUN_00403650((int)puStack_18);
      if (uVar3 != 0) {
        FUN_00402870(puStack_18,puVar4,uVar3);
        puVar4 = (undefined4 *)((int)puVar4 + uVar3);
      }
      *(undefined *)puVar4 = 0xd;
      *(undefined *)((int)puVar4 + 1) = 10;
      puVar4 = (undefined4 *)((int)puVar4 + 2);
      iStack_10 = iStack_10 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  *in_FS_OFFSET = uStack_34;
  puStack_2c = &LAB_0040a4aa;
  puStack_30 = (undefined *)0x40a4a2;
  FUN_004034fc(&iStack_1c,2);
  return;
}

