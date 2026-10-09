/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409280.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409280(undefined4 param_1)

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
  puStack_24 = &LAB_004092e2;
  piStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = (int *)&piStack_28;
  ppuVar2 = &local_8;
  local_c = 0xb;
  local_10 = param_1;
  FUN_00405c28(0xf008,&local_10,0,(int *)ppuVar2);
  iVar1 = FUN_00407498(0x408934,CONCAT31((int3)((uint)extraout_EDX >> 8),1),local_8);
  FUN_004031f8(iVar1);
  *in_FS_OFFSET = (int *)ppuVar2;
  puStack_24 = &LAB_004092e9;
  piStack_28 = (int *)0x4092e1;
  FUN_004034dc((int *)&local_8);
  return;
}

