/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e818.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e818(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined in_CL;
  undefined extraout_CL;
  undefined extraout_DL;
  undefined4 uVar3;
  undefined *puVar4;
  code *pcVar5;
  
  pcVar5 = root_0040e5bc;
  puVar4 = &LAB_0040e5e4;
  uVar3 = param_1;
  uVar2 = param_1;
  uVar1 = FUN_0040e7a8((char)param_1,(char)param_2,in_CL,&stack0xfffffffc);
  (**(code **)*param_2)(param_2,&DAT_0040e888,uVar1,puVar4,uVar3,pcVar5,uVar2);
  pcVar5 = root_0040e5d0;
  puVar4 = &LAB_0040e5f0;
  uVar3 = param_1;
  uVar2 = FUN_0040e7e0((char)param_1,extraout_DL,extraout_CL,&stack0xfffffffc);
  (**(code **)*param_2)(param_2,&DAT_0040e898,uVar2,puVar4,param_1,pcVar5,uVar3);
  return;
}

