/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ba9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0040ba9c(int param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar2;
  int local_114;
  char local_110 [4];
  byte local_10c [256];
  
  FUN_00403988(local_10c,param_3,0xff);
  iVar1 = FUN_00402d34(*param_2,local_10c);
  local_110[0] = iVar1 == 0;
  uVar2 = extraout_EDX;
  local_114 = iVar1;
  if (*(short *)(param_1 + 0x36) != 0) {
    iVar1 = (**(code **)(param_1 + 0x34))
                      (*(undefined4 *)(param_1 + 0x38),param_1,param_3,local_110,&local_114);
    uVar2 = extraout_EDX_00;
  }
  if (local_110[0] != '\0') {
    FUN_0040b8e0(iVar1,uVar2);
  }
  return local_114;
}

