/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403498.
 * Inferred types, shared tails and runtime effects require assembly review. */

LPVOID FUN_00403498(void)

{
  LPVOID pvVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int in_FS_OFFSET;
  
  if (DAT_0048a034 == '\0') {
    return *(LPVOID *)(*(int *)(in_FS_OFFSET + 0x2c) + _tls_index * 4);
  }
  pvVar1 = TlsGetValue(_tls_index);
  if (pvVar1 != (LPVOID)0x0) {
    return pvVar1;
  }
  FUN_00403450(0,extraout_EDX,extraout_ECX);
  pvVar1 = TlsGetValue(_tls_index);
  if (pvVar1 != (LPVOID)0x0) {
    return pvVar1;
  }
  return DAT_0048a490;
}

