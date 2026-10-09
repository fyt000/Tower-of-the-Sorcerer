/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403dc4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403dc4(VARIANTARG *param_1,VARIANTARG *param_2,VARTYPE param_3)

{
  VARTYPE VVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  VARIANTARG local_14;
  
  VVar1 = (param_2->n1).n2.vt;
  if (param_3 == VVar1) {
    puStack_20 = (undefined *)0x403de0;
    FUN_00403c90(param_1,param_2);
  }
  else if (VVar1 == 0x100) {
    if (param_3 != 8) {
      local_14.n1.n2.vt = 0;
      puStack_20 = (undefined *)0x403e0c;
      FUN_00403da4(&local_14,(int)param_2);
      puStack_24 = &LAB_00403e3d;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_20 = &stack0xfffffffc;
      FUN_00403d04(param_1,&local_14,param_3);
      *in_FS_OFFSET = uStack_28;
      puStack_20 = (undefined *)0x403ead;
      puStack_24 = (undefined *)0x403e3c;
      FUN_00403c5c(&local_14);
      return;
    }
    puStack_20 = (undefined *)0x403df9;
    FUN_00403da4(param_1,(int)param_2);
  }
  else if (param_3 == 0x100) {
    if (VVar1 != 8) {
      local_14.n1.n2.vt = 0;
      puStack_20 = (undefined *)0x403e6d;
      FUN_00403d04(&local_14,param_2,8);
      puStack_24 = &LAB_00403e9c;
      uStack_28 = *in_FS_OFFSET;
      *in_FS_OFFSET = &uStack_28;
      puStack_20 = &stack0xfffffffc;
      FUN_00403d74(param_1,(int)&local_14);
      *in_FS_OFFSET = uStack_28;
      puStack_20 = (undefined *)0x403ead;
      puStack_24 = (undefined *)0x403e9b;
      FUN_00403c5c(&local_14);
      return;
    }
    puStack_20 = (undefined *)0x403e59;
    FUN_00403d74(param_1,(int)param_2);
  }
  else {
    puStack_20 = (undefined *)0x403ead;
    FUN_00403d04(param_1,param_2,param_3);
  }
  return;
}

