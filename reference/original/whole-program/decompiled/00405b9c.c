/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405b9c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00405b9c(byte *param_1)

{
  undefined4 uVar1;
  int local_14;
  byte *local_10;
  undefined local_c;
  
  uVar1 = FUN_004029d8(param_1,&local_14);
  if (local_14 != 0) {
    local_c = 0xb;
    local_10 = param_1;
    FUN_0040592c(0xff80,&local_10,0);
  }
  return uVar1;
}

