/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406fb4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406fb4(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_120;
  undefined *puStack_11c;
  undefined *puStack_118;
  undefined4 *local_108;
  undefined4 local_104 [64];
  
  puStack_118 = &stack0xfffffffc;
  local_108 = (undefined4 *)0x0;
  puStack_11c = &LAB_00407076;
  uStack_120 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_120;
  iVar1 = 1;
  puVar2 = (undefined4 *)&DAT_0048a498;
  puVar3 = (undefined4 *)&DAT_0048a4d0;
  do {
    FUN_00405bf0(iVar1 + 0xfe7f,(int *)&local_108);
    FUN_00403988((undefined *)local_104,local_108,0xff);
    FUN_00402918(puVar2,local_104,7);
    FUN_00405bf0(iVar1 + 0xfe86,(int *)&local_108);
    FUN_00403988((undefined *)local_104,local_108,0xff);
    FUN_00402918(puVar3,local_104,0xf);
    iVar1 = iVar1 + 1;
    puVar3 = puVar3 + 4;
    puVar2 = puVar2 + 2;
  } while (iVar1 != 8);
  *in_FS_OFFSET = uStack_120;
  puStack_118 = &LAB_0040707d;
  puStack_11c = (undefined *)0x407075;
  FUN_004034dc((int *)&local_108);
  return;
}

