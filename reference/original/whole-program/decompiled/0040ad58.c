/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ad58.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ad58(int *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  int extraout_EDX;
  int iVar2;
  
  piVar1 = param_1;
  iVar2 = param_2;
  if (*(char *)(param_1 + 5) != '\0') {
    piVar1 = (int *)FUN_00409960(0xf00d,param_2);
    iVar2 = extraout_EDX;
  }
  if ((param_2 < 0) || (param_1[3] <= param_2)) {
    FUN_00409978(piVar1,iVar2);
  }
  (**(code **)(*param_1 + 0x6c))();
  FUN_0040352c((int *)(param_1[2] + param_2 * 8),param_3);
  (**(code **)(*param_1 + 0x68))();
  return;
}

