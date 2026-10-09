/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423680.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00423680(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint extraout_ECX;
  undefined4 extraout_EDX;
  uint uVar3;
  int iVar4;
  undefined4 local_10;
  
  uVar1 = param_1;
  local_10 = param_3;
  if (*(char *)(param_1 + 0x11a) == '\x02') {
    local_10 = param_3 & 0xffffff00;
    uVar1 = FUN_004219b8(param_1);
    if (-1 < (int)(uVar1 - 1)) {
      iVar4 = 0;
      uVar3 = uVar1;
      do {
        iVar2 = FUN_00421a04(param_1,iVar4);
        uVar1 = FUN_00423680(iVar2,extraout_EDX,extraout_ECX);
        if ((char)uVar1 == '\0') goto LAB_004236d8;
        iVar4 = iVar4 + 1;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  local_10 = CONCAT31(local_10._1_3_,1);
  if (*(short *)(param_1 + 0x172) != 0) {
    uVar1 = (**(code **)(param_1 + 0x170))(*(undefined4 *)(param_1 + 0x174),param_1,&local_10);
  }
LAB_004236d8:
  return CONCAT31((int3)(uVar1 >> 8),(undefined)local_10);
}

