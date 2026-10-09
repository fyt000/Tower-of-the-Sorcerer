/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413d94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413d94(int param_1,int *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = *param_2;
  if (iVar2 == 0xc) {
    uVar3 = FUN_00406240((undefined4 *)param_2[2]);
    FUN_0040626c(*(int *)(param_1 + 0x40));
    *(undefined4 *)(param_1 + 0x40) = uVar3;
  }
  else if (iVar2 == 0xd) {
    puVar1 = *(undefined4 **)(param_1 + 0x40);
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)&DAT_00413e08;
    }
    puVar1 = FUN_00406168((undefined4 *)param_2[2],puVar1,param_2[1] + -1);
    iVar2 = FUN_004060ac((char *)puVar1);
    param_2[3] = iVar2;
  }
  else if (iVar2 == 0xe) {
    if (*(char **)(param_1 + 0x40) == (char *)0x0) {
      param_2[3] = 0;
    }
    else {
      iVar2 = FUN_004060ac(*(char **)(param_1 + 0x40));
      param_2[3] = iVar2;
    }
  }
  return;
}

