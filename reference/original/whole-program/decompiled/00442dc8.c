/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00442dc8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void kaidanwork(int param_1)

{
  dword dVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  FUN_00402c34(DAT_0048c514);
  FUN_00402c34(DAT_0048c518);
  DAT_0048c514 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),
                                     extraout_ECX);
  DAT_0048c518 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),
                                     extraout_ECX_00);
  (**(code **)(*DAT_0048c514 + 0x28))(DAT_0048c514,*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)
  ;
  (**(code **)(*DAT_0048c514 + 0x2c))(DAT_0048c514,*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb)
  ;
  uVar2 = (**(code **)(*DAT_0048c514 + 0x1c))();
  (**(code **)(*DAT_0048c518 + 0x28))(DAT_0048c518,uVar2);
  uVar2 = (**(code **)(*DAT_0048c514 + 0x20))();
  (**(code **)(*DAT_0048c518 + 0x2c))(DAT_0048c518,uVar2);
  FUN_0042c454(*(int *)(param_1 + 0x1b4),'\0');
  iVar3 = 1;
  do {
    if ((original_hero._360_4_ != 0) && (iVar3 == 0x14)) {
      dVar1 = event_cursor + 1;
      event_cursor = dVar1;
      event_stack[dVar1].opcode = 0xf;
      event_stack[dVar1].a = 0;
      event_stack[dVar1].b = 0;
    }
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0x15;
    event_stack[dVar1].a = 1;
    event_stack[dVar1].b = 0x7a - (short)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x7a);
  iVar3 = 1;
  do {
    dVar1 = event_cursor + 1;
    event_cursor = dVar1;
    event_stack[dVar1].opcode = 0x15;
    event_stack[dVar1].a = 0;
    event_stack[dVar1].b = 0x7a - (short)iVar3;
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x7a);
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 0;
  event_stack[dVar1].a = 0;
  event_stack[dVar1].b = 0;
  dVar1 = event_cursor + 1;
  event_cursor = dVar1;
  event_stack[dVar1].opcode = 1;
  event_stack[dVar1].a = 9;
  event_stack[dVar1].b = 0;
  if (*(char *)(*(int *)(param_1 + 0x3a8) + 0x28) == '\x01') {
    FUN_0042c464(*(int *)(param_1 + 0x2ec),2);
  }
  if (*(char *)(*(int *)(param_1 + 0x3ac) + 0x28) == '\x01') {
    FUN_0042c464(*(int *)(param_1 + 0x2ec),6);
  }
  if (*(char *)(*(int *)(param_1 + 0x3b0) + 0x28) == '\x01') {
    FUN_0042c464(*(int *)(param_1 + 0x2ec),10);
  }
  start_event_timer(param_1);
  return;
}

