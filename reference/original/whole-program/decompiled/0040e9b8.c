/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e9b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e9b8(int *param_1,uint *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  bool bVar3;
  uint *local_14;
  undefined local_10;
  
  bVar3 = &stack0x00000000 == (undefined *)0x14;
  FUN_00403760((uint *)param_1[2],param_2);
  if (!bVar3) {
    if (param_2 != (uint *)0x0) {
      uVar2 = FUN_00405b08((char *)param_2);
      if ((char)uVar2 == '\0') {
        local_10 = 0xb;
        local_14 = param_2;
        uVar2 = FUN_0040753c(0x408a84,CONCAT31((int3)((uint)extraout_EDX >> 8),1),0xf011,0,&local_14
                            );
        FUN_004031f8(uVar2);
      }
    }
    piVar1 = (int *)param_1[1];
    if (piVar1 == (int *)0x0) {
      (**(code **)(*param_1 + 0x1c))(param_1,0,param_1[2],param_2);
    }
    else {
      (**(code **)(*piVar1 + 0x1c))(piVar1,param_1,param_1[2],param_2);
    }
    FUN_0040eb1c((int)param_1,'\0');
    FUN_0040ea40((int)param_1,param_2);
    FUN_0040eb1c((int)param_1,'\x01');
  }
  return;
}

