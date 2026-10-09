/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00429210.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00429210(int *param_1,int param_2)

{
  (**(code **)(*param_1 + -0x10))(param_1,param_2);
  if (*(char *)(param_1 + 0x48) == '\0') {
    *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) & 0xfffffffd;
  }
  else {
    *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) | 2;
  }
  if (*(char *)((int)param_1 + 0x11f) == '\0') {
    *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) & 0xfffffffb;
  }
  return;
}

