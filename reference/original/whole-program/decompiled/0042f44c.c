/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f44c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f44c(int *param_1)

{
  undefined uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  undefined uStack_9;
  int *piStack_8;
  
  puStack_10 = (undefined *)0x42f45d;
  piStack_8 = param_1;
  uVar1 = FUN_004286f4(param_1);
  *(undefined *)((int)piStack_8 + 0x151) = uVar1;
  puStack_10 = (undefined *)0x42f472;
  iVar2 = FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)piStack_8 >> 8),1),extraout_ECX);
  piStack_8[0x51] = iVar2;
  puStack_10 = (undefined *)0x42f483;
  uVar3 = FUN_0042f574((int)piStack_8);
  uStack_9 = (undefined)uVar3;
  puStack_10 = (undefined *)0x42f490;
  FUN_0042f580((int)piStack_8,0);
  puStack_14 = &LAB_0042f4de;
  uStack_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_18;
  puStack_10 = &stack0xfffffffc;
  (**(code **)(*(int *)piStack_8[0x50] + 0x60))((int *)piStack_8[0x50],piStack_8[0x51]);
  FUN_0040af10((int *)piStack_8[0x51],0);
  *in_FS_OFFSET = uStack_18;
  puStack_10 = &LAB_0042f4e5;
  puStack_14 = (undefined *)0x42f4dd;
  FUN_0042f580((int)piStack_8,uStack_9);
  return;
}

