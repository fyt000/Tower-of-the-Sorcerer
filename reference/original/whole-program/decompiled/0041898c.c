/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041898c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041898c(void)

{
  DWORD DVar1;
  
  DVar1 = GetVersion();
  DAT_0048a694 = 3 < ((ushort)DVar1 & 0xff);
  FUN_0041e7ac();
  FUN_00418884();
  return;
}

