/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041389c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined FUN_0041389c(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  BOOL BVar4;
  RECT local_28;
  tagRECT local_18;
  undefined local_5;
  
  local_5 = 1;
  puVar1 = *(undefined4 **)(*(int *)(*(int *)(param_4 + -4) + 0x20) + 0xb0);
  iVar2 = FUN_00409a88((int)puVar1,*(int *)(param_4 + -4));
  do {
    do {
      if (iVar2 < 1) {
        return 0;
      }
      iVar2 = iVar2 + -1;
      iVar3 = FUN_00409a40(puVar1,iVar2);
    } while ((*(byte *)(iVar3 + 0x34) & 0x40) == 0);
    FUN_00413118(iVar3,&local_28.left);
    IntersectRect(&local_18,(RECT *)(param_4 + -0x14),&local_28);
    BVar4 = EqualRect(&local_18,(RECT *)(param_4 + -0x14));
  } while (BVar4 == 0);
  return local_5;
}

