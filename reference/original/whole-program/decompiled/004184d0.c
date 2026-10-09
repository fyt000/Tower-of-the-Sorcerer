/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004184d0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004184d0(int *param_1,int *param_2)

{
  int iVar1;
  code *pcVar2;
  code *pcVar3;
  int *piVar4;
  
  FUN_0040e818(param_1,param_2);
  pcVar3 = root_00418518;
  pcVar2 = root_00418760;
  piVar4 = param_1;
  iVar1 = FUN_00417b3c(param_1);
  (**(code **)(*param_2 + 4))(param_2,"Bitmap",0 < iVar1,pcVar2,param_1,pcVar3,piVar4);
  return;
}

