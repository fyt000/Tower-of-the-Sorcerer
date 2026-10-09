/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042035c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042035c(int param_1,int param_2)

{
  int iVar1;
  
  switch(*(undefined2 *)(param_2 + 4)) {
  case 0:
    FUN_00420424(param_1,*(int *)(param_1 + 0xc) - (uint)*(ushort *)(param_1 + 8));
    return;
  case 1:
    FUN_00420424(param_1,(uint)*(ushort *)(param_1 + 8) + *(int *)(param_1 + 0xc));
    return;
  case 2:
    iVar1 = FUN_004202c4(param_1);
    FUN_00420424(param_1,*(int *)(param_1 + 0xc) - iVar1);
    return;
  case 3:
    iVar1 = FUN_004202c4(param_1);
    FUN_00420424(param_1,iVar1 + *(int *)(param_1 + 0xc));
    return;
  case 4:
    FUN_00420424(param_1,(int)*(short *)(param_2 + 6));
    return;
  case 5:
    if (*(char *)(param_1 + 0x1d) != '\0') {
      FUN_00420424(param_1,(int)*(short *)(param_2 + 6));
      return;
    }
    break;
  case 6:
    FUN_00420424(param_1,0);
    return;
  case 7:
    FUN_00420424(param_1,*(int *)(param_1 + 0x14));
    return;
  }
  return;
}

