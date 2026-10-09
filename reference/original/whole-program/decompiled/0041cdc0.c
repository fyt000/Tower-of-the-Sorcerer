/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041cdc0.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0041cdc0(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 extraout_var;
  int local_64 [10];
  int local_3c;
  
  iVar1 = FUN_0040af1c(param_2);
  iVar2 = FUN_0040af00(param_2);
  if (0x58 < iVar1 - iVar2) {
    (**(code **)*param_2)(param_2,local_64,0x58);
    uVar3 = (**(code **)(*param_2 + 8))(param_2,0xffffffa8,CONCAT22(extraout_var,1));
    if ((local_64[0] == 1) && (local_3c == 0x464d4520)) {
      return CONCAT31((int3)((uint)uVar3 >> 8),1);
    }
  }
  return 0;
}

