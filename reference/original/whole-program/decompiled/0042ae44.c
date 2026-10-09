/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ae44.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042ae44(int *param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  undefined2 uVar2;
  
  uVar2 = (undefined2)((uint)param_2 >> 0x10);
  sVar1 = *(short *)(param_2 + 6) + -1;
  if (sVar1 == 0) {
    FUN_00402cdc(param_1,CONCAT22(uVar2,sVar1),param_3);
    return;
  }
  sVar1 = *(short *)(param_2 + 6) + -2;
  if (sVar1 == 0) {
    FUN_00402cdc(param_1,CONCAT22(uVar2,sVar1),param_3);
  }
  return;
}

