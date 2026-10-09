/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0047e7d4.
 * Inferred types and shared tails require assembly review. */

void FUN_0047e7d4(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined *puVar3;
  OriginalHero_conflict *pOVar4;
  int iVar5;
  int extraout_ECX;
  uint uVar6;
  undefined4 extraout_EDX;
  int iVar7;
  uint uVar8;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 local_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = (undefined4 *)0x0;
  puStack_20 = &LAB_0047ea93;
  local_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_24;
  puVar3 = &stack0xfffffffc;
  local_8 = param_1;
  if (*(char *)(*(int *)(param_1 + 0x330) + 0x28) == '\x01') {
    puStack_28 = (undefined *)0x47e810;
    FUN_00431188(*(int **)(param_1 + 0x2d8),0,param_3);
    puVar3 = puStack_1c;
  }
  puStack_1c = puVar3;
  puStack_28 = (undefined *)0x47e820;
  FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
  puStack_2c = &LAB_0047ea42;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  puStack_28 = &stack0xfffffffc;
  FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048c600);
  FUN_00402710();
  if (original_hero._628_4_ == -4) {
    iVar7 = 0;
    iVar5 = 0;
    uVar6 = 0;
    pOVar4 = &original_hero;
    do {
      iVar1 = pOVar4->hp;
      iVar7 = iVar7 + iVar1;
      uVar8 = uVar6 & 0x80000001;
      if ((int)uVar8 < 0) {
        uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
      }
      if (uVar8 != 0) {
        iVar1 = -iVar1;
      }
      iVar5 = iVar5 + iVar1;
      uVar6 = uVar6 + 1;
      pOVar4 = (OriginalHero_conflict *)&pOVar4->attack;
    } while (uVar6 != 0xa4);
    if ((iVar7 == original_hero._656_4_) && (iVar5 == original_hero._660_4_)) {
      FUN_00454de8(local_8,0xa4,iVar5);
      tile_class_or_message = 0x85;
      FUN_0044cb34(local_8);
    }
    else {
      piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
      (**(code **)(*piVar2 + 0xc))(piVar2,0,&local_c);
      FUN_0040369c((int *)&DAT_0048c5d4,local_c,(undefined4 *)"\\save0.dat");
      FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
      FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
      FUN_00402710();
      FUN_004041f0((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
      FUN_00402710();
      FUN_004041f0((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
      FUN_00402710();
      FUN_004042b8(&DAT_0048c600);
      FUN_00402710();
      FUN_0042cf78((uint *)"Donot use this save data.");
    }
  }
  else {
    piVar2 = *(int **)(*(int *)(local_8 + 0x444) + 0x118);
    (**(code **)(*piVar2 + 0xc))(piVar2,0,&local_c);
    FUN_0040369c((int *)&DAT_0048c5d4,local_c,(undefined4 *)"\\save0.dat");
    FUN_0040414d((undefined4 *)&DAT_0048c600,DAT_0048c5d4);
    FUN_0040458d((HANDLE *)&DAT_0048c600,(HANDLE)0x1);
    FUN_00402710();
    FUN_004041f0((HANDLE *)&DAT_0048c600,original_maps,0x1881,(uint *)0x0);
    FUN_00402710();
    FUN_004041f0((HANDLE *)&DAT_0048c600,&original_hero,0x2ac,(uint *)0x0);
    FUN_00402710();
    FUN_004042b8(&DAT_0048c600);
    FUN_00402710();
    FUN_0042cf78((uint *)"Donot use this save data.");
  }
  *in_FS_OFFSET = uStack_30;
  if (*(char *)(*(int *)(local_8 + 0x330) + 0x28) == '\x01') {
    puStack_28 = (undefined *)0x47ea75;
    FUN_0047c8f8();
    puStack_28 = (undefined *)0x47ea7d;
    FUN_0047c2bc(local_8,extraout_EDX,extraout_ECX);
  }
  *in_FS_OFFSET = local_24;
  puStack_1c = &LAB_0047ea9a;
  puStack_20 = (undefined *)0x47ea92;
  FUN_004034dc((int *)&local_c);
  return;
}

