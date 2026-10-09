/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004085f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Unable to track spacebase fully for stack */

void FUN_004085f0(undefined4 param_1,int *param_2,undefined param_3,undefined1 param_4 [10])

{
  code *pcVar1;
  undefined4 uVar2;
  int *piVar3;
  code *extraout_ECX;
  int extraout_EDX;
  int iVar4;
  undefined *puVar5;
  undefined4 uStack_10;
  
  iVar4 = (uint)*(byte *)(*param_2 + 2 + (uint)*(byte *)(*param_2 + 1)) * 4;
  if (*(char *)((int)param_2 + 0xb) == -1) {
    uStack_10 = 0x40867f;
    (**(code **)(&DAT_00408647 + iVar4))(param_1,param_2,param_2[2] & 0xffffff);
  }
  else {
    pcVar1 = *(code **)(&DAT_00408647 + iVar4);
    puVar5 = (undefined *)((int)&uStack_10 + -*(int *)(&DAT_00408633 + iVar4));
    *(undefined4 *)((int)&uStack_10 + -*(int *)(&DAT_00408633 + iVar4)) = 0x40861d;
    piVar3 = (int *)(*pcVar1)();
    uVar2 = *(undefined4 *)(extraout_EDX + 0x10);
    if (*(byte *)(extraout_EDX + 0xb) < 0xfe) {
      *(undefined4 *)(puVar5 + -4) = 0x408631;
      (*extraout_ECX)(piVar3,uVar2);
    }
    else {
      pcVar1 = *(code **)((int)(short)extraout_ECX + *piVar3);
      *(undefined4 *)(puVar5 + -4) = 0x40862d;
      (*pcVar1)();
    }
  }
  return;
}

