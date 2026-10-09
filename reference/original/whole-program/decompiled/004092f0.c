/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004092f0.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004092f0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = DAT_004891c0[2];
  if (-1 < iVar4 + -1) {
    iVar3 = 0;
    do {
      iVar2 = FUN_00409a40(DAT_004891c0,iVar3);
      cVar1 = FUN_00402b90(iVar2,param_1);
      if (cVar1 != '\0') {
        return iVar2;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  iVar4 = (**(code **)(*DAT_004891c4 + 0x48))(DAT_004891c4,param_1);
  if (iVar4 < 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = (**(code **)(*DAT_004891c4 + 0x14))(DAT_004891c4,iVar4);
  }
  return iVar4;
}

