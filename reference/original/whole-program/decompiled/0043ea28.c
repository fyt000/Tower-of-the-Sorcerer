/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043ea28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0043ea28(int param_1)

{
  char cVar1;
  LPCSTR lpRootPathName;
  int iVar2;
  uint uVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int iVar4;
  undefined4 *in_FS_OFFSET;
  LPSTR lpVolumeNameBuffer;
  DWORD nVolumeNameSize;
  LPDWORD lpVolumeSerialNumber;
  DWORD *lpMaximumComponentLength;
  LPDWORD lpFileSystemFlags;
  undefined4 uVar5;
  LPSTR lpFileSystemNameBuffer;
  DWORD nFileSystemNameSize;
  undefined **ppuVar6;
  undefined4 uStack_4c;
  undefined *puStack_48;
  undefined *puStack_44;
  undefined4 uStack_40;
  undefined *puStack_3c;
  undefined *puStack_38;
  undefined4 *puStack_28;
  undefined *puStack_24;
  int iStack_20;
  int *piStack_1c;
  byte bStack_18;
  DWORD DStack_14;
  int iStack_10;
  undefined *puStack_c;
  int iStack_8;
  
  puStack_38 = &stack0xfffffffc;
  puStack_44 = &stack0xfffffffc;
  puStack_28 = (undefined4 *)0x0;
  puStack_c = (undefined *)0x0;
  iStack_10 = 0;
  puStack_24 = (undefined *)0x0;
  puStack_3c = &LAB_0043ed0a;
  uStack_40 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_40;
  puStack_48 = &LAB_0043ecc4;
  uStack_4c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_4c;
  iStack_8 = param_1;
  FUN_0040a14c(*(int **)(param_1 + 0x100));
  (**(code **)(**(int **)(iStack_8 + 0x100) + 0x38))();
  iVar4 = 0;
  FUN_00405f04(*(char **)(iStack_8 + 0x158),(int *)&puStack_28);
  FUN_0040369c((int *)&puStack_24,puStack_28,(undefined4 *)&DAT_0043ed20);
  nFileSystemNameSize = 0;
  lpFileSystemNameBuffer = (LPSTR)0x0;
  lpFileSystemFlags = (LPDWORD)&bStack_18;
  lpMaximumComponentLength = &DStack_14;
  lpVolumeSerialNumber = (LPDWORD)0x0;
  nVolumeNameSize = 0;
  lpVolumeNameBuffer = (LPSTR)0x0;
  lpRootPathName = FUN_00403814(puStack_24);
  GetVolumeInformationA
            (lpRootPathName,lpVolumeNameBuffer,nVolumeNameSize,lpVolumeSerialNumber,
             lpMaximumComponentLength,lpFileSystemFlags,lpFileSystemNameBuffer,nFileSystemNameSize);
  *(bool *)(iStack_8 + 0x149) = (bStack_18 & 3) != 0;
  *(bool *)(iStack_8 + 0x14a) = (bStack_18 & 1) != 0;
  iVar2 = FUN_00403650((int)puStack_24);
  if ((iVar2 < 2) || (puStack_24[1] != '\\')) {
    FUN_00403570((int *)&puStack_c,*(int *)(iStack_8 + 0x158));
  }
  else {
    (**(code **)(**(int **)(iStack_8 + 0x100) + 0x30))
              (*(int **)(iStack_8 + 0x100),puStack_24,*(undefined4 *)(iStack_8 + 0x150));
    iVar4 = 1;
    ppuVar6 = &puStack_c;
    uVar3 = FUN_00403650(*(int *)(iStack_8 + 0x158));
    iVar2 = FUN_00403650((int)puStack_24);
    FUN_00403854(*(int *)(iStack_8 + 0x158),iVar2 + 1,uVar3,(int *)ppuVar6);
  }
  iVar2 = FUN_00403650((int)puStack_c);
  if (0 < iVar2) {
    cVar1 = FUN_0040ed64(puStack_c);
    if (cVar1 != '\\') {
      iVar2 = FUN_0040edcc((uint *)&DAT_0043ed20,(int)puStack_c);
      while (iVar2 != 0) {
        FUN_00403854((int)puStack_c,1,iVar2 - 1,&iStack_10);
        if (iVar4 == 0) {
          FUN_00403658(&iStack_10,(undefined4 *)&DAT_0043ed20);
        }
        FUN_00403894((int *)&puStack_c,1,iVar2);
        (**(code **)(**(int **)(iStack_8 + 0x100) + 0x30))
                  (*(int **)(iStack_8 + 0x100),iStack_10,*(undefined4 *)(iStack_8 + 0x150));
        iVar4 = iVar4 + 1;
        iVar2 = FUN_0040edcc((uint *)&DAT_0043ed20,(int)puStack_c);
      }
    }
    (**(code **)(**(int **)(iStack_8 + 0x100) + 0x30))
              (*(int **)(iStack_8 + 0x100),puStack_c,*(undefined4 *)(iStack_8 + 0x154));
  }
  iStack_20 = (**(code **)(**(int **)(iStack_8 + 0x100) + 0x10))();
  iStack_20 = iStack_20 + -1;
  piStack_1c = (int *)FUN_00402c0c(0x408d3c,CONCAT31((int3)((uint)extraout_EDX >> 8),1),extraout_ECX
                                  );
  uVar5 = *in_FS_OFFSET;
  *in_FS_OFFSET = &stack0xffffffa8;
  FUN_0040aea8(piStack_1c,'\x01');
  FUN_0043e8e4(iStack_8,*(undefined **)(iStack_8 + 0x158),piStack_1c);
  iVar4 = (**(code **)(*piStack_1c + 0x10))();
  if (-1 < iVar4 + -1) {
    DStack_14 = 0;
    do {
      (**(code **)(*piStack_1c + 0xc))(piStack_1c,DStack_14,&puStack_28);
      (**(code **)(**(int **)(iStack_8 + 0x100) + 0x30))
                (*(int **)(iStack_8 + 0x100),puStack_28,*(undefined4 *)(iStack_8 + 0x14c));
      DStack_14 = DStack_14 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  *in_FS_OFFSET = uVar5;
  FUN_00402c34(piStack_1c);
  return;
}

