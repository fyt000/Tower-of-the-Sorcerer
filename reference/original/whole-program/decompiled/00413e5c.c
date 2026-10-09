/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413e5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413e5c(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined in_CL;
  undefined *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  
  puVar3 = &LAB_00413e0c;
  puVar2 = &LAB_00413e20;
  uVar4 = param_1;
  uVar1 = FUN_00413e2c((char)param_1,(char)param_2,in_CL,&stack0xfffffffc);
  (**(code **)*param_2)(param_2,"IsControl",uVar1,puVar2,param_1,puVar3,uVar4);
  return;
}

