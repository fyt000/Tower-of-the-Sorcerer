/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004237a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004237a8(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(char *)((int)param_1 + 0x119) == '\0') {
    if ((*(char *)((int)param_1 + 0x37) == '\0') || (*(char *)(param_1 + 0xe) == '\0')) {
      uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf02e);
      param_1 = (int *)FUN_004031f8(uVar1);
    }
    FUN_004226b4(param_1);
  }
  return;
}

