/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040769c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040769c(int *param_1)

{
  int iVar1;
  undefined3 uVar3;
  int iVar2;
  
  iVar1 = *param_1;
  uVar3 = (undefined3)((uint)iVar1 >> 8);
  if (iVar1 < -0x3fffff6d) {
    iVar2 = iVar1;
    if (iVar1 == -0x3fffff6e) {
LAB_00407700:
      return CONCAT31((int3)((uint)iVar2 >> 8),6);
    }
    if (iVar1 < -0x3fffff71) {
      if (iVar1 == -0x3fffff72) {
        return CONCAT31(uVar3,7);
      }
      if (iVar1 == -0x3ffffffb) {
        return 0xb;
      }
      if (iVar1 == -0x3fffff74) {
        return 4;
      }
      iVar2 = iVar1 + 0x3fffff73;
      if (iVar2 == 0) goto LAB_00407709;
    }
    else {
      iVar2 = iVar1 + 0x3fffff6f;
      if (iVar1 + 0x3fffff71U < 2) goto LAB_00407700;
      if (iVar2 == 0) {
        return 8;
      }
    }
  }
  else if (iVar1 < -0x3fffff69) {
    if (iVar1 == -0x3fffff6a) {
      return CONCAT31(uVar3,0xc);
    }
    iVar2 = iVar1 + 0x3fffff6d;
    if (iVar2 == 0) {
LAB_00407709:
      return CONCAT31((int3)((uint)iVar2 >> 8),9);
    }
    if (iVar1 == -0x3fffff6c) {
      return 3;
    }
    iVar2 = iVar1 + 0x3fffff6b;
    if (iVar2 == 0) {
      return 5;
    }
  }
  else {
    if (iVar1 == -0x3fffff03) {
      return 0xe;
    }
    iVar2 = iVar1 + 0x3ffffec6;
    if (iVar2 == 0) {
      return 0xd;
    }
  }
  return CONCAT31((int3)((uint)iVar2 >> 8),0x15);
}

