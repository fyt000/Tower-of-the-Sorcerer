/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004179f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004179f0(int *param_1)

{
  HIMAGELIST p_Var1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  p_Var1 = ImageList_Create(param_1[9],param_1[8],
                            *(uint *)(&DAT_0048932c + (uint)*(byte *)((int)param_1 + 0x31) * 4) |
                            0xfe,4,param_1[10]);
  param_1[0xb] = (int)p_Var1;
  if (p_Var1 == (HIMAGELIST)0x0) {
    uVar2 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf027);
    FUN_004031f8(uVar2);
  }
  if (param_1[0xd] != 0x1fffffff) {
    FUN_00417de0(param_1,param_1[0xd]);
  }
  return;
}

