/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406240.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00406240(undefined4 *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0;
  }
  iVar1 = FUN_004060ac((char *)param_1);
  piVar2 = FUN_00406220(iVar1 + 1U);
  uVar3 = FUN_004060d8(piVar2,param_1,iVar1 + 1U);
  return uVar3;
}

