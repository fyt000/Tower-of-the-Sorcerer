/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418884.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00418884(void)

{
  byte *pbVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar2;
  byte local_38 [32];
  DWORD local_18;
  undefined local_14;
  undefined4 local_10;
  undefined local_c;
  DWORD local_8;
  undefined local_4;
  
  uVar2 = 0;
  local_18 = GetCurrentProcessId();
  local_14 = 0;
  pbVar1 = FUN_004065e8(local_38,(byte *)"Delphi%.8X",&local_18,uVar2);
  DAT_0048a696 = GlobalAddAtomA((LPCSTR)pbVar1);
  uVar2 = 1;
  local_10 = DAT_0048a014;
  local_c = 0;
  local_8 = GetCurrentThreadId();
  local_4 = 0;
  pbVar1 = FUN_004065e8(local_38,(byte *)"ControlOfs%.8X%.8X",&local_10,uVar2);
  DAT_0048a698 = GlobalAddAtomA((LPCSTR)pbVar1);
  DAT_0048a6d0 = (undefined4 *)
                 FUN_00402c0c(0x408ac8,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX);
  FUN_00409b4c(DAT_0048a6d0,4);
  DAT_0048a6fc = FUN_00423a54(0x41f6e0,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),(int *)0x0);
  DAT_0048a6f8 = FUN_00423ffc(0x41f760,CONCAT31((int3)((uint)extraout_EDX_01 >> 8),1),(int *)0x0);
  FUN_0041fad4();
  FUN_00425260(DAT_0048a6f8,'\x01');
  FUN_00405998(&LAB_00418854);
  FUN_004095a0(&DAT_00411190,root_004123c8,&LAB_00412394);
  return;
}

