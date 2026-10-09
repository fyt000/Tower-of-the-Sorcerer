/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042df04.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0042df04(int param_1)

{
  undefined4 auStack_3c [2];
  byte local_31;
  undefined4 local_28;
  
  FUN_0042de88(param_1,auStack_3c);
  if ((local_31 & 0x40) != 0) {
    local_28 = 0x80000008;
  }
  return local_28;
}

