/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00413f58.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00413f58(int **param_1,int param_2)

{
  FUN_004132a4(param_1,param_1);
  (*(code *)(*param_1)[-4])(param_1,param_2);
  if ((*(byte *)(param_1 + 0xd) & 2) != 0) {
    FUN_00413758(param_1,'\x01');
  }
  if ((*(byte *)(param_1 + 0xd) & 8) != 0) {
    *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) | 2;
  }
  FUN_00413f14((int *)param_1,param_2,0,DAT_00413fa0);
  return;
}

