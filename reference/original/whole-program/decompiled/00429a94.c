/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429a94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00429a94(int **param_1,UINT *param_2,HWND param_3,WNDPROC param_4)

{
  undefined *puVar1;
  char cVar2;
  bool bVar3;
  int **ppiVar4;
  undefined4 uVar5;
  HWND hWndTo;
  UINT UVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  LPPOINT lpPoints;
  undefined4 uStack_28;
  code *pcStack_24;
  undefined *puStack_20;
  undefined8 uStack_10;
  int **ppiStack_8;
  
  puStack_20 = &stack0xfffffffc;
  pcStack_24 = thunk_FUN_00402f4c;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  UVar6 = *param_2;
  ppiStack_8 = param_1;
  if ((int)UVar6 < 0x105) {
    if (UVar6 != 0x104) {
      if ((int)UVar6 < 0x88) {
        if (UVar6 == 0x87) {
          puStack_20 = &stack0xfffffffc;
          bVar3 = FUN_004295d4((int *)param_1);
          puVar1 = puStack_20;
          if (bVar3) {
            param_2[3] = 4;
            *in_FS_OFFSET = uStack_28;
            return;
          }
        }
        else if (UVar6 == 7) {
          puStack_20 = &stack0xfffffffc;
          ppiVar4 = FUN_0041fffc(param_1);
          uVar5 = FUN_00422478((int *)ppiVar4,(int *)ppiStack_8);
          puVar1 = puStack_20;
          if ((char)uVar5 == '\0') {
            *in_FS_OFFSET = uStack_28;
            return;
          }
        }
        else if (UVar6 == 8) {
          puVar1 = &stack0xfffffffc;
          if ((*(byte *)((int)param_1 + 0x36) & 0x20) != 0) {
            *in_FS_OFFSET = uStack_28;
            return;
          }
        }
        else {
          puVar1 = &stack0xfffffffc;
          if ((UVar6 == 0x84) && (puVar1 = &stack0xfffffffc, (*(byte *)(param_1 + 7) & 0x10) != 0))
          {
            param_2[3] = 0xffffffff;
            *in_FS_OFFSET = uStack_28;
            return;
          }
        }
        goto LAB_00429cfb;
      }
      if (UVar6 != 0x100) {
        if (UVar6 != 0x101) {
          puVar1 = &stack0xfffffffc;
          if (UVar6 == 0x102) {
            puStack_20 = &stack0xfffffffc;
            uVar5 = FUN_00415ff8(param_1,(int)param_2);
            if ((char)uVar5 != '\0') {
              *in_FS_OFFSET = uStack_28;
              return;
            }
            if (((*(short *)(param_2 + 1) == 0xd) ||
                (puVar1 = puStack_20, *(short *)(param_2 + 1) == 0x1b)) &&
               (bVar3 = FUN_004295d4((int *)ppiStack_8), puVar1 = puStack_20, bVar3)) {
              FUN_004295f8((int *)ppiStack_8,0);
              *in_FS_OFFSET = uStack_28;
              return;
            }
          }
          goto LAB_00429cfb;
        }
        goto LAB_00429c20;
      }
    }
    puVar1 = &stack0xfffffffc;
    if ((param_3 != (HWND)param_1[0x47]) &&
       (puStack_20 = &stack0xfffffffc, cVar2 = FUN_00415e38(param_1,(int)param_2),
       puVar1 = puStack_20, cVar2 != '\0')) {
      *in_FS_OFFSET = uStack_28;
      return;
    }
  }
  else {
    if (0xbd00 < (int)UVar6) {
      if (((UVar6 != 0xbd02) && (UVar6 != 0xbd04)) && (puVar1 = &stack0xfffffffc, UVar6 != 0xbd06))
      goto LAB_00429cfb;
LAB_00429ce7:
      (*(code *)(*param_1)[0x10])(param_1,param_2);
      *in_FS_OFFSET = uStack_28;
      return;
    }
    if (UVar6 == 0xbd00) goto LAB_00429ce7;
    if (UVar6 != 0x105) {
      if (UVar6 == 0x200) {
        puStack_20 = &stack0xfffffffc;
        FUN_004254ec(DAT_0048a6f8,(int *)param_1,(int)param_2);
        puVar1 = puStack_20;
      }
      else {
        puVar1 = &stack0xfffffffc;
        if ((UVar6 == 0x205) &&
           (puStack_20 = &stack0xfffffffc, uVar5 = FUN_00427ee0((int)param_1), puVar1 = puStack_20,
           (char)uVar5 != '\0')) {
          uStack_10._0_4_ = (int)*(short *)(param_2 + 2);
          uStack_10._4_4_ = (int)*(short *)((int)param_2 + 10);
          UVar6 = 1;
          lpPoints = (LPPOINT)&uStack_10;
          hWndTo = (HWND)FUN_00416cbc((int *)ppiStack_8);
          MapWindowPoints(param_3,hWndTo,lpPoints,UVar6);
          *(undefined2 *)(param_2 + 2) = (undefined2)uStack_10;
          *(undefined2 *)((int)param_2 + 10) = uStack_10._4_2_;
          (*(code *)(*ppiStack_8)[0x10])(ppiStack_8,param_2);
          *in_FS_OFFSET = uStack_28;
          return;
        }
      }
      goto LAB_00429cfb;
    }
LAB_00429c20:
    puStack_20 = &stack0xfffffffc;
    uVar5 = FUN_00415f34(param_1,(int)param_2);
    puVar1 = puStack_20;
    if ((char)uVar5 != '\0') {
      *in_FS_OFFSET = uStack_28;
      return;
    }
  }
LAB_00429cfb:
  puStack_20 = puVar1;
  UVar6 = CallWindowProcA(param_4,param_3,*param_2,param_2[1],param_2[2]);
  param_2[3] = UVar6;
  if ((*param_2 == 0x203) && ((*(byte *)(ppiStack_8 + 0xd) & 0x80) != 0)) {
    FUN_00402cdc((int *)ppiStack_8,extraout_EDX,extraout_ECX);
  }
  *in_FS_OFFSET = uStack_28;
  return;
}

