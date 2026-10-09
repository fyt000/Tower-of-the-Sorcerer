/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405a6c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405a6c(char *param_1,char **param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  
  iVar2 = FUN_00403650((int)param_1);
  pcVar5 = param_1 + iVar2;
  iVar2 = 0;
  pcVar3 = param_1;
  if (param_1 < pcVar5) {
    do {
      if (*pcVar3 == '\n') {
        iVar2 = iVar2 + 1;
      }
      else if (*pcVar3 == '\r') {
        if (pcVar3[1] == '\n') {
          pcVar3 = pcVar3 + 1;
        }
        else {
          iVar2 = iVar2 + 1;
        }
      }
      pcVar3 = pcVar3 + 1;
    } while (pcVar3 < pcVar5);
  }
  if (iVar2 == 0) {
    FUN_00403570((int *)param_2,(int)param_1);
  }
  else {
    FUN_004035bc((int *)param_2,(undefined4 *)0x0,(uint)(pcVar5 + (iVar2 - (int)param_1)));
    pcVar3 = *param_2;
    if (param_1 < pcVar5) {
      do {
        cVar1 = *param_1;
        if (cVar1 == '\n') {
          *pcVar3 = '\r';
          pcVar3[1] = '\n';
          pcVar3 = pcVar3 + 2;
          pcVar4 = param_1 + 1;
        }
        else if (cVar1 == '\r') {
          *pcVar3 = '\r';
          pcVar3[1] = '\n';
          pcVar3 = pcVar3 + 2;
          pcVar4 = param_1 + 1;
          if (*pcVar4 == '\n') {
            pcVar4 = param_1 + 2;
          }
        }
        else {
          *pcVar3 = cVar1;
          pcVar3 = pcVar3 + 1;
          pcVar4 = param_1 + 1;
        }
        param_1 = pcVar4;
      } while (pcVar4 < pcVar5);
    }
  }
  return;
}

