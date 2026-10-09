/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a1b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040a1b8(undefined4 param_1,undefined4 *param_2)

{
  byte bVar1;
  undefined in_CL;
  code *pcVar2;
  code *pcVar3;
  undefined4 uVar4;
  
  pcVar3 = root_0040a714;
  pcVar2 = root_0040a960;
  uVar4 = param_1;
  bVar1 = FUN_0040a164((char)param_1,(char)param_2,in_CL,&stack0xfffffffc);
  (**(code **)*param_2)(param_2,"Strings",bVar1,pcVar2,param_1,pcVar3,uVar4);
  return;
}

