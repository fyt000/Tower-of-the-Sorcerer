/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b19c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0040b19c(undefined4 param_1,undefined *param_2)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_18;
  undefined *puStackY_14;
  
  puStackY_14 = (undefined *)0x40b1b6;
  piVar1 = (int *)FUN_0040b04c(0x408ec8,CONCAT31((int3)((uint)param_2 >> 8),1),param_2,0xffff);
  puStackY_14 = &UNK_0040b1e7;
  uStackY_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_18;
  root_0040b184(param_1,piVar1);
  *in_FS_OFFSET = uStackY_18;
  puStackY_14 = (undefined *)0x40b1e6;
  FUN_00402c34(piVar1);
  return;
}

