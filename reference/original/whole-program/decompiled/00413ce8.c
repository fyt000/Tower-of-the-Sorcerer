/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413ce8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413ce8(int **param_1,int *param_2)

{
  int iVar1;
  char cVar2;
  int **ppiVar3;
  
  if (((((*(byte *)(param_1 + 7) & 0x10) != 0) &&
       (ppiVar3 = FUN_0041fffc(param_1), ppiVar3 != (int **)0x0)) && (ppiVar3[0x4c] != (int *)0x0))
     && (cVar2 = (**(code **)*ppiVar3[0x4c])(ppiVar3[0x4c],param_1,param_2), cVar2 != '\0')) {
    return;
  }
  iVar1 = *param_2;
  if ((0x1ff < iVar1) && (iVar1 < 0x20a)) {
    if (((*(byte *)(param_1 + 0xd) & 0x80) == 0) &&
       (((iVar1 == 0x203 || (iVar1 == 0x206)) || (iVar1 == 0x209)))) {
      *param_2 = *param_2 + -2;
    }
    iVar1 = *param_2;
    if (iVar1 == 0x200) {
      FUN_004254ec(DAT_0048a6f8,(int *)param_1,(int)param_2);
    }
    else {
      if (iVar1 != 0x201) {
        if (iVar1 == 0x202) {
          *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) & 0xfe;
          goto LAB_00413d86;
        }
        if (iVar1 != 0x203) goto LAB_00413d86;
      }
      if (*(char *)(param_1 + 0xf) == '\x01') {
        FUN_00413ad4(param_1,'\x01');
        return;
      }
      *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) | 1;
    }
  }
LAB_00413d86:
  FUN_00402d0c((int *)param_1,(ushort *)param_2);
  return;
}

