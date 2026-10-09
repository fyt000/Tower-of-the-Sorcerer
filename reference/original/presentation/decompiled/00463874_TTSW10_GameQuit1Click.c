/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00463874.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TTSW10_GameQuit1Click(int param_1,undefined4 param_2)

{
  int iVar1;
  int extraout_ECX;
  undefined4 extraout_EDX;
  
  iVar1 = FUN_0042cec8((uint *)"This game is over. Is it true?",
                       CONCAT31((int3)((uint)param_2 >> 8),2),_DAT_004638f0,0);
  if (iVar1 == 6) {
    if (*(char *)(*(int *)(param_1 + 0x330) + 0x28) == '\x01') {
      FUN_00431188(*(int **)(param_1 + 0x2d8),extraout_EDX,extraout_ECX);
    }
    FUN_00402c34(DAT_0048c514);
    FUN_00402c34(DAT_0048c518);
    FUN_00402c34(DAT_0048c51c);
    FUN_00402c34(DAT_0048c520);
    FUN_00402c34(DAT_0048c524);
    FUN_00402c34(DAT_0048c528);
    FUN_00425018();
  }
  return;
}

