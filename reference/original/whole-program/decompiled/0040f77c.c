/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040f77c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040f77c(void)

{
  char cVar1;
  int *piVar2;
  ushort *puVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined4 *local_8;
  
  puStack_18 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_1c = &LAB_0040f7d3;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  cVar1 = '\x12';
  puVar3 = &DAT_004891f8;
  piVar2 = (int *)&DAT_0048a644;
  do {
    FUN_00405bf0((uint)*puVar3,(int *)&local_8);
    FUN_0040352c(piVar2,local_8);
    piVar2 = piVar2 + 1;
    puVar3 = puVar3 + 1;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0040f7da;
  puStack_1c = (undefined *)0x40f7d2;
  FUN_004034dc((int *)&local_8);
  return;
}

