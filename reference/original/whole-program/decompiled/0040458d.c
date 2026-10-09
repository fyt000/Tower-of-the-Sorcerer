/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040458d.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040458d(HANDLE *param_1,HANDLE param_2)

{
  uint uVar1;
  
  uVar1 = DAT_0048a037 & 0xffffff03;
  if (2 < (byte)uVar1) {
    uVar1 = 2;
  }
  FUN_0040448c(param_1,param_2,uVar1);
  return;
}

