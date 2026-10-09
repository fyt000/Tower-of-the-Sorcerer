/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040afc0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040afc0(undefined4 param_1,int *param_2)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_1c;
  undefined *puStackY_18;
  
  puStackY_18 = (undefined *)0x40afdc;
  piVar1 = (int *)FUN_0040b54c(0x40906c,CONCAT31((int3)((uint)param_2 >> 8),1),param_1,0x1000);
  puStackY_18 = &LAB_0040b010;
  uStackY_1c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_1c;
  FUN_0040caf4((int)piVar1,param_2);
  *in_FS_OFFSET = uStackY_1c;
  puStackY_18 = (undefined *)0x40b00f;
  FUN_00402c34(piVar1);
  return;
}

