/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004328cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004328cc(int *param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  uint *in_FS_OFFSET;
  uint uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  
  puStack_1c = (undefined *)0x4328e3;
  uVar1 = FUN_00432860(param_1);
  puStack_1c = (undefined *)0x4328f2;
  piVar2 = (int *)FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  puStack_20 = &LAB_00432932;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = (uint)&uStack_24;
  puStack_1c = &stack0xfffffffc;
  (**(code **)(*piVar2 + 8))(piVar2,param_2);
  FUN_00417bc8(param_1,uVar1,piVar2,param_3);
  *in_FS_OFFSET = param_3;
  puStack_20 = &LAB_00432939;
  uStack_24 = 0x432931;
  FUN_00402c34(piVar2);
  return;
}

