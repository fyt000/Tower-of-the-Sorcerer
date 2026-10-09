/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0043f1c0.
 * Inferred types and shared tails require assembly review. */

void helper_43f1c0(int *param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  byte abStack_10 [4];
  undefined uStack_c;
  int iStack_8;
  
  puStack_20 = &stack0xfffffffc;
  iStack_8 = 0;
  puStack_24 = &UNK_0043f236;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  bVar1 = FUN_004028b0(param_2);
  uVar3 = FUN_0043f1b4((int)param_1);
  bVar2 = FUN_004028b0((byte)uVar3);
  if (bVar1 != bVar2) {
    uStack_c = 2;
    abStack_10[0] = param_2;
    FUN_0040661c(&UNK_0043f24c,abStack_10,0,&iStack_8);
    (**(code **)(*param_1 + 0x8c))(param_1,iStack_8);
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &UNK_0043f23d;
  puStack_24 = (undefined *)0x43f235;
  FUN_004034dc(&iStack_8);
  return;
}

