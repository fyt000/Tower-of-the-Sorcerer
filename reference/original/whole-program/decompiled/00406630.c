/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406630.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406630(int *param_1,byte *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_EDX;
  undefined local_1006 [4098];
  
  local_1006._2_4_ = param_1;
  iVar1 = FUN_00403650((int)param_2);
  uVar2 = FUN_004062e0(local_1006,(byte *)0x1001,param_2,param_4,param_3,iVar1);
  if (uVar2 == 0x1001) {
    FUN_00405914(0xffa7,extraout_EDX);
  }
  FUN_004035bc(param_1,(undefined4 *)local_1006,uVar2);
  return;
}

