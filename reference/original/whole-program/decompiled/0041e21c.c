/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e21c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041e21c(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (param_2 != *(int *)(iVar1 + 0x14)) {
    FUN_0041d7fc(param_1,*(HGDIOBJ *)(iVar1 + 0xc),*(HPALETTE *)(iVar1 + 0x10),
                 *(char *)(iVar1 + 0x24),*(int *)(iVar1 + 0x18),param_2);
    FUN_0041bd8c(param_1);
  }
  return;
}

