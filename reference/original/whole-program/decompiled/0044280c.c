/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044280c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void TTSW10_formactivate(int *param_1)

{
  LPSTR lpBuffer;
  char *pcVar1;
  uint uVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_130;
  UINT uSize;
  undefined4 uStack_124;
  code *pcStack_120;
  undefined *puStack_11c;
  undefined4 auStack_10c [64];
  undefined4 *puStack_c;
  int *piStack_8;
  
  puStack_11c = &stack0xfffffffc;
  puStack_c = (undefined4 *)0x0;
  pcStack_120 = thunk_FUN_00403140;
  uStack_124 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_124;
  original_hero._628_4_ = 0xfffffffc;
  original_hero.cycle_factor_minus_one = 0;
  original_hero.later_cycle = 0;
  original_hero._680_4_ = 0xc;
  piStack_8 = param_1;
  FUN_004135d4(DAT_0048c510,(uint *)"Tower of the Sorcerer Ver1.2");
  FUN_00406068((int *)&puStack_c);
  FUN_0040352c((int *)&DAT_0048c5e0,puStack_c);
  FUN_00403924((int *)&DAT_0048c5d8,0xff);
  uSize = 0xff;
  lpBuffer = FUN_00403814((undefined *)DAT_0048c5d8);
  uStackY_130 = 0x442898;
  GetWindowsDirectoryA(lpBuffer,uSize);
  pcVar1 = FUN_00403814((undefined *)DAT_0048c5d8);
  uVar2 = FUN_004060ac(pcVar1);
  FUN_00403924((int *)&DAT_0048c5d8,uVar2);
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0x38))();
  FUN_0040369c((int *)&DAT_0048c5d4,DAT_0048c5d8,(undefined4 *)"\\TSW12.INI");
  uStackY_130 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_130;
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0x50))
            (*(int **)(piStack_8[0x111] + 0x118),DAT_0048c5d4);
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0xc))
            (*(int **)(piStack_8[0x111] + 0x118),0,&puStack_c);
  FUN_0040352c((int *)&DAT_0048c5dc,puStack_c);
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0xc))
            (*(int **)(piStack_8[0x111] + 0x118),1,&puStack_c);
  FUN_0040352c((int *)&DAT_0048c5e0,puStack_c);
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0xc))
            (*(int **)(piStack_8[0x111] + 0x118),2,&puStack_c);
  FUN_00403988((undefined *)auStack_10c,puStack_c,0xff);
  FUN_00402918((undefined4 *)&DAT_0048c5ef,auStack_10c,10);
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0xc))
            (*(int **)(piStack_8[0x111] + 0x118),1,&puStack_c);
  FUN_00403658((int *)&puStack_c,(undefined4 *)"\\data\\center.bmp");
  FUN_0041c1e8(*(int *)(piStack_8[0x6e] + 0xac),(int)puStack_c);
  *in_FS_OFFSET = uStackY_130;
  (**(code **)(**(int **)(piStack_8[0x111] + 0x118) + 0xc))
            (*(int **)(piStack_8[0x111] + 0x118),0,&puStack_c);
  FUN_0040369c((int *)&DAT_0048c5d4,puStack_c,(undefined4 *)"\\option.dat");
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048c600,&DAT_00489b9c,10,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  FUN_00484f48(piStack_8);
  if (*(char *)(piStack_8[0x108] + 0x28) == '\x01') {
    FUN_0042c454(piStack_8[0x107],'\x01');
    FUN_0047d4a4((int)piStack_8);
    DAT_0048c56c = 0;
    FUN_0042c454(piStack_8[0x6d],'\0');
  }
  else {
    FUN_0047d4a4((int)piStack_8);
  }
  initialize_cycle();
  FUN_00454de8((int)piStack_8,extraout_EDX,extraout_ECX);
  if (*(char *)(piStack_8[0x108] + 0x28) == '\0') {
    FUN_00450880((int)piStack_8);
  }
  *in_FS_OFFSET = uStack_124;
  puStack_11c = &LAB_00442baf;
  pcStack_120 = (code *)0x442ba7;
  FUN_004034dc((int *)&puStack_c);
  return;
}

