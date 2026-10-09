/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040a898.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040a898(int *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int iStack_c;
  int *piStack_8;
  
  puStack_1c = &stack0xfffffffc;
  iStack_c = 0;
  puStack_20 = &LAB_0040a94e;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  puStack_28 = (undefined *)0x40a8c1;
  piStack_8 = param_1;
  FUN_0040a14c(param_1);
  puStack_2c = &LAB_0040a931;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  puStack_28 = &stack0xfffffffc;
  (**(code **)(*piStack_8 + 0x38))();
  if (param_2 != (undefined4 *)0x0) {
    while (puVar2 = param_2, *(char *)param_2 != '\0') {
      for (; ((cVar1 = *(char *)puVar2, cVar1 != '\0' && (cVar1 != '\n')) && (cVar1 != '\r'));
          puVar2 = (undefined4 *)((int)puVar2 + 1)) {
      }
      FUN_004035bc(&iStack_c,param_2,(int)puVar2 - (int)param_2);
      (**(code **)(*piStack_8 + 0x2c))(piStack_8,iStack_c);
      param_2 = puVar2;
      if (*(char *)puVar2 == '\r') {
        param_2 = (undefined4 *)((int)puVar2 + 1);
      }
      if (*(char *)param_2 == '\n') {
        param_2 = (undefined4 *)((int)param_2 + 1);
      }
    }
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_0040a938;
  puStack_2c = (undefined *)0x40a930;
  FUN_0040a204(piStack_8);
  return;
}

