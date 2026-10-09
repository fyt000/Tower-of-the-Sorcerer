/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004309b4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004309b4(int **param_1,int param_2)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  int **ppiVar4;
  int iVar5;
  int **ppiVar6;
  byte bVar7;
  int *apiStack_1c [4];
  
  bVar7 = 0;
  iVar5 = 0;
  bVar3 = 0;
  do {
    if (*(char *)(param_1 + (uint)bVar3 * 4 + 0x41) != '\0') {
      if ((iVar5 <= param_2) && (param_2 <= (int)param_1[0x6c] + iVar5)) {
        if (*(char *)(param_1 + 0x84) == '\0') {
          cVar1 = *(char *)((int)param_1 + (uint)bVar3 * 0x10 + 0x105);
        }
        else {
          cVar1 = *(char *)((int)param_1 + (uint)bVar3 * 0x10 + 0x107);
        }
        if (cVar1 == '\0') {
          return;
        }
        goto LAB_00430a22;
      }
      iVar5 = (int)param_1[0x6c] + iVar5 + -1;
    }
    bVar3 = bVar3 + 1;
    if (bVar3 == 9) {
LAB_00430a22:
      *(byte *)((int)param_1 + 0x19e) = bVar3;
      if (bVar3 != *(byte *)(param_1 + 0x75)) {
        *(byte *)(param_1 + 0x75) = bVar3;
        (*(code *)(*param_1)[0x21])();
      }
      FUN_0040923c(iVar5,0,(int)param_1[0x6c] + iVar5,apiStack_1c,param_1[0xc]);
      ppiVar4 = apiStack_1c;
      ppiVar6 = param_1 + 0x68;
      for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
        *ppiVar6 = *ppiVar4;
        ppiVar4 = ppiVar4 + (uint)bVar7 * -2 + 1;
        ppiVar6 = ppiVar6 + (uint)bVar7 * -2 + 1;
      }
      *(undefined *)(param_1 + 0x67) = 1;
      *(undefined *)((int)param_1 + 0x19d) = 1;
      FUN_00430420((int *)param_1,bVar3,iVar5);
      FUN_00413758(param_1,'\x01');
      return;
    }
  } while( true );
}

