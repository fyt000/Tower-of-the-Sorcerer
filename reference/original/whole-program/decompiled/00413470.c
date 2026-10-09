/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413470.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413470(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined local_1c [8];
  int iStack_14;
  int iStack_10;
  
  iVar1 = *param_2;
  iVar2 = param_2[1];
  (**(code **)(*param_1 + 0x2c))(param_1,local_1c,*param_1,iVar1,iVar2);
  (**(code **)(*param_1 + 0x4c))
            (param_1,param_1[9],param_1[10],(param_1[0xc] - iStack_10) + iVar2,
             (param_1[0xb] - iStack_14) + iVar1);
  return;
}

