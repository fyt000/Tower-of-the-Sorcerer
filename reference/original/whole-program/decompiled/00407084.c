/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00407084.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00407084(char **param_1,int *param_2)

{
  char *pcVar1;
  
  pcVar1 = FUN_004038dc(",",*param_1);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = (char *)0x100;
  }
  FUN_00403854((int)*param_1,1,(uint)(pcVar1 + -1),param_2);
  if ((int)pcVar1 < 0xff) {
    FUN_00403854((int)*param_1,(int)(pcVar1 + 1),0xff,(int *)param_1);
  }
  else {
    FUN_004034dc((int *)param_1);
  }
  return;
}

