/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00403450.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00403450(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HLOCAL lpTlsValue;
  
  if ((int)_tls_index < 0) {
    FUN_00404431(0xe2);
  }
  lpTlsValue = LocalAlloc(0x40,8);
  if (lpTlsValue == (HLOCAL)0x0) {
    FUN_00404431(0xe2);
  }
  else {
    TlsSetValue(_tls_index,lpTlsValue);
  }
  DAT_0048a490 = lpTlsValue;
  return;
}

