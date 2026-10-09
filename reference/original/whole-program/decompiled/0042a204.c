/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042a204.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042a204(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 8);
  *(int *)(iVar1 + 0x10) = param_1[0x43];
  if (*(char *)((int)param_1 + 0x109) == '\x04') {
    (**(code **)(*param_1 + 0x8c))(param_1,*(undefined4 *)(iVar1 + 8),iVar1 + 0x10);
  }
  return;
}

