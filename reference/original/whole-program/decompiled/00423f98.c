/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423f98.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423f98(uint param_1)

{
  undefined4 local_8;
  uint local_4;
  
  local_8 = 8;
  local_4 = param_1 & 0x7f;
  SystemParametersInfoA(0x49,0,&local_8,0);
  return;
}

