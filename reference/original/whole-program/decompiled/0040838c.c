/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040838c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040838c(int *param_1,char **param_2,char *param_3)

{
  code *pcVar1;
  char **ppcVar2;
  char *pcVar3;
  byte bVar4;
  
  pcVar3 = *param_2;
  bVar4 = 4;
  if (*pcVar3 != '\a') {
    bVar4 = pcVar3[(byte)pcVar3[1] + 2];
  }
  pcVar3 = param_2[4];
  if (param_2[4] == (char *)0x80000000) {
    pcVar3 = param_3;
  }
  pcVar1 = (code *)param_2[2];
  if (*(byte *)((int)param_2 + 0xb) == 0xff) {
    ppcVar2 = (char **)((int)param_1 + ((uint)pcVar1 & 0xffffff));
    *(char *)ppcVar2 = (char)param_3;
    if ((1 < bVar4) && (*(short *)ppcVar2 = (short)param_3, 3 < bVar4)) {
      *ppcVar2 = param_3;
    }
  }
  else if (*(byte *)((int)param_2 + 0xb) < 0xfe) {
    (*pcVar1)(param_1,pcVar3);
  }
  else {
    (**(code **)((int)(short)pcVar1 + *param_1))();
  }
  return;
}

