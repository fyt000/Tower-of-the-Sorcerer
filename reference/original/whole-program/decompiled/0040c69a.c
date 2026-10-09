/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c69a.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 thunk_FUN_00403010(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int **ppiVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  undefined4 *in_FS_OFFSET;
  bool bVar10;
  PEXCEPTION_RECORD in_stack_00000004;
  PVOID in_stack_00000008;
  ULONG_PTR in_stack_0000000c;
  int *piStack_24;
  PVOID pvStack_20;
  ULONG_PTR UStack_1c;
  PEXCEPTION_RECORD pEStack_18;
  undefined4 uStack_14;
  
  if ((in_stack_00000004->ExceptionFlags & 6) == 0) {
    if (in_stack_00000004->ExceptionCode == 0xeedface) {
      iVar2 = *(int *)in_stack_00000004->ExceptionInformation[1];
    }
    else {
      FUN_00402b6c();
      if (DAT_0048a008 == (code *)0x0) {
        return 1;
      }
      iVar2 = (*DAT_0048a008)();
      if (iVar2 == 0) {
        return 1;
      }
    }
    iVar7 = *(int *)(*(int *)((int)in_stack_00000008 + 4) + 5);
    piVar8 = (int *)(*(int *)((int)in_stack_00000008 + 4) + 9);
    do {
      iVar3 = *piVar8;
      iVar9 = iVar2;
      if (iVar3 == 0) {
LAB_004030a2:
        UStack_1c = in_stack_00000004->ExceptionInformation[1];
        pvStack_20 = (PVOID)in_stack_00000004->ExceptionInformation[0];
        if (in_stack_00000004->ExceptionCode != 0xeedface) {
          uStack_14 = 0x4030ba;
          uVar4 = (*DAT_0048a00c)();
          uStack_14 = 0x4030c3;
          UStack_1c = FUN_00402e6c(uVar4,in_stack_0000000c);
          pvStack_20 = in_stack_00000004->ExceptionAddress;
        }
        uStack_14 = *in_FS_OFFSET;
        pEStack_18 = in_stack_00000004;
        in_stack_00000004->ExceptionFlags = in_stack_00000004->ExceptionFlags | 2;
        piStack_24 = piVar8;
        RtlUnwind(in_stack_00000008,(PVOID)0x4030ec,in_stack_00000004,(PVOID)0x0);
        piVar8 = piStack_24;
        piStack_24 = (int *)0x4030f6;
        ppiVar5 = (int **)FUN_00403498();
        piStack_24 = *ppiVar5;
        *ppiVar5 = (int *)&piStack_24;
        *(undefined **)((int)in_stack_00000008 + 4) = &LAB_00403118;
        FUN_00402ea0();
                    /* WARNING: Could not recover jumptable at 0x00403115. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (*(code *)piVar8[1])();
        return uVar4;
      }
      do {
        if (iVar3 == iVar9) goto LAB_004030a2;
        if (*(int *)(iVar3 + -0x18) == *(int *)(iVar9 + -0x18)) {
          bVar1 = **(byte **)(iVar3 + -0x1c);
          if (bVar1 == **(byte **)(iVar9 + -0x1c)) {
            piVar6 = (int *)(*(byte **)(iVar9 + -0x1c) + 1);
            bVar10 = piVar6 == (int *)0x0;
            uStack_14 = 0x403088;
            FUN_00402948((int *)(*(byte **)(iVar3 + -0x1c) + 1),piVar6,(uint)bVar1);
            if (bVar10) goto LAB_004030a2;
          }
        }
        piVar6 = (int *)(iVar9 + -0x14);
        iVar3 = *piVar8;
        iVar9 = *piVar6;
      } while (*piVar6 != 0);
      piVar8 = piVar8 + 2;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  return 1;
}

