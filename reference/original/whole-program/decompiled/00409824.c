/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409824.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409824(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 extraout_ECX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_18;
  undefined *puStackY_14;
  
  puStackY_14 = (undefined *)0x40983e;
  piVar1 = (int *)FUN_0040b54c(0x4090d4,CONCAT31((int3)((uint)param_2 >> 8),1),param_1,0x400);
  puStackY_14 = &LAB_0040986f;
  uStackY_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_18;
  FUN_0040d3b4((int)piVar1,param_2,extraout_ECX);
  *in_FS_OFFSET = uStackY_18;
  puStackY_14 = (undefined *)0x40986e;
  FUN_00402c34(piVar1);
  return;
}

