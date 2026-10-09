/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429d5c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00429d5c(int **param_1,int *param_2)

{
  bool bVar1;
  COLORREF CVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (((*(byte *)(param_1 + 7) & 0x10) == 0) &&
     ((((*param_2 == 0x201 || (*param_2 == 0x203)) && (bVar1 = FUN_00413b6c((int)param_1), !bVar1))
      && (*(char *)(param_1 + 0xf) == '\x01')))) {
    bVar1 = FUN_00415410((int *)param_1,param_2);
    if (bVar1) {
      return;
    }
    *(byte *)((int)param_1 + 0x36) = DAT_00429e7c | *(byte *)((int)param_1 + 0x36);
    FUN_00402d0c((int *)param_1,(ushort *)param_2);
    return;
  }
  iVar4 = *param_2;
  if (iVar4 == 0x102) {
    uVar5 = FUN_00415ff8(param_1,(int)param_2);
    if ((char)uVar5 != '\0') {
      return;
    }
    if (((*(short *)(param_2 + 1) == 0xd) || (*(short *)(param_2 + 1) == 0x1b)) &&
       (bVar1 = FUN_004295d4((int *)param_1), bVar1)) {
      FUN_004295f8((int *)param_1,0);
      return;
    }
  }
  else {
    if (iVar4 - 0x132U < 7) {
      CVar2 = FUN_00419b00(param_1[0x11][4]);
      SetTextColor((HDC)param_2[1],CVar2);
      uVar3 = FUN_0041a14c((int)param_1[0x2f]);
      CVar2 = FUN_00419b00(uVar3);
      SetBkColor((HDC)param_2[1],CVar2);
      iVar4 = FUN_0041a188((int)param_1[0x2f]);
      param_2[3] = iVar4;
      return;
    }
    if (((iVar4 - 0xbd32U < 7) && (DAT_0048a694 == '\0')) && (*(byte *)((int)param_1 + 0x109) < 2))
    {
      iVar4 = FUN_0041a188(param_1[8][0x2f]);
      param_2[3] = iVar4;
      return;
    }
  }
  FUN_0041549c(param_1,param_2);
  return;
}

