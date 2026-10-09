/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040de7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040de7c(undefined param_1,undefined param_2,undefined param_3,uint param_4)

{
  undefined uVar1;
  char cVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined uVar3;
  undefined4 *in_FS_OFFSET;
  uint uVar4;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  uVar3 = SUB41(&stack0xfffffffc,0);
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0040dedf;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  uVar1 = FUN_00408510(*(int **)(param_4 - 8),*(char ***)(param_4 - 0xc),(int *)&local_8);
  cVar2 = FUN_0040ddf4(uVar1,extraout_DL,extraout_CL,&stack0xfffffffc);
  if (cVar2 == '\0') {
    uVar4 = param_4;
    FUN_0040d9f8((char)param_4,extraout_DL_00,uVar3,param_4);
    FUN_0040e448(*(int *)(param_4 - 4),local_8,uVar4);
  }
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040dee6;
  puStack_1c = (undefined *)0x40dede;
  FUN_004034dc((int *)&local_8);
  return;
}

