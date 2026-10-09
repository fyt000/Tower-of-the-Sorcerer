/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043fa68.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043fa68(int *param_1,int *param_2)

{
  bool bVar1;
  WPARAM WVar2;
  int iVar3;
  
  WVar2 = FUN_0042a91c(param_1);
  if (((-1 < (int)WVar2) && (iVar3 = (**(code **)(*(int *)param_1[0x40] + 0x10))(), iVar3 != 0)) &&
     (bVar1 = FUN_0042aa18(param_1,WVar2), bVar1)) {
    (**(code **)(*(int *)param_1[0x40] + 0xc))((int *)param_1[0x40],WVar2,param_2);
    return;
  }
  FUN_004034dc(param_2);
  return;
}

