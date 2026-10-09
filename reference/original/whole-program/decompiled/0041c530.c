/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c530.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c530(undefined4 param_1,int *param_2)

{
  bool bVar1;
  undefined in_CL;
  code *pcVar2;
  code *pcVar3;
  undefined4 uVar4;
  
  pcVar3 = root_0041c38c;
  pcVar2 = FUN_0041c468;
  uVar4 = param_1;
  bVar1 = FUN_0041c4b4((char)param_1,(char)param_2,in_CL,&stack0xfffffffc);
  (**(code **)(*param_2 + 4))(param_2,&DAT_0041c574,bVar1,pcVar2,param_1,pcVar3,uVar4);
  return;
}

