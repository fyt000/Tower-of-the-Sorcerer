/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e5fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041e5fc(int param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined2 extraout_var;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  code *pcStack_24;
  undefined *puStack_20;
  undefined auStack_e [2];
  ushort uStack_c;
  int *piStack_8;
  
  puStack_20 = (undefined *)0x41e615;
  piStack_8 = (int *)FUN_00402c0c(0x408f68,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
  pcStack_24 = thunk_FUN_00402f4c;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puStack_20 = &stack0xfffffffc;
  iVar1 = FUN_0040af1c(param_2);
  iVar2 = FUN_0040af00(param_2);
  FUN_0040b2e8(piStack_8,iVar1 - iVar2);
  iVar1 = FUN_0040af1c(piStack_8);
  FUN_0040af50(param_2,piStack_8[1],iVar1);
  FUN_0040af50(piStack_8,auStack_e,6);
  if (1 < uStack_c) {
    FUN_0041ac44(CONCAT22(extraout_var,uStack_c - 2),extraout_EDX);
  }
  FUN_0041e6b4(param_1,0,piStack_8);
  *in_FS_OFFSET = uStack_28;
  puStack_20 = (undefined *)0x41e6ac;
  FUN_0041bd8c(param_1);
  return;
}

