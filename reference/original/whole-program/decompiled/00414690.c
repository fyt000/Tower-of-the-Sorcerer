/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414690.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00414690(int *param_1,char param_2,undefined4 param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  BOOL BVar5;
  int iVar6;
  
  if (param_2 == '\x01') {
    piVar1 = (int *)(*(int *)(param_4 + -4) + 4);
    *piVar1 = *piVar1 + param_1[0xc];
  }
  else if (param_2 == '\x02') {
    piVar1 = (int *)(*(int *)(param_4 + -4) + 0xc);
    *piVar1 = *piVar1 - param_1[0xc];
  }
  else if (param_2 == '\x03') {
    **(int **)(param_4 + -4) = **(int **)(param_4 + -4) + param_1[0xb];
  }
  else if (param_2 == '\x04') {
    piVar1 = (int *)(*(int *)(param_4 + -4) + 8);
    *piVar1 = *piVar1 - param_1[0xb];
  }
  switch(param_2) {
  case '\x01':
    iVar6 = **(int **)(param_4 + -4);
    iVar2 = FUN_00414688(*(int *)(*(int *)(param_4 + -4) + 8) - iVar6,param_1[0xb]);
    (**(code **)(*param_1 + 0x4c))
              (param_1,iVar6,*(int *)(*(int *)(param_4 + -4) + 4) - param_1[0xc],param_1[0xc],iVar2)
    ;
    break;
  case '\x02':
    iVar6 = **(int **)(param_4 + -4);
    iVar2 = FUN_00414688(*(int *)(*(int *)(param_4 + -4) + 8) - iVar6,param_1[0xb]);
    (**(code **)(*param_1 + 0x4c))
              (param_1,iVar6,*(undefined4 *)(*(int *)(param_4 + -4) + 0xc),param_1[0xc],iVar2);
    break;
  case '\x03':
    iVar6 = param_1[0xb];
    iVar2 = *(int *)(*(int *)(param_4 + -4) + 4);
    iVar4 = iVar6;
    iVar3 = FUN_00414688(*(int *)(*(int *)(param_4 + -4) + 0xc) - iVar2,param_1[0xc]);
    (**(code **)(*param_1 + 0x4c))(param_1,**(int **)(param_4 + -4) - iVar6,iVar2,iVar3,iVar4);
    break;
  case '\x04':
    iVar6 = param_1[0xb];
    iVar2 = *(int *)(*(int *)(param_4 + -4) + 4);
    iVar4 = FUN_00414688(*(int *)(*(int *)(param_4 + -4) + 0xc) - iVar2,param_1[0xc]);
    (**(code **)(*param_1 + 0x4c))
              (param_1,*(undefined4 *)(*(int *)(param_4 + -4) + 8),iVar2,iVar4,iVar6);
    break;
  case '\x05':
    BVar5 = IsRectEmpty(*(RECT **)(param_4 + -4));
    if (BVar5 == 0) {
      FUN_00413138(param_1,*(int **)(param_4 + -4));
    }
  }
  return;
}

