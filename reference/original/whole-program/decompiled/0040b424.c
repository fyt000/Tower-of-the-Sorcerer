/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b424.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040b424(undefined param_1,undefined param_2,undefined param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EDX;
  int **in_FS_OFFSET;
  undefined4 **ppuVar2;
  int *piStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined4 local_10;
  undefined local_c;
  undefined4 *local_8;
  
  puStack_20 = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  puStack_24 = &LAB_0040b48a;
  piStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int *)&piStack_28;
  ppuVar2 = &local_8;
  local_10 = *(undefined4 *)(param_4 + -4);
  local_c = 6;
  FUN_00405c28(0xf00a,&local_10,0,(int *)ppuVar2);
  iVar1 = FUN_00407498(0x408978,CONCAT31((int3)((uint)extraout_EDX >> 8),1),local_8);
  FUN_004031f8(iVar1);
  *in_FS_OFFSET = (int *)ppuVar2;
  puStack_24 = &LAB_0040b491;
  piStack_28 = (int *)0x40b489;
  FUN_004034dc((int *)&local_8);
  return;
}

