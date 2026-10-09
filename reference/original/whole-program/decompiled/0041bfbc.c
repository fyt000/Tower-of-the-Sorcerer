/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bfbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041bfbc(int *param_1,undefined *param_2)

{
  int *piVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_18;
  undefined *puStackY_14;
  
  puStackY_14 = (undefined *)0x41bfd3;
  piVar1 = (int *)FUN_0040b04c(0x408ec8,CONCAT31((int3)((uint)param_2 >> 8),1),param_2,0);
  puStackY_14 = &LAB_0041c004;
  uStackY_18 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_18;
  (**(code **)(*param_1 + 0x3c))(param_1,piVar1);
  *in_FS_OFFSET = uStackY_18;
  puStackY_14 = (undefined *)0x41c003;
  FUN_00402c34(piVar1);
  return;
}

