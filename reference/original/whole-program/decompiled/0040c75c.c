/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c75c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c75c(undefined4 param_1,undefined4 param_2,char *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 *local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_c = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  puStack_24 = &LAB_0040c82c;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  local_8 = param_2;
  FUN_004034dc((int *)&local_c);
  FUN_00403570((int *)&local_10,(int)param_3);
  pcVar1 = FUN_004038dc(".",param_3);
  uVar3 = extraout_EDX;
  if (pcVar1 != (char *)0x0) {
    FUN_00403854((int)param_3,1,(uint)(pcVar1 + -1),(int *)&local_c);
    FUN_00403854((int)param_3,(int)(pcVar1 + 1),0x7fffffff,(int *)&local_10);
    uVar3 = extraout_EDX_00;
  }
  iVar2 = FUN_0040b644(0x40b5e8,CONCAT31((int3)((uint)uVar3 >> 8),1),param_1,local_10,local_c,
                       local_8,*(undefined4 *)(*(int *)(param_4 + -4) + 0x18));
  if (local_c == (undefined4 *)0x0) {
    FUN_004099a4(*(int **)(*(int *)(param_4 + -4) + 0x2c),iVar2);
  }
  else {
    FUN_004099a4(DAT_0048a61c,iVar2);
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_0040c833;
  puStack_24 = (undefined *)0x40c82b;
  FUN_004034fc((int *)&local_10,2);
  return;
}

