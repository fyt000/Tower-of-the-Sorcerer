/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433838.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00433838(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 8);
  *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(param_1 + 0x30);
  return;
}

