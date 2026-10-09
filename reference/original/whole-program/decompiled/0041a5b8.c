/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041a5b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041a5b8(int *param_1,int param_2,int param_3,int *param_4)

{
  char cVar1;
  uint uVar2;
  COLORREF CVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_18 [4];
  int local_8;
  
  if (param_4 != (int *)0x0) {
    local_8 = param_3;
    cVar1 = (**(code **)(*param_4 + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(*param_1 + 0x10))();
      FUN_0041aa24(param_1,DAT_0041a660);
      uVar2 = FUN_0041a14c(param_1[5]);
      CVar3 = FUN_00419b00(uVar2);
      SetBkColor((HDC)param_1[1],CVar3);
      CVar3 = FUN_00419b00(*(uint *)(param_1[3] + 0x10));
      SetTextColor((HDC)param_1[1],CVar3);
      iVar4 = (**(code **)(*param_4 + 0x1c))();
      iVar4 = iVar4 + local_8;
      puVar6 = local_18;
      iVar5 = (**(code **)(*param_4 + 0x20))();
      FUN_0040923c(param_2,local_8,iVar5 + param_2,puVar6,iVar4);
      (**(code **)(*param_4 + 0x10))(param_4,param_1,local_18);
      (**(code **)(*param_1 + 0xc))();
    }
  }
  return;
}

