/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00416074.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00416074(int **param_1,int param_2)

{
  BOOL BVar1;
  HWND pHVar2;
  int **ppiVar3;
  int iVar4;
  
  if ((((((*(uint *)(param_2 + 4) & 0xfff0) == 0xf100) && (*(short *)(param_2 + 8) != 0x20)) &&
       (*(short *)(param_2 + 8) != 0x2d)) &&
      ((BVar1 = IsIconic((HWND)param_1[0x30]), BVar1 == 0 &&
       (pHVar2 = GetCapture(), pHVar2 == (HWND)0x0)))) &&
     ((param_1 != *(int ***)(DAT_0048a6f8 + 0x28) &&
      ((ppiVar3 = FUN_0041fffc(param_1), ppiVar3 != (int **)0x0 &&
       (iVar4 = FUN_00413cb8((int *)ppiVar3,0xb017,0,param_2), iVar4 != 0)))))) {
    return;
  }
  (*(code *)(*param_1)[-4])(param_1,param_2);
  return;
}

