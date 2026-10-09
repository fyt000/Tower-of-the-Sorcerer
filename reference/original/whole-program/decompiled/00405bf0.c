/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405bf0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00405bf0(UINT param_1,int *param_2)

{
  uint uVar1;
  undefined4 local_408 [256];
  
  uVar1 = LoadStringA(DAT_0048a014,param_1,(LPSTR)local_408,0x400);
  FUN_004035bc(param_2,local_408,uVar1);
  return;
}

