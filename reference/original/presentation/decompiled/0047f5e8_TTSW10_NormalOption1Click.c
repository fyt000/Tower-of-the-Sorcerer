/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047f5e8.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_NormalOption1Click(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  
  iVar1 = FUN_0042cec8((uint *)"Initialize options. Is it true?",
                       CONCAT31((int3)((uint)param_2 >> 8),2),_DAT_0047f6a0,0);
  if (iVar1 == 6) {
    DAT_00489b9c = 10;
    DAT_00489b9d = 0xc;
    DAT_00489b9e = 0;
    DAT_00489b9f = 2;
    DAT_00489ba0 = 0;
    DAT_00489ba1 = 1;
    DAT_00489ba2 = 0;
    DAT_00489ba3 = 0;
    DAT_00489ba5 = 0;
    if (DAT_00489ba4 == '\x01') {
      DAT_00489ba4 = '\0';
      FUN_00417dc4((int *)param_1[0x6c]);
      FUN_00417dc4((int *)param_1[0x71]);
      FUN_00417dc4((int *)param_1[0x103]);
      FUN_00484f48(param_1);
      FUN_0047d4a4((int)param_1);
      FUN_00454de8((int)param_1,extraout_EDX,extraout_ECX);
      FUN_00450880((int)param_1);
    }
    else {
      FUN_0047d4a4((int)param_1);
    }
  }
  return;
}

