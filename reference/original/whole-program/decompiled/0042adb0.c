/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042adb0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042adb0(int **param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  WPARAM WVar3;
  int aiStack_18 [2];
  
  bVar1 = FUN_0041fecc(CONCAT22((short)((uint)param_1 >> 0x10),*(undefined2 *)(param_2 + 4)));
  if (((*(char *)(param_1 + 0xf) == '\x01') && (*(char *)((int)param_1 + 0x116) != '\0')) &&
     (((bVar1 & 1) == 0 || ((bVar1 & 4) != 0)))) {
    FUN_004052e0(*(undefined4 *)(param_2 + 8),aiStack_18);
    WVar3 = root_0042aae8(param_1,aiStack_18,1);
    if ((-1 < (int)WVar3) && (bVar2 = FUN_0042aa18((int *)param_1,WVar3), bVar2)) {
      FUN_00413ad4(param_1,'\0');
      return;
    }
  }
  FUN_00413f58(param_1,param_2);
  if ((*(char *)(param_1 + 0xf) == '\x01') &&
     ((*(char *)((int)param_1 + 0x116) == '\0' || (((bVar1 & 4) == 0 && ((bVar1 & 1) == 0)))))) {
    FUN_00413ad4(param_1,'\0');
  }
  return;
}

