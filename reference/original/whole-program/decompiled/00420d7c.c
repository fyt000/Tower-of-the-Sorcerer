/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00420d7c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int ** root_00420d7c(int **param_1,char param_2)

{
  bool bVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  
  puStack_1c = (undefined *)0x420d93;
  FUN_0040e704((int)param_1);
  puStack_1c = (undefined *)0x420d9d;
  FUN_0040b868((int)param_1,(undefined *)0x0);
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  if (param_1[0x51] != (int *)0x0) {
    puStack_1c = (undefined *)0x420dae;
    (**(code **)*param_1[0x51])();
    uVar2 = extraout_ECX_00;
    uVar3 = extraout_EDX_00;
  }
  if (*(char *)((int)param_1 + 0x11a) != '\x01') {
    puStack_1c = (undefined *)0x420dc2;
    FUN_00423788((int *)param_1,uVar3,uVar2);
  }
  if (*(short *)((int)param_1 + 0x1aa) != 0) {
    pcStack_20 = thunk_FUN_00402f4c;
    uStack_24 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_24;
    puStack_1c = &stack0xfffffffc;
    (*(code *)param_1[0x6a])(param_1[0x6b],param_1);
    *in_FS_OFFSET = uStack_24;
  }
  puStack_1c = (undefined *)0x420e1a;
  FUN_004227b8((int *)param_1,'\0');
  puStack_1c = (undefined *)0x420e22;
  bVar1 = FUN_00416e54((int)param_1);
  if (bVar1) {
    puStack_1c = (undefined *)0x420e2e;
    (*(code *)(*param_1)[0x1a])();
  }
  puStack_1c = (undefined *)0x420e3b;
  FUN_00423c0c(DAT_0048a6fc,(int)param_1);
  puStack_1c = (undefined *)0x420e49;
  FUN_00402c34(param_1[0x48]);
  puStack_1c = (undefined *)0x420e57;
  FUN_00402c34(param_1[0x49]);
  puStack_1c = (undefined *)0x420e65;
  FUN_00402c34(param_1[0x4a]);
  puStack_1c = (undefined *)0x420e6f;
  FUN_0042063c(param_1,'\0');
  puStack_1c = (undefined *)0x420e7d;
  FUN_00402c34(param_1[0x51]);
  if (param_2 != '\0') {
    puStack_1c = (undefined *)0x420e8b;
    FUN_00402e48((int *)param_1);
  }
  return param_1;
}

