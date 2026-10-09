/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004126c4.
 * Inferred types, shared tails and runtime effects require assembly review. */

LRESULT FUN_004126c4(HWND param_1,uint param_2,undefined4 param_3,undefined4 *param_4,
                    undefined4 param_5)

{
  LRESULT LVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  LVar1 = 0;
  if (param_1 != (HWND)0x0) {
    local_18 = *param_4;
    local_14 = param_4[1];
    local_c = param_5;
    local_10 = param_3;
    local_8 = param_3;
    LVar1 = SendMessageA(param_1,0xb02f,param_2 & 0x7f,(LPARAM)&local_18);
  }
  return LVar1;
}

