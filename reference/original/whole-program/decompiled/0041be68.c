/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041be68.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041be68(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_0040af1c(param_1);
  iVar2 = FUN_0040af1c(param_2);
  if (iVar1 == iVar2) {
    uVar3 = FUN_0040af1c(param_1);
    uVar4 = FUN_0041be48((int *)param_1[1],(int *)param_2[1],uVar3);
    if ((char)uVar4 != '\0') {
      return CONCAT31((int3)((uint)uVar4 >> 8),1);
    }
  }
  return 0;
}

