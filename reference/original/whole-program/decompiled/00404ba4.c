/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00404ba4.
 * Inferred types, shared tails and runtime effects require assembly review. */

BOOL __stdcall
GetVolumeInformationA
          (LPCSTR lpRootPathName,LPSTR lpVolumeNameBuffer,DWORD nVolumeNameSize,
          LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,LPDWORD lpFileSystemFlags,
          LPSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x00404ba4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetVolumeInformationA
                    (lpRootPathName,lpVolumeNameBuffer,nVolumeNameSize,lpVolumeSerialNumber,
                     lpMaximumComponentLength,lpFileSystemFlags,lpFileSystemNameBuffer,
                     nFileSystemNameSize);
  return BVar1;
}

