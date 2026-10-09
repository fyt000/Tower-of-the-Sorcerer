/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dc78.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040dc78(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  char cVar1;
  bool bVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined4 extraout_EDX;
  undefined uVar3;
  undefined4 *in_FS_OFFSET;
  int iVar4;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *local_c;
  uint local_8;
  
  puStack_1c = &stack0xfffffffc;
  uVar3 = SUB41(&stack0xfffffffc,0);
  local_c = (undefined *)0x0;
  puStack_20 = &LAB_0040dd42;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  local_8 = FUN_0040831c(*(int **)(param_4 + -8),*(char ***)(param_4 + -0xc));
  bVar2 = FUN_0040dc28((char)local_8,extraout_DL,extraout_CL,&stack0xfffffffc);
  if (!bVar2) {
    iVar4 = param_4;
    FUN_0040d9f8((char)param_4,extraout_DL_00,uVar3,param_4);
    cVar1 = **(char **)(param_4 + -0x10);
    if (cVar1 == '\x01') {
      FUN_0040dae4(**(int **)(param_4 + -0xc),local_8,iVar4,param_4);
    }
    else if (cVar1 == '\x02') {
      FUN_0040d360(*(int *)(param_4 + -4),local_8);
    }
    else if (cVar1 == '\x03') {
      FUN_004081ac(*(int *)(param_4 + -0x10),local_8,(int *)&local_c);
      FUN_0040d784(*(int *)(param_4 + -4),local_c);
    }
    else if (cVar1 == '\x06') {
      FUN_0040da50(local_8,extraout_EDX,iVar4,param_4);
    }
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0040dd49;
  puStack_20 = (undefined *)0x40dd41;
  FUN_004034dc((int *)&local_c);
  return;
}

