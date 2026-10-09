/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fad4.
 * Inferred types, shared tails and runtime effects require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041fad4(void)

{
  DWORD DVar1;
  uint uVar2;
  UINT UVar3;
  int iVar4;
  
  if (DAT_0048959c == (HMODULE)0x0) {
    DVar1 = GetVersion();
    if ((byte)DVar1 < 4) {
      uVar2 = FUN_00405294(DVar1);
      if ((byte)uVar2 < 0x59) {
        UVar3 = SetErrorMode(0x8000);
        DAT_0048959c = LoadLibraryA("CTL3D32.DLL");
        SetErrorMode(UVar3 & 0xffff);
      }
    }
    if ((int)DAT_0048959c < 0x20) {
      DAT_0048959c = (HMODULE)0x1;
    }
    if (0x1f < (int)DAT_0048959c) {
      DAT_0048a700 = GetProcAddress(DAT_0048959c,"Ctl3dRegister");
      iVar4 = (*DAT_0048a700)();
      if (iVar4 == 0) {
        FreeLibrary(DAT_0048959c);
        DAT_0048959c = (HMODULE)0x1;
      }
      else {
        DAT_0048a704 = GetProcAddress(DAT_0048959c,"Ctl3dUnregister");
        _DAT_0048a708 = GetProcAddress(DAT_0048959c,"Ctl3dSubclassCtl");
        _DAT_0048a70c = GetProcAddress(DAT_0048959c,"Ctl3dSubclassDlgEx");
        DAT_00489578 = GetProcAddress(DAT_0048959c,"Ctl3dDlgFramePaint");
        _DAT_0048957c = GetProcAddress(DAT_0048959c,"Ctl3dCtlColorEx");
        _DAT_0048a710 = GetProcAddress(DAT_0048959c,"Ctl3dAutoSubclass");
        _DAT_0048a714 = GetProcAddress(DAT_0048959c,"Ctl3dUnAutoSubclass");
        DAT_0048a718 = GetProcAddress(DAT_0048959c,"Ctl3DColorChange");
        _DAT_00489574 = GetProcAddress(DAT_0048959c,"BtnWndProc3d");
      }
    }
  }
  return;
}

