/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cbb8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041cbb8(int *param_1,undefined *param_2)

{
  undefined uVar1;
  undefined4 *in_FS_OFFSET;
  undefined uVar2;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *puStack_c;
  uint *puStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_c = (undefined *)0x0;
  uVar2 = 1;
  puStack_20 = &LAB_0041cc26;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  uVar1 = *(undefined *)(param_1 + 5);
  FUN_00405fec((int)param_2,(int *)&puStack_c);
  FUN_004059cc(puStack_c,(LPSTR *)&puStack_8);
  FUN_00403760(puStack_8,(uint *)&DAT_0041cc3c);
  if ((bool)uVar2) {
    *(undefined *)(param_1 + 5) = 0;
  }
  FUN_0041c010(param_1,param_2);
  *(undefined *)(param_1 + 5) = uVar1;
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0041cc2d;
  puStack_20 = (undefined *)0x41cc25;
  FUN_004034fc((int *)&puStack_c,2);
  return;
}

