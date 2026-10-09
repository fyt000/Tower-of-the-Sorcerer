/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fd08.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043fd08(int *param_1,byte *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0043c180(param_2,(byte *)param_1[0x4f]);
  if (iVar1 != 0) {
    FUN_0040274c((undefined *)param_1[0x4f]);
    FUN_00402710();
    FUN_0040274c(param_2);
    FUN_00402710();
    FUN_00402768('\0',param_1 + 0x4f);
    (**(code **)(*param_1 + 0x94))();
  }
  return;
}

