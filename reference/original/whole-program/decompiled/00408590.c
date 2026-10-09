/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00408590.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00408590(int *param_1,int *param_2)

{
  code *pcVar1;
  
  pcVar1 = (code *)param_2[1];
  if (*(char *)((int)param_2 + 7) == -1) {
    (*(code *)(&PTR_LAB_004085ac)[*(byte *)(*param_2 + 2 + (uint)*(byte *)(*param_2 + 1))])
              ((int)param_1 + ((uint)pcVar1 & 0xffffff));
    return;
  }
  if (*(char *)((int)param_2 + 7) != -2) {
    (*pcVar1)(param_1,param_2[4]);
    return;
  }
  (**(code **)((int)(short)pcVar1 + *param_1))(param_1,param_2[4]);
  return;
}

