/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421a68.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 root_00421a68(int param_1)

{
  if (((*(char *)(param_1 + 0xc5) == '\0') || (*(int *)(param_1 + 0x48) == -0x7ffffff1)) &&
     ((*(char *)(param_1 + 0xc5) != '\0' || (*(int *)(param_1 + 0x48) == -0x7ffffffb)))) {
    return 0;
  }
  return 1;
}

