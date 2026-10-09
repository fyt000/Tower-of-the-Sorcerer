/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00433784.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00433784(int *param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0xe);
  FUN_004150c4(param_1);
  FUN_00432c54(param_1[0x44],cVar1 == '\0');
  return;
}

