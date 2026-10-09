/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fc48.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040fc48(undefined *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char local_1a;
  byte local_19;
  int local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  byte local_5;
  
  local_14 = 0;
  local_18 = 0;
  iVar2 = 0;
  iVar3 = 0;
  local_10 = param_3;
  local_c = param_1;
  if (param_2 != 0) {
    iVar2 = FUN_0041040c(param_2);
  }
  if (local_10 != 0) {
    iVar3 = FUN_0041040c(local_10);
  }
  local_1a = '\0';
  while ((local_1a == '\0' && ((local_14 < iVar2 || (local_18 < iVar3))))) {
    local_5 = 0xff;
    local_19 = 0xff;
    if (local_14 < iVar2) {
      iVar1 = FUN_0041041c(param_2,local_14);
      local_5 = *(byte *)(iVar1 + 0x2d);
    }
    if (local_18 < iVar3) {
      iVar1 = FUN_0041041c(local_10,local_18);
      local_19 = *(byte *)(iVar1 + 0x2d);
    }
    if (local_19 < local_5) {
      local_5 = local_19;
      local_1a = FUN_0040fbe8(&local_18,local_10,local_c,(int)&stack0xfffffffc);
    }
    else {
      local_1a = FUN_0040fbe8(&local_14,param_2,local_c,(int)&stack0xfffffffc);
    }
    while ((local_14 < iVar2 &&
           (iVar1 = FUN_0041041c(param_2,local_14), *(byte *)(iVar1 + 0x2d) <= local_5))) {
      local_14 = local_14 + 1;
    }
    while ((local_18 < iVar3 &&
           (iVar1 = FUN_0041041c(local_10,local_18), *(byte *)(iVar1 + 0x2d) <= local_5))) {
      local_18 = local_18 + 1;
    }
  }
  return;
}

