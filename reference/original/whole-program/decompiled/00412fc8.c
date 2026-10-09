/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00412fc8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00412fc8(int *param_1,char param_2)

{
  char cVar1;
  
  cVar1 = *(char *)((int)param_1 + 0x3b);
  if (param_2 != cVar1) {
    *(char *)((int)param_1 + 0x3b) = param_2;
    if (((((*(byte *)(param_1 + 7) & 1) == 0) &&
         ((byte)(cVar1 - 1U) < 2 == (byte)(param_2 - 3U) < 2)) && (cVar1 != '\0')) &&
       (((cVar1 != '\x05' && (param_2 != '\0')) && (param_2 != '\x05')))) {
      (**(code **)(*param_1 + 0x4c))(param_1,param_1[9],param_1[10],param_1[0xb],param_1[0xc]);
    }
  }
  FUN_00412f1c((int)param_1);
  return;
}

