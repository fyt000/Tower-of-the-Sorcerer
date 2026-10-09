/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040b504.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_0040b504(int *param_1,char param_2)

{
  FUN_0040529c();
  FreeResource((HGLOBAL)param_1[4]);
  FUN_00402c28(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

