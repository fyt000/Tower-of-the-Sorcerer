/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043d5cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0043d5cc(undefined *param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  undefined *local_24;
  undefined local_20;
  undefined *local_1c;
  undefined local_18;
  undefined4 local_14;
  undefined local_10;
  
  local_20 = 0xb;
  local_24 = param_1;
  cVar1 = FUN_0040ed64(param_1);
  local_1c = (&PTR_DAT_004898f0)[cVar1 != '\\'];
  local_18 = 6;
  local_10 = 0xb;
  local_14 = param_2;
  FUN_0040661c((byte *)"%s%s%s",&local_24,2,param_3);
  return;
}

