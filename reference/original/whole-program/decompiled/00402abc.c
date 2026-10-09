/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402abc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402abc(void)

{
  LSTATUS LVar1;
  HKEY local_10;
  ushort local_c [2];
  DWORD local_8;
  DWORD local_4;
  
  DAT_00489014 = 0x1332;
  local_8 = 4;
  local_4 = 4;
  LVar1 = RegOpenKeyExA((HKEY)0x80000002,"SOFTWARE\\Borland\\Delphi\\RTL",0,1,&local_10);
  if (LVar1 == 0) {
    LVar1 = RegQueryValueExA(local_10,"FPUMaskValue",(LPDWORD)0x0,&local_4,(LPBYTE)local_c,&local_8)
    ;
    if (LVar1 == 0) {
      RegCloseKey(local_10);
      DAT_00489014 = DAT_00489014 & 0xffc0 | local_c[0] & 0x3f;
    }
  }
  return;
}

