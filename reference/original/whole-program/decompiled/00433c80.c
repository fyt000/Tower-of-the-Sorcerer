/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433c80.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00433c80(int *param_1)

{
  undefined *puVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *puStack_c;
  undefined *puStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_8 = (undefined *)0x0;
  puStack_c = (undefined *)0x0;
  puStack_20 = &UNK_00433cee;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_00405bf0((uint)*(ushort *)(&DAT_00489890 + (uint)*(byte *)((int)param_1 + 0x115) * 2),
               (int *)&puStack_8);
  puVar1 = puStack_8;
  FUN_004135a4(param_1,(int *)&puStack_c);
  FUN_004059fc(puStack_c,puVar1);
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &UNK_00433cf5;
  puStack_20 = (undefined *)0x433ce5;
  FUN_004034dc((int *)&puStack_c);
  puStack_20 = (undefined *)0x433ced;
  FUN_004034dc((int *)&puStack_8);
  return;
}

