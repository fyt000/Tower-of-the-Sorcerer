/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047d324.
 * Inferred types and shared tails require assembly review. */

void FUN_0047d324(int param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0047d44a;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  iVar2 = FUN_0042cec8((uint *)"Save options. Is it true?",CONCAT31((int3)((uint)param_2 >> 8),2),
                       DAT_0047d458,0);
  if (iVar2 == 6) {
    iVar2 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x3c8) + 0x44));
    DAT_00489b9c = (undefined)iVar2;
    iVar2 = FUN_00419e30(*(int *)(*(int *)(param_1 + 0x1c8) + 0x44));
    DAT_00489b9d = (undefined)iVar2;
    DAT_00489b9e = 0;
    DAT_00489b9f = 2;
    if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
      DAT_00489b9f = 1;
    }
    if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
      DAT_00489b9f = 3;
    }
    piVar1 = *(int **)(*(int *)(param_1 + 0x444) + 0x118);
    (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_8);
    FUN_0040369c((int *)&DAT_0048c5d4,local_8,(undefined4 *)"\\option.dat");
    FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
    FUN_004045a4((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
    FUN_00402710();
    FUN_00404254((HANDLE *)&DAT_0048c600,&DAT_00489b9c,10,(uint *)0x0);
    FUN_00402710();
    FUN_004042b8(&DAT_0048c600);
    FUN_00402710();
    FUN_0042cf78((uint *)"Done.");
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0047d451;
  puStack_1c = (undefined *)0x47d449;
  FUN_004034dc((int *)&local_8);
  return;
}

