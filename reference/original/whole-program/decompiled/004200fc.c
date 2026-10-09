/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004200fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004200fc(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x37) != '\0') {
    if (*(char *)(param_1 + 0x3b) == '\0') {
      iVar1 = FUN_0041f7d8(*(int *)(param_4 + -4),
                           *(int *)(*(int *)(param_4 + -8) + 0xc) + *(int *)(param_1 + 0x24) +
                           *(int *)(param_1 + 0x2c));
      *(int *)(param_4 + -4) = iVar1;
    }
    else if (*(char *)(param_1 + 0x3b) == '\x04') {
      *(int *)(param_4 + -0xc) = *(int *)(param_4 + -0xc) + *(int *)(param_1 + 0x2c);
    }
  }
  return;
}

