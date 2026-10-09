/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004042f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_004042f4(UINT param_1)

{
  ulonglong uVar1;
  code *pcVar2;
  UINT UVar3;
  uint uVar4;
  undefined *puVar5;
  char *pcVar6;
  
  DAT_0048a024 = param_1;
  if (DAT_0048a034 != '\0') {
    if (DAT_0048a418 == '\0') goto LAB_004043cf;
    if ((DAT_0048a418 != '\x01') && (param_1 == 0)) goto LAB_004043da;
  }
  while (pcVar2 = DAT_0048a028, DAT_0048a028 != (code *)0x0) {
    DAT_0048a028 = (code *)0x0;
    (*pcVar2)();
  }
  if (DAT_0048a02c != 0) {
    pcVar6 = s_Runtime_error_at_00000000_00489018 + 0x10;
    UVar3 = DAT_0048a024;
    do {
      uVar1 = (ulonglong)UVar3;
      UVar3 = UVar3 / 10;
      *pcVar6 = (char)(uVar1 % 10) + '0';
      pcVar6 = pcVar6 + -1;
    } while (UVar3 != 0);
    pcVar6 = s_Runtime_error_at_00000000_00489018 + 0x1c;
    uVar4 = DAT_0048a02c - 0x401224;
    do {
      *pcVar6 = (&DAT_0040440c)[uVar4 & 0xf];
      pcVar6 = pcVar6 + -1;
      uVar4 = uVar4 >> 4;
    } while (uVar4 != 0);
    if (DAT_0048a035 == '\0') {
      MessageBoxA((HWND)0x0,s_Runtime_error_at_00000000_00489018,s_Error_00489036,0);
    }
    else {
      puVar5 = (undefined *)FUN_0040470c(&DAT_0048a208,s_Runtime_error_at_00000000_00489018);
      FUN_0040468f(puVar5);
    }
  }
  FUN_004042b8(&DAT_0048a03c);
  FUN_004042b8(&DAT_0048a208);
  FUN_00401a98();
  if (DAT_0048a418 != '\0') {
LAB_004043da:
    FUN_004033f8();
    DAT_0048a418 = 0;
    return (bool)('\x01' - (DAT_0048a024 != 0));
  }
  FUN_004033f8();
LAB_004043cf:
                    /* WARNING: Subroutine does not return */
  ExitProcess(DAT_0048a024);
}

