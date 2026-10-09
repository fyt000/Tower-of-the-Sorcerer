/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00428b18.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00428b18(int param_1,UINT *param_2)

{
  undefined4 uVar1;
  BOOL BVar2;
  
  if (*param_2 == 7) {
    if ((DAT_00489080 == 1) && (BVar2 = IsWindow((HWND)param_2[1]), BVar2 == 0)) {
      param_2[1] = 0;
    }
  }
  else if ((*param_2 == 0x205) && (uVar1 = FUN_00427ee0(param_1), (char)uVar1 != '\0')) {
    return;
  }
  FUN_004155c4(param_1,param_2);
  return;
}

