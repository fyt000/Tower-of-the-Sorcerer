/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040d8a4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040d8a4(int param_1,char param_2,int param_3)

{
  undefined4 extraout_ECX;
  undefined4 local_c;
  
  if (DAT_0040d8e4 != param_2) {
    local_c._2_2_ = (undefined2)((uint)param_3 >> 0x10);
    local_c = CONCAT22(local_c._2_2_,CONCAT11(param_2,param_2)) | 0xf000;
    FUN_0040d260(param_1,(undefined4 *)((int)&local_c + 1),1);
    if ((local_c & 2) != 0) {
      FUN_0040d820(param_1,param_3,extraout_ECX);
    }
  }
  return;
}

