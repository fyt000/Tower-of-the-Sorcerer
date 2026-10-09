/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418760.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00418760(int *param_1,int *param_2,undefined4 param_3)

{
  int *piVar1;
  HANDLE pvVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  int iStack_8;
  
  puStack_20 = (undefined *)0x418779;
  piVar1 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  puStack_24 = &LAB_00418845;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_20 = &stack0xfffffffc;
  pvVar2 = (HANDLE)FUN_00417a50(param_1);
  FUN_0041e0ec((int)piVar1,pvVar2);
  iVar3 = FUN_0040af00(param_2);
  iStack_8 = FUN_00417b3c(param_1);
  (**(code **)(*param_2 + 4))(param_2,&iStack_8,4);
  (**(code **)(*param_2 + 4))(param_2,&iStack_8,4);
  (**(code **)(*piVar1 + 0x40))(piVar1,param_2);
  iStack_8 = FUN_0040af00(param_2);
  iStack_8 = iStack_8 - (iVar3 + 8);
  pvVar2 = (HANDLE)FUN_00417a90(param_1);
  FUN_0041e0ec((int)piVar1,pvVar2);
  (**(code **)(*piVar1 + 0x40))(piVar1,param_2);
  uVar4 = FUN_0040af00(param_2);
  FUN_0040af10(param_2,iVar3);
  (**(code **)(*param_2 + 4))(param_2,&iStack_8,4);
  FUN_0040af10(param_2,uVar4);
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0041884c;
  puStack_24 = (undefined *)0x418844;
  FUN_00402c34(piVar1);
  return;
}

