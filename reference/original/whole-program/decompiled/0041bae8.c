/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041bae8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041bae8(int *param_1,HBITMAP param_2,HPALETTE param_3,LPVOID *param_4,
                 LPBITMAPINFO *param_5,int param_6)

{
  int local_10;
  int local_c;
  HPALETTE local_8;
  
  local_8 = param_3;
  if (param_2 == (HBITMAP)0x0) {
    FUN_0041ac38(param_1,0);
  }
  FUN_0041b9dc(param_2,&local_c,&local_10,param_6);
  FUN_0040b2e8(param_1,local_c + local_10);
  *param_5 = (LPBITMAPINFO)param_1[1];
  *param_4 = (LPVOID)((int)&(((tagBITMAPINFO *)((*param_5)->bmiColors + -10))->bmiHeader).biSize +
                     local_c);
  FUN_0041ba28(param_2,local_8,*param_5,param_6,*param_4);
  return;
}

