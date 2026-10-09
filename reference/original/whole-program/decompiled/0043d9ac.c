/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043d9ac.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043d9ac(undefined4 param_1,byte **param_2)

{
  DWORD DVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_130;
  undefined *puStack_12c;
  undefined *puStack_128;
  byte *local_118;
  undefined4 local_111 [65];
  uint local_c;
  byte local_8;
  undefined local_7;
  undefined local_6;
  
  puStack_128 = &stack0xfffffffc;
  local_118 = (byte *)0x0;
  puStack_12c = &LAB_0043da72;
  uStack_130 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_130;
  local_c = 0x105;
  local_8 = FUN_004028b0((byte)param_1);
  local_7 = 0x3a;
  local_6 = 0;
  DVar1 = WNetGetConnectionA((LPCSTR)&local_8,(LPSTR)local_111,&local_c);
  if (DVar1 == 0) {
    FUN_004035bc((int *)param_2,local_111,local_c);
    if ((byte)param_1 < 0x61) {
      FUN_0043c0c8(*param_2,&local_118);
      FUN_00403570((int *)param_2,(int)local_118);
    }
    else {
      FUN_0043c124(*param_2,&local_118);
      FUN_00403570((int *)param_2,(int)local_118);
    }
  }
  else {
    FUN_0043d838(param_1,param_2);
  }
  *in_FS_OFFSET = uStack_130;
  puStack_128 = &LAB_0043da79;
  puStack_12c = (undefined *)0x43da71;
  FUN_004034dc((int *)&local_118);
  return;
}

