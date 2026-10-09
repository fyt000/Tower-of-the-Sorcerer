/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e0ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e0ec(int param_1,HANDLE param_2)

{
  int iVar1;
  undefined uVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  short local_10;
  short local_e;
  undefined4 local_8;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (param_2 != *(HANDLE *)(iVar1 + 0xc)) {
    FUN_0041db9c(param_1);
    if (param_2 == (HANDLE)0x0) {
      FUN_004029b8(&local_20,0x18,0);
    }
    else {
      GetObjectA(param_2,0x18,&local_20);
    }
    if (*(int *)(iVar1 + 4) == 1) {
      local_8 = *(undefined4 *)(iVar1 + 0x10);
      *(undefined4 *)(iVar1 + 0x10) = 0;
    }
    else {
      local_8 = FUN_0041d66c(*(HPALETTE *)(iVar1 + 0x10));
    }
    uVar3 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffc8;
    if ((local_10 == 1) && (local_e == 1)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
    FUN_0041de0c(param_1,param_2,local_8,0,0,0,0,uVar2,local_18,local_1c);
    *in_FS_OFFSET = uVar3;
    FUN_0041bd8c(param_1);
  }
  return;
}

