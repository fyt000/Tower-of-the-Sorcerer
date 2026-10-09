/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406054.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00406054(BYTE param_1)

{
  BOOL BVar1;
  
  BVar1 = IsDBCSLeadByte(param_1);
  return BVar1 != 0;
}

