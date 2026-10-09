/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414990.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414990(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  undefined4 *in_FS_OFFSET;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puVar7;
  
  puVar7 = &stack0xfffffffc;
  puVar3 = &stack0xfffffffc;
  puVar4 = &stack0xfffffffc;
  puVar5 = &stack0xfffffffc;
  puVar6 = &stack0xfffffffc;
  puStack_1c = (undefined *)0x4149a5;
  uVar1 = FUN_00414954((undefined)param_1,(undefined)param_2,(undefined)param_3,&stack0xfffffffc);
  if ((char)uVar1 != '\0') {
    piVar2 = (int *)FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX >> 8),1),puVar7);
    puStack_1c = &LAB_00414a0a;
    uStack_20 = *in_FS_OFFSET;
    *in_FS_OFFSET = &uStack_20;
    FUN_00414824('\x01',extraout_EDX_00,extraout_ECX,(int)&stack0xfffffffc);
    FUN_00414824('\x02',extraout_EDX_01,puVar3,(int)&stack0xfffffffc);
    FUN_00414824('\x03',extraout_EDX_02,puVar4,(int)&stack0xfffffffc);
    FUN_00414824('\x04',extraout_EDX_03,puVar5,(int)&stack0xfffffffc);
    FUN_00414824('\x05',extraout_EDX_04,puVar6,(int)&stack0xfffffffc);
    *in_FS_OFFSET = uStack_20;
    puStack_1c = (undefined *)0x414a09;
    FUN_00402c34(piVar2);
    return;
  }
  return;
}

