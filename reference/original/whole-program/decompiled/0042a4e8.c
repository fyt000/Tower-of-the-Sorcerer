/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a4e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042a4e8(int **param_1,int param_2)

{
  char cVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  char *pcStack_8;
  
  puStack_18 = &stack0xfffffffc;
  pcStack_8 = (char *)0x0;
  puStack_1c = &LAB_0042a55a;
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  FUN_004135a4((int *)param_1,(int *)&pcStack_8);
  cVar1 = FUN_0041ff5c(CONCAT22(extraout_var,*(undefined2 *)(param_2 + 4)),pcStack_8);
  if (cVar1 != '\0') {
    uVar2 = FUN_00416c2c(param_1);
    if ((char)uVar2 != '\0') {
      FUN_00402cdc((int *)param_1,extraout_EDX,extraout_ECX);
      *(undefined4 *)(param_2 + 0xc) = 1;
      goto LAB_0042a544;
    }
  }
  FUN_004162dc((int)param_1,param_2);
LAB_0042a544:
  *in_FS_OFFSET = uStack_20;
  puStack_18 = &LAB_0042a561;
  puStack_1c = (undefined *)0x42a559;
  FUN_004034dc((int *)&pcStack_8);
  return;
}

