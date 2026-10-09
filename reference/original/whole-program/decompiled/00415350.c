/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00415350.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * FUN_00415350(int param_1,int *param_2,byte param_3)

{
  POINT pt;
  int *piVar1;
  BOOL BVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  LONG LVar6;
  LONG LVar7;
  LONG local_28;
  LONG local_24;
  RECT local_20;
  
  if ((*(int *)(param_1 + 0xb0) != 0) &&
     (iVar5 = *(int *)(*(int *)(param_1 + 0xb0) + 8) + -1, -1 < iVar5)) {
    do {
      piVar1 = (int *)FUN_00409a40(*(undefined4 **)(param_1 + 0xb0),iVar5);
      FUN_00409224(*param_2 - piVar1[9],param_2[1] - piVar1[10],&local_28);
      LVar6 = local_28;
      LVar7 = local_24;
      (**(code **)(*piVar1 + 0x2c))(piVar1,&local_20);
      pt.y = LVar7;
      pt.x = LVar6;
      BVar2 = PtInRect(&local_20,pt);
      if (BVar2 != 0) {
        if ((*(byte *)(piVar1 + 7) & 0x10) != 0) {
          if (*(char *)((int)piVar1 + 0x37) != '\0') {
            return piVar1;
          }
          if ((*(byte *)((int)piVar1 + 0x35) & 4) == 0) {
            return piVar1;
          }
        }
        if ((*(char *)((int)piVar1 + 0x37) != '\0') && ((*(byte *)(piVar1 + 0xe) | param_3) != 0)) {
          uVar3 = FUN_004052f4((undefined2 *)&local_28);
          iVar4 = FUN_00413cb8(piVar1,0xb00a,0,uVar3);
          if (iVar4 != 0) {
            return piVar1;
          }
        }
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != -1);
  }
  return (int *)0x0;
}

