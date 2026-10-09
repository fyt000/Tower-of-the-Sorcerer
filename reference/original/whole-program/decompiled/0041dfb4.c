/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dfb4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041dfb4(int param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 extraout_var;
  undefined4 extraout_EDX;
  uint uStack_58;
  uint uStack_54;
  undefined uStack_50;
  undefined uStack_4f;
  int iStack_4c;
  int local_48;
  undefined auStack_44 [4];
  ushort uStack_40;
  ushort uStack_3e;
  short sStack_3c;
  short sStack_3a;
  undefined auStack_38 [4];
  uint uStack_34;
  uint uStack_30;
  short sStack_2c;
  short sStack_2a;
  int iStack_18;
  
  iVar1 = param_2[1];
  (**(code **)*param_2)(param_2,&local_48,4);
  uVar2 = (**(code **)(*param_2 + 8))(param_2,0xfffffffc,CONCAT22(extraout_var,1));
  if (local_48 == 0xc) {
    (**(code **)*param_2)(param_2,auStack_44,0xc);
    uStack_54 = (uint)uStack_3e;
    uStack_58 = (uint)uStack_40;
    if ((sStack_3c == 1) && (sStack_3a == 1)) {
      uStack_50 = 1;
    }
    else {
      uStack_50 = 0;
    }
    uStack_4f = 2;
    iVar3 = FUN_0041adb0(sStack_3a);
    iStack_4c = iVar3 * 3 + iVar1 + 0xc;
  }
  else if (local_48 == 0x28) {
    (**(code **)*param_2)(param_2,auStack_38,0x28);
    uStack_54 = uStack_30;
    uStack_58 = uStack_34;
    if ((sStack_2c == 1) && (sStack_2a == 1)) {
      uStack_50 = 1;
    }
    else {
      uStack_50 = 0;
    }
    uStack_4f = 1;
    if (iStack_18 == 0) {
      iStack_18 = FUN_0041adb0(sStack_2a);
    }
    iStack_4c = iVar1 + 0x28 + iStack_18 * 4;
  }
  else {
    FUN_0041ac38(uVar2,extraout_EDX);
  }
  FUN_0040af10(param_2,0);
  FUN_0041de0c(param_1,0,0,iStack_4c,iVar1,uStack_4f,param_2,uStack_50,uStack_54,uStack_58);
  return;
}

