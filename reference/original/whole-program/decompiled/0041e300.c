/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041e300.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041e300(int param_1,undefined2 *param_2,BOOL *param_3,undefined4 *param_4)

{
  int iVar1;
  BOOL BVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStackY_2c;
  code *pcStackY_28;
  undefined *puStackY_24;
  
  *param_2 = 2;
  FUN_0041dbac(param_1);
  iVar1 = *(int *)(param_1 + 0x10);
  puStackY_24 = (undefined *)0x41e335;
  BVar2 = FUN_0041d400(*(HGDIOBJ *)(iVar1 + 0xc),*(HPALETTE *)(iVar1 + 0x10),*(int *)(iVar1 + 0x14),
                       *(char *)(iVar1 + 0x24),*(int *)(param_1 + 0x14),*(int *)(iVar1 + 0x18));
  *param_3 = BVar2;
  pcStackY_28 = thunk_FUN_00402f4c;
  uStackY_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_2c;
  puStackY_24 = &stack0xfffffffc;
  uVar3 = FUN_0041d66c(*(HPALETTE *)(*(int *)(param_1 + 0x10) + 0x10));
  *param_4 = uVar3;
  *in_FS_OFFSET = uStackY_2c;
  return;
}

