/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00405dbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_00405dbc(undefined *param_1)

{
  int iVar1;
  
  iVar1 = FUN_00405d54(param_1);
  return CONCAT31((int3)((uint)(iVar1 + 1) >> 8),iVar1 + 1 != 0);
}

