/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403214.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00403214(void)

{
  uint *puVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 *in_stack_00000014;
  int in_stack_00000030;
  
  *(undefined4 *)(in_stack_00000030 + 4) = 0x40325f;
  piVar3 = (int *)FUN_00403498();
  piVar2 = (int *)*piVar3;
  *piVar3 = *piVar2;
  piVar3 = (int *)piVar2[3];
  puVar1 = (uint *)(piVar3 + 1);
  *puVar1 = *puVar1 & 0xfffffffd;
  if (*piVar3 != 0xeedface) {
    FUN_00402c34((int *)piVar2[2]);
    root_00402e50();
  }
  *in_stack_00000014 = *(undefined4 *)*in_FS_OFFSET;
  return 1;
}

