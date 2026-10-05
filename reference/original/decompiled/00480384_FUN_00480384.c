/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00480384. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_00480384(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  int *piVar7;
  dword local_24;
  undefined4 local_20 [4];

  bVar6 = 0;
  iVar3 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  DAT_0048c54c = ((short)event_stack[event_cursor].a * iVar3) % (iVar3 * 0xb);
  iVar3 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  DAT_0048c550 = (((short)event_stack[event_cursor].a * iVar3) / (iVar3 * 0xb)) * iVar3;
  iVar3 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
  if (0 < iVar3) {
    local_24 = 1;
    do {
      DAT_0048c56c = local_24;
      neighbor_index = local_24;
      iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      if ((int)local_24 % (iVar1 >> 2) == 0) {
        scratch_index =
             *(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                      (int)(short)event_stack[event_cursor].a) - 1;
      }
      else {
        scratch_index =
             (dword)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                             (int)(short)event_stack[event_cursor].a);
      }
      FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),local_20,
                   *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
      puVar4 = local_20;
      puVar5 = &DAT_0048c53c;
      for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
        puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
      }
      iVar1 = (int)(short)event_stack[event_cursor].b - (int)(short)event_stack[event_cursor].a;
      if (iVar1 == -0xb) {
        DAT_0048c568 = 4;
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 3;
        }
        door_opened = (dword)((int)neighbor_index % (iVar1 >> 2) != 0);
        FUN_00480a90(param_1);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        DAT_0048c54c = ((short)event_stack[event_cursor].b * iVar1) % (iVar1 * 0xb);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
        DAT_0048c550 = (((short)event_stack[event_cursor].b * iVar1) / (iVar1 * 0xb)) * iVar1;
      }
      else if (iVar1 == -1) {
        DAT_0048c568 = 2;
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 3;
        }
        door_opened = (dword)((int)neighbor_index % (iVar1 >> 2) != 0);
        FUN_00480a90(param_1);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        DAT_0048c54c = ((short)event_stack[event_cursor].b * iVar1) % (iVar1 * 0xb);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
        DAT_0048c550 = (((short)event_stack[event_cursor].b * iVar1) / (iVar1 * 0xb)) * iVar1;
      }
      else if (iVar1 == 1) {
        DAT_0048c568 = 3;
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 3;
        }
        door_opened = (dword)((int)neighbor_index % (iVar1 >> 2) != 0);
        FUN_00480a90(param_1);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        DAT_0048c54c = ((short)event_stack[event_cursor].a * iVar1) % (iVar1 * 0xb);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
        DAT_0048c550 = (((short)event_stack[event_cursor].a * iVar1) / (iVar1 * 0xb)) * iVar1;
      }
      else if (iVar1 == 0xb) {
        DAT_0048c568 = 1;
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        if (iVar1 < 0) {
          iVar1 = iVar1 + 3;
        }
        door_opened = (dword)((int)neighbor_index % (iVar1 >> 2) != 0);
        FUN_00480a90(param_1);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
        DAT_0048c54c = ((short)event_stack[event_cursor].a * iVar1) % (iVar1 * 0xb);
        iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x30);
        DAT_0048c550 = (((short)event_stack[event_cursor].a * iVar1) / (iVar1 * 0xb)) * iVar1;
      }
      iVar1 = *(int *)(*(int *)(param_1 + 0x254) + 0x2c);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      if ((int)neighbor_index % (iVar1 >> 2) == 0) {
        piVar7 = DAT_0048c51c;
        piVar2 = (int *)FUN_0041dad8((int)DAT_0048c514);
        FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar7);
      }
      else {
        piVar7 = DAT_0048c51c;
        piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
        FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar7);
      }
      piVar7 = DAT_0048c514;
      piVar2 = (int *)FUN_00421a54(DAT_0048c510);
      FUN_0041a5b8(piVar2,DAT_0048c578,DAT_0048c57c,piVar7);
      local_24 = local_24 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  neighbor_index = *(dword *)(*(int *)(param_1 + 0x254) + 0x2c);
  scratch_index =
       (dword)*(byte *)(original_hero.floor * 0x7b + 0x4b8936 +
                       (int)(short)event_stack[event_cursor].a);
  FUN_0040923c(0,0,*(undefined4 *)(*(int *)(param_1 + 0x254) + 0x2c),local_20,
               *(undefined4 *)(*(int *)(param_1 + 0x254) + 0x30));
  puVar4 = local_20;
  puVar5 = &DAT_0048c53c;
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
  }
  iVar3 = (int)(short)event_stack[event_cursor].b - (int)(short)event_stack[event_cursor].a;
  if (iVar3 == -0xb) {
    DAT_0048c568 = 4;
    door_opened = 1;
    FUN_00480a90(param_1);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].b *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c)) %
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
    DAT_0048c550 = (((int)(short)event_stack[event_cursor].b *
                    *(int *)(*(int *)(param_1 + 0x254) + 0x30)) /
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  }
  else if (iVar3 == -1) {
    DAT_0048c568 = 2;
    door_opened = 1;
    FUN_00480a90(param_1);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].b *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c)) %
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
    DAT_0048c550 = (((int)(short)event_stack[event_cursor].b *
                    *(int *)(*(int *)(param_1 + 0x254) + 0x30)) /
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  }
  else if (iVar3 == 1) {
    DAT_0048c568 = 3;
    door_opened = 1;
    FUN_00480a90(param_1);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c)) %
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
    DAT_0048c550 = (((int)(short)event_stack[event_cursor].a *
                    *(int *)(*(int *)(param_1 + 0x254) + 0x30)) /
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  }
  else if (iVar3 == 0xb) {
    DAT_0048c568 = 1;
    door_opened = 1;
    FUN_00480a90(param_1);
    DAT_0048c54c = ((int)(short)event_stack[event_cursor].a *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x2c)) %
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x2c) * 0xb);
    DAT_0048c550 = (((int)(short)event_stack[event_cursor].a *
                    *(int *)(*(int *)(param_1 + 0x254) + 0x30)) /
                   (*(int *)(*(int *)(param_1 + 0x254) + 0x30) * 0xb)) *
                   *(int *)(*(int *)(param_1 + 0x254) + 0x30);
  }
  piVar7 = DAT_0048c51c;
  piVar2 = (int *)FUN_0041dad8(DAT_0048c518);
  FUN_0041a5b8(piVar2,DAT_0048c54c,DAT_0048c550,piVar7);
  iVar3 = original_hero.floor * 0x7b;
  *(undefined *)(iVar3 + 0x4b8936 + (int)(short)event_stack[event_cursor].b) =
       *(undefined *)(iVar3 + 0x4b8936 + (int)(short)event_stack[event_cursor].a);
  *(undefined *)(iVar3 + 0x4b8936 + (int)(short)event_stack[event_cursor].a) = 6;
  return;
}
