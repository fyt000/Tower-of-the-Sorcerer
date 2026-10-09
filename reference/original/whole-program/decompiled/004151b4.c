/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004151b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004151b4(int *param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  code *pcStack_20;
  undefined *puStack_1c;
  
  if (((*(char *)((int)param_1 + 0x37) == '\0') &&
      (((*(byte *)(param_1 + 7) & 0x10) == 0 || ((*(byte *)((int)param_1 + 0x35) & 4) != 0)))) ||
     ((*(byte *)((int)param_1 + 0x36) & 8) != 0)) {
    cVar1 = '\0';
  }
  else {
    cVar1 = '\x01';
  }
  if (cVar1 != '\0') {
    if (param_1[0x30] == 0) {
      puStack_1c = (undefined *)0x415207;
      (**(code **)(*param_1 + 0x58))();
    }
    if ((param_1[0x2d] != 0) && (iVar3 = *(int *)(param_1[0x2d] + 8), -1 < iVar3 + -1)) {
      iVar4 = 0;
      do {
        puStack_1c = (undefined *)0x41522f;
        piVar2 = (int *)FUN_00409a40((undefined4 *)param_1[0x2d],iVar4);
        puStack_1c = (undefined *)0x415234;
        FUN_004151b4(piVar2);
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  if ((param_1[0x30] != 0) && (*(char *)((int)param_1 + 199) != cVar1)) {
    *(char *)((int)param_1 + 199) = cVar1;
    pcStack_20 = thunk_FUN_00402f4c;
    uStack_24 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_24;
    puStack_1c = &stack0xfffffffc;
    FUN_00413cb8(param_1,0xb019,0,0);
    *in_FS_OFFSET = uStack_24;
  }
  return;
}

