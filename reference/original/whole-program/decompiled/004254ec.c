/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004254ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004254ec(int param_1,int *param_2,int param_3)

{
  char cVar1;
  POINT pt;
  int *piVar2;
  int iVar3;
  BOOL BVar4;
  UINT UVar5;
  POINT local_20;
  int local_18 [2];
  
  FUN_004052e0(*(undefined4 *)(param_3 + 8),local_18);
  FUN_0041324c(param_2,local_18,&local_20.x);
  piVar2 = FUN_00412be8(&local_20,1);
  iVar3 = thunk_FUN_00423e0d((int)piVar2);
  if ((iVar3 == 0) || (*(char *)(iVar3 + 0x5d) == '\0')) {
    FUN_00425618(param_1);
  }
  else {
    if (iVar3 == *(int *)(param_1 + 0x40)) {
      FUN_004052e0(*(undefined4 *)(param_3 + 8),local_18);
      FUN_0041324c(param_2,local_18,&local_20.x);
      pt.y = local_20.y;
      pt.x = local_20.x;
      BVar4 = PtInRect((RECT *)(param_1 + 0x44),pt);
      if (BVar4 != 0) {
        return;
      }
    }
    cVar1 = *(char *)(param_1 + 0x38);
    if (cVar1 == '\0') {
      UVar5 = *(UINT *)(param_1 + 0x54);
    }
    else {
      UVar5 = *(UINT *)(param_1 + 0x58);
    }
    FUN_00425618(param_1);
    *(char *)(param_1 + 0x38) = cVar1;
    *(int *)(param_1 + 0x40) = iVar3;
    FUN_0042548c(param_1,UVar5,0);
  }
  return;
}

