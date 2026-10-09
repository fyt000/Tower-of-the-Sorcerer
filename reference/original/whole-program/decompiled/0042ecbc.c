/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ecbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042ecbc(void)

{
  int *piVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  int *in_stack_00000004;
  undefined4 *in_stack_00000008;
  uint in_stack_0000000c;
  uint *in_stack_00000010;
  undefined4 uStack_38;
  code *pcStack_34;
  undefined *puStack_30;
  undefined4 uStack_2c;
  code *pcStack_28;
  undefined *puStack_24;
  
  puStack_24 = (undefined *)0x42ecde;
  piVar1 = FUN_00406220(in_stack_0000000c + 1);
  pcStack_28 = thunk_FUN_00403140;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  iVar4 = (int)in_stack_0000000c >> 1;
  if (iVar4 < 0) {
    iVar4 = iVar4 + (uint)((in_stack_0000000c & 1) != 0);
  }
  *in_stack_00000010 = 0;
  pcVar2 = (char *)((int)piVar1 + iVar4);
  pcStack_34 = thunk_FUN_00402f4c;
  uStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_38;
  puStack_30 = &stack0xfffffffc;
  puStack_24 = &stack0xfffffffc;
  if (*in_stack_00000004 != 0) {
    puStack_30 = &stack0xfffffffc;
    puStack_24 = &stack0xfffffffc;
    uVar3 = (***(code ***)(undefined4 *)*in_stack_00000004)
                      ((undefined4 *)*in_stack_00000004,in_stack_00000004[1],pcVar2,iVar4);
    *in_stack_00000010 = uVar3;
  }
  if (0 < (int)*in_stack_00000010) {
    pcVar2[*in_stack_00000010] = '\0';
    if (pcVar2[*in_stack_00000010 - 1] == '\r') {
      pcVar2[*in_stack_00000010 - 1] = '\0';
    }
    uVar3 = FUN_0042ec24((undefined2 *)piVar1,pcVar2);
    *in_stack_00000010 = uVar3;
    FUN_00402870(piVar1,in_stack_00000008,*in_stack_00000010);
  }
  *in_FS_OFFSET = uStack_38;
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_0042eda3;
  pcStack_28 = (code *)0x42ed9b;
  FUN_0040626c((int)piVar1);
  return;
}

