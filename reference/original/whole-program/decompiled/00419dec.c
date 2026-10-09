/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419dec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00419dec(int *param_1,undefined4 *param_2)

{
  undefined4 auStack_34 [2];
  undefined4 local_2a [8];
  
  if (*(char *)param_2 != '\0') {
    FUN_00419c54((int)param_1,auStack_34);
    FUN_004029b8(local_2a,0x20,0);
    FUN_00402918(local_2a,param_2,0x1f);
    FUN_00419c6c(param_1,auStack_34);
  }
  return;
}

