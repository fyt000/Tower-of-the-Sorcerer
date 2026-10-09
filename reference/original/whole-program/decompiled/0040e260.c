/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e260.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e260(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined uVar1;
  undefined4 uVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined uVar3;
  undefined4 *in_FS_OFFSET;
  int iVar4;
  undefined4 uStack_128;
  undefined *puStack_124;
  undefined *puStack_120;
  byte local_110 [256];
  undefined *local_10;
  int local_c [2];
  
  puStack_120 = &stack0xfffffffc;
  uVar3 = SUB41(&stack0xfffffffc,0);
  local_10 = (undefined *)0x0;
  puStack_124 = &LAB_0040e308;
  uStack_128 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_128;
  uVar1 = FUN_00408688(*(int **)(param_4 + -8),*(int *)(param_4 + -0xc),local_c);
  uVar2 = FUN_0040e1dc(uVar1,extraout_DL,extraout_CL,&stack0xfffffffc);
  if ((char)uVar2 == '\0') {
    iVar4 = param_4;
    FUN_0040d9f8((char)param_4,extraout_DL_00,uVar3,param_4);
    if (local_c[0] == 0) {
      FUN_0040e4a4(*(int *)(param_4 + -4),0xd,iVar4);
    }
    else {
      FUN_00402d80(**(int **)(*(int *)(param_4 + -4) + 0x18),local_c[0],local_110);
      FUN_004035fc((int *)&local_10,local_110);
      FUN_0040d784(*(int *)(param_4 + -4),local_10);
    }
  }
  *in_FS_OFFSET = uStack_128;
  puStack_120 = &LAB_0040e30f;
  puStack_124 = (undefined *)0x40e307;
  FUN_004034dc((int *)&local_10);
  return;
}

