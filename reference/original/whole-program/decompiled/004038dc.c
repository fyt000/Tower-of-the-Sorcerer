/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004038dc.
 * Inferred types, shared tails and runtime effects require assembly review. */

char * FUN_004038dc(char *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  if (param_1 != (char *)0x0) {
    if (param_2 == (char *)0x0) {
      return (char *)0x0;
    }
    iVar3 = *(int *)(param_1 + -4) + -1;
    if (-1 < iVar3) {
      iVar1 = *(int *)(param_2 + -4) - iVar3;
      bVar7 = iVar1 == 0;
      pcVar5 = param_2;
      if (!bVar7 && iVar3 <= *(int *)(param_2 + -4)) {
LAB_004038fc:
        do {
          if (iVar1 != 0) {
            iVar1 = iVar1 + -1;
            pcVar4 = pcVar5 + 1;
            bVar7 = *param_1 == *pcVar5;
            pcVar5 = pcVar4;
            if (!bVar7) goto LAB_004038fc;
          }
          iVar2 = iVar3;
          pcVar4 = param_1 + 1;
          pcVar6 = pcVar5;
          if (!bVar7) break;
          do {
            if (iVar2 == 0) break;
            bVar7 = *pcVar4 == *pcVar6;
            iVar2 = iVar2 + -1;
            pcVar4 = pcVar4 + 1;
            pcVar6 = pcVar6 + 1;
          } while (bVar7);
          if (bVar7) {
            return pcVar5 + -(int)param_2;
          }
        } while( true );
      }
    }
    param_1 = (char *)0x0;
  }
  return param_1;
}

