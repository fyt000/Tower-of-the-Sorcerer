/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004163ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004163ac(int *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar3;
  undefined4 uVar4;
  
  FUN_00414320(param_1);
  bVar1 = FUN_00416e54((int)param_1);
  uVar3 = extraout_var;
  if (bVar1) {
    uVar4 = 0;
    uVar2 = FUN_00419c90(param_1[0x11]);
    FUN_00413cb8(param_1,0x30,uVar2,uVar4);
    uVar3 = extraout_var_00;
  }
  FUN_00414d24((int)param_1,CONCAT22(uVar3,0xb008));
  return;
}

