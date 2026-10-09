/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004081ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004081ac(int param_1,int param_2,int *param_3)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = FUN_004081a0(param_1);
  iVar1 = FUN_004081a0(*(int *)(iVar1 + 9));
  pbVar2 = (byte *)(iVar1 + 0xd);
  if (param_2 != 0) {
    do {
      pbVar2 = pbVar2 + *pbVar2 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  FUN_004035fc(param_3,pbVar2);
  return;
}

