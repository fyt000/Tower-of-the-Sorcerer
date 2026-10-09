/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c908.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041c908(int param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  FUN_0041c954(param_1);
  uVar1 = FUN_0041cdc0(param_1,param_2);
  if ((char)uVar1 == '\0') {
    iVar2 = FUN_0040af1c(param_2);
    iVar3 = FUN_0040af00(param_2);
    FUN_0041ca94(param_1,param_2,iVar2 - iVar3);
  }
  else {
    FUN_0041c9c4(param_1,param_2);
  }
  FUN_0041bd8c(param_1);
  return;
}

