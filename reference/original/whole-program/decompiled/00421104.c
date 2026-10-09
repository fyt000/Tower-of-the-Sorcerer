/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421104.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421104(undefined4 param_1,int **param_2)

{
  int *piVar1;
  code *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  FUN_00413e5c(param_1,param_2);
  uVar5 = 0;
  uVar4 = 0;
  pcVar2 = root_004211b4;
  uVar3 = param_1;
  piVar1 = FUN_00402c7c(param_2,(int *)&PTR_root_004090d4);
  (*(code *)**param_2)(param_2,"PixelsPerInch",piVar1,pcVar2,uVar3,uVar4,uVar5);
  (*(code *)**param_2)(param_2,"TextHeight",1,root_00421198,param_1,&LAB_00421180,param_1);
  return;
}

