/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00410508.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00410508(int *param_1,char param_2)

{
  int iVar1;
  int iVar2;
  undefined3 in_register_00000009;
  int iVar3;
  
  if (param_2 != *(char *)((int)param_1 + 0x2a)) {
    if ((param_2 != '\0') && (param_1[0x11] != 0)) {
      in_register_00000009 = 0;
      iVar1 = FUN_0041040c(param_1[0x11]);
      if (-1 < iVar1 + -1) {
        iVar3 = 0;
        do {
          in_register_00000009 = 0;
          iVar2 = FUN_0041041c(param_1[0x11],iVar3);
          if (*(char *)(iVar2 + 0x2a) != '\0') {
            in_register_00000009 = 0;
            iVar2 = FUN_0041041c(param_1[0x11],iVar3);
            *(undefined *)(iVar2 + 0x2a) = 0;
          }
          iVar3 = iVar3 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
    }
    *(char *)((int)param_1 + 0x2a) = param_2;
    (**(code **)(*param_1 + 0x28))(param_1,CONCAT31(in_register_00000009,1));
  }
  return;
}

