/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410bdc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00410bdc(int *param_1)

{
  HMENU pHVar1;
  char *pcVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined *puVar4;
  undefined4 local_204 [128];
  
  puVar4 = &stack0xfffffffc;
  local_204[0]._0_1_ = '\0';
  if (param_1[9] != 0) {
    pHVar1 = (HMENU)(**(code **)(*param_1 + 0x2c))();
    FUN_00410b08(pHVar1,extraout_EDX,extraout_ECX,(int)puVar4);
  }
  if (param_1[10] != 0) {
    pcVar2 = FUN_00403814((undefined *)param_1[10]);
    iVar3 = FUN_004061dc(pcVar2,(char *)local_204);
    if (iVar3 == 0) {
      return 0;
    }
  }
  FUN_00403638(param_1 + 10,local_204,0x200);
  return 1;
}

