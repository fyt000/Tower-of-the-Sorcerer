/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bdfc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041bdfc(int *param_1,int *param_2,undefined param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  
  uVar3 = *(undefined4 *)(*param_1 + 0x24);
  uVar2 = *(undefined4 *)(*param_1 + 0x30);
  piVar4 = param_1;
  uVar1 = FUN_0041bda4((char)uVar2,(char)param_2,param_3,&stack0xfffffffc);
  (**(code **)(*param_2 + 4))(param_2,&DAT_0041be40,uVar1,uVar2,param_1,uVar3,piVar4);
  return;
}

