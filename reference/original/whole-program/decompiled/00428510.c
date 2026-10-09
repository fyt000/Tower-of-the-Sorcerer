/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428510.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00428510(int *param_1,int param_2)

{
  int **ppiVar1;
  char cVar2;
  undefined2 extraout_var;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  char *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (char *)0x0;
  puStack_1c = &LAB_00428594;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  if (((param_1[0x2b] != 0) && (*(char *)(param_1 + 0xe) != '\0')) &&
     (*(char *)((int)param_1 + 0xb3) != '\0')) {
    FUN_004135a4(param_1,(int *)&local_8);
    cVar2 = FUN_0041ff5c(CONCAT22(extraout_var,*(undefined2 *)(param_2 + 4)),local_8);
    if (cVar2 != '\0') {
      ppiVar1 = (int **)param_1[0x2b];
      uVar3 = FUN_00416c2c(ppiVar1);
      if ((char)uVar3 != '\0') {
        (*(code *)(*ppiVar1)[0x20])();
        *(undefined4 *)(param_2 + 0xc) = 1;
      }
    }
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0042859b;
  puStack_1c = (undefined *)0x428593;
  FUN_004034dc((int *)&local_8);
  return;
}

