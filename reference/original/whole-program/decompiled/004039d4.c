/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004039d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004039d4(undefined4 *param_1,char *param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  cVar1 = *param_2;
  uVar3 = (uint)(byte)param_2[1];
  if (cVar1 == '\n') {
    do {
      *param_1 = 0;
      param_1 = param_1 + 1;
      iVar4 = param_3 + -1;
      bVar2 = 0 < param_3;
      param_3 = iVar4;
    } while (iVar4 != 0 && bVar2);
  }
  else if (cVar1 == '\f') {
    do {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1 = param_1 + 4;
      iVar4 = param_3 + -1;
      bVar2 = 0 < param_3;
      param_3 = iVar4;
    } while (iVar4 != 0 && bVar2);
  }
  else if (cVar1 == '\r') {
    do {
      iVar4 = *(int *)(param_2 + uVar3 + 2);
      FUN_004039d4(param_1,*(char **)(param_2 + uVar3 + 10),*(int *)(param_2 + uVar3 + 6));
      iVar5 = param_3 + -1;
      bVar2 = 0 < param_3;
      param_1 = (undefined4 *)((int)param_1 + iVar4);
      param_3 = iVar5;
    } while (iVar5 != 0 && bVar2);
  }
  else {
    if (cVar1 != '\x0e') {
      FUN_004026d0(CONCAT31((int3)((uint)param_1 >> 8),2));
      return;
    }
    do {
      iVar4 = *(int *)(param_2 + uVar3 + 2);
      FUN_004039ac((int)param_1,(int)param_2);
      iVar5 = param_3 + -1;
      bVar2 = 0 < param_3;
      param_1 = (undefined4 *)((int)param_1 + iVar4);
      param_3 = iVar5;
    } while (iVar5 != 0 && bVar2);
  }
  return;
}

