/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0047ed97.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4
thunk_FUN_00403140(undefined param_1,undefined param_2,undefined param_3,int param_4,int param_5)

{
  int iVar1;
  code *extraout_ECX;
  
  if ((*(uint *)(param_4 + 4) & 6) != 0) {
    iVar1 = *(int *)(param_5 + 4);
    *(undefined4 *)(param_5 + 4) = 0x403170;
    FUN_00402ee8(param_4,param_5,(char *)(iVar1 + 5));
    (*extraout_ECX)();
  }
  return 1;
}

