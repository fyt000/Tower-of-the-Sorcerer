/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413f14.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413f14(int *param_1,int param_2,undefined param_3,byte param_4)

{
  byte bVar1;
  undefined3 extraout_var;
  undefined4 extraout_EDX;
  
  if ((*(byte *)((int)param_1 + 0x35) & 0x10) == 0) {
    bVar1 = FUN_0041fecc(CONCAT22(*(short *)(param_2 + 10) >> 0xf,*(undefined2 *)(param_2 + 4)));
    FUN_00402cdc(param_1,CONCAT31((int3)((uint)extraout_EDX >> 8),param_3),
                 CONCAT31(extraout_var,bVar1 | param_4));
  }
  return;
}

