/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040dda8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040dda8(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined uVar1;
  undefined4 uVar2;
  undefined extraout_CL;
  undefined extraout_DL;
  undefined extraout_DL_00;
  undefined4 extraout_EDX;
  undefined uVar3;
  undefined in_MM0_Ba;
  int iVar4;
  
  uVar3 = SUB41(&stack0xfffffffc,0);
  uVar1 = FUN_00408590(*(int **)(param_4 + -8),*(int **)(param_4 + -0xc));
  uVar2 = FUN_0040dd50(uVar1,extraout_DL,extraout_CL,&stack0xfffffffc);
  if ((char)uVar2 == '\0') {
    iVar4 = param_4;
    FUN_0040d9f8((char)param_4,extraout_DL_00,uVar3,param_4);
    FUN_0040d760(*(int *)(param_4 + -4),extraout_EDX,iVar4,in_MM0_Ba);
  }
  return;
}

