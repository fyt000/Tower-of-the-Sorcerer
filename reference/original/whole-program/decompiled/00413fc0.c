/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413fc0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413fc0(int **param_1,int param_2)

{
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar2;
  
  FUN_004132a4(param_1,param_1);
  (*(code *)(*param_1)[-4])(param_1,param_2);
  uVar1 = extraout_ECX;
  uVar2 = extraout_EDX;
  if ((*(byte *)(param_1 + 0xd) & 2) != 0) {
    FUN_00413758(param_1,'\x01');
    uVar1 = extraout_ECX_00;
    uVar2 = extraout_EDX_00;
  }
  if ((*(byte *)(param_1 + 0xd) & 8) != 0) {
    FUN_00402cdc((int *)param_1,uVar2,uVar1);
  }
  FUN_00413f14((int *)param_1,param_2,0,DAT_00414010);
  return;
}

