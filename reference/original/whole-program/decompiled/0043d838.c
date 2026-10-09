/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043d838.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043d838(undefined4 param_1,byte **param_2)

{
  LPCSTR lpRootPathName;
  uint uVar1;
  undefined4 *in_FS_OFFSET;
  undefined4 *lpVolumeNameBuffer;
  DWORD nVolumeNameSize;
  LPDWORD lpVolumeSerialNumber;
  DWORD *lpMaximumComponentLength;
  DWORD *lpFileSystemFlags;
  LPSTR lpFileSystemNameBuffer;
  DWORD nFileSystemNameSize;
  undefined4 uStack_148;
  undefined4 uStack_13c;
  undefined *puStack_138;
  undefined *puStack_134;
  byte *local_124;
  undefined local_120;
  byte *local_11c;
  undefined4 local_115 [65];
  DWORD local_10;
  DWORD local_c;
  UINT local_8;
  
  puStack_134 = &stack0xfffffffc;
  local_11c = (byte *)0x0;
  puStack_138 = &LAB_0043d97f;
  uStack_13c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_13c;
  local_8 = SetErrorMode(1);
  uStack_148 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_148;
  nFileSystemNameSize = 0;
  lpFileSystemNameBuffer = (LPSTR)0x0;
  lpFileSystemFlags = &local_10;
  lpMaximumComponentLength = &local_c;
  lpVolumeSerialNumber = (LPDWORD)0x0;
  nVolumeNameSize = 0x105;
  lpVolumeNameBuffer = local_115;
  FUN_004035ec((int *)&local_11c,param_1);
  FUN_00403658((int *)&local_11c,(undefined4 *)&DAT_0043d998);
  lpRootPathName = FUN_00403814(local_11c);
  GetVolumeInformationA
            (lpRootPathName,(LPSTR)lpVolumeNameBuffer,nVolumeNameSize,lpVolumeSerialNumber,
             lpMaximumComponentLength,lpFileSystemFlags,lpFileSystemNameBuffer,nFileSystemNameSize);
  uVar1 = FUN_004060ac((char *)local_115);
  FUN_004035bc((int *)param_2,local_115,uVar1);
  if ((byte)param_1 < 0x61) {
    FUN_0043c0c8(*param_2,&local_11c);
    FUN_00403570((int *)param_2,(int)local_11c);
  }
  else {
    FUN_0043c124(*param_2,&local_11c);
    FUN_00403570((int *)param_2,(int)local_11c);
  }
  local_124 = *param_2;
  local_120 = 0xb;
  FUN_0040661c(&LAB_0043d9a4,&local_124,0,(int *)&local_11c);
  FUN_00403570((int *)param_2,(int)local_11c);
  *in_FS_OFFSET = uStack_148;
  uStack_148 = 0x43d95e;
  SetErrorMode(local_8);
  return;
}

