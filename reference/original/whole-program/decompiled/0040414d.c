/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040414d.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040414d(undefined4 *param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  char cVar4;
  
  param_1[5] = param_1 + 0x53;
  *param_1 = 0;
  param_1[1] = 0xd7b0;
  param_1[2] = 0x80;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[6] = &LAB_00403fbf;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  puVar3 = param_1 + 0x12;
  if (param_2 != (char *)0x0) {
    cVar4 = -0x7e;
    do {
      puVar2 = puVar3;
      cVar1 = *param_2;
      *(char *)puVar2 = cVar1;
      if (cVar1 == '\0') {
        return;
      }
      cVar1 = param_2[1];
      param_2 = param_2 + 2;
      *(char *)((int)puVar2 + 1) = cVar1;
      if (cVar1 == '\0') {
        return;
      }
      cVar4 = cVar4 + -1;
      puVar3 = (undefined4 *)((int)puVar2 + 2);
    } while (cVar4 != '\0');
    puVar3 = (undefined4 *)((int)puVar2 + 1);
  }
  *(char *)puVar3 = '\0';
  return;
}

