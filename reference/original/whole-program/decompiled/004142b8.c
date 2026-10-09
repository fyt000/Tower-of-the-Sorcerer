/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004142b8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004142b8(int **param_1)

{
  bool bVar1;
  
  (*(code *)(*param_1)[-4])();
  bVar1 = FUN_00413748(param_1);
  if (bVar1) {
    FUN_00413758(param_1,'\0');
    if ((*(byte *)((int)param_1 + 0x36) & 1) != 0) {
      FUN_00413cb8((int *)param_1,0x202,0,0xffffffff);
    }
  }
  return;
}

