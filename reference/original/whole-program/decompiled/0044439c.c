/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0044439c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0044439c(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  iVar1 = FUN_0041dad8(DAT_0048c520);
  *(undefined4 *)(iVar1 + 0x20) = 0xee0086;
  piVar4 = &DAT_0048c53c;
  piVar2 = (int *)FUN_0041dad8(DAT_0048c524);
  piVar3 = (int *)FUN_0041dad8(DAT_0048c520);
  FUN_0041a530(piVar3,&DAT_0048c53c,piVar2,piVar4);
  iVar1 = FUN_0041dad8(DAT_0048c524);
  *(undefined4 *)(iVar1 + 0x20) = 0x330008;
  piVar4 = &DAT_0048c53c;
  piVar2 = (int *)FUN_0041dad8(DAT_0048c524);
  piVar3 = (int *)FUN_0041dad8(DAT_0048c524);
  FUN_0041a530(piVar3,&DAT_0048c53c,piVar2,piVar4);
  iVar1 = FUN_0041dad8(DAT_0048c51c);
  *(undefined4 *)(iVar1 + 0x20) = 0xee0086;
  piVar4 = &DAT_0048c53c;
  piVar2 = (int *)FUN_0041dad8(DAT_0048c524);
  piVar3 = (int *)FUN_0041dad8(DAT_0048c51c);
  FUN_0041a530(piVar3,&DAT_0048c52c,piVar2,piVar4);
  iVar1 = FUN_0041dad8(DAT_0048c51c);
  *(undefined4 *)(iVar1 + 0x20) = 0x8800c6;
  piVar4 = &DAT_0048c53c;
  piVar2 = (int *)FUN_0041dad8(DAT_0048c520);
  piVar3 = (int *)FUN_0041dad8(DAT_0048c51c);
  FUN_0041a530(piVar3,&DAT_0048c52c,piVar2,piVar4);
  iVar1 = FUN_0041dad8(DAT_0048c51c);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  iVar1 = FUN_0041dad8(DAT_0048c520);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  iVar1 = FUN_0041dad8(DAT_0048c524);
  *(undefined4 *)(iVar1 + 0x20) = 0xcc0020;
  return;
}

