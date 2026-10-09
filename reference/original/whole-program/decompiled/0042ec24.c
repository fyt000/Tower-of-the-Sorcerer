/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042ec24.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_0042ec24(undefined2 *param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  
  puVar3 = param_1;
  do {
    cVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar4 = puVar3;
    do {
      if (cVar2 == '\0') {
        *(undefined *)puVar4 = 0;
        return (int)puVar4 - (int)param_1;
      }
      if (cVar2 == '\n') {
        puVar3 = puVar4 + 1;
        *puVar4 = 0xa0d;
        break;
      }
      *(char *)puVar4 = cVar2;
      puVar3 = (undefined2 *)((int)puVar4 + 1);
      if (cVar2 != '\r') break;
      puVar3 = puVar4 + 1;
      *(undefined *)(undefined2 *)((int)puVar4 + 1) = 10;
      pcVar1 = param_2 + 1;
      cVar2 = *param_2;
      param_2 = pcVar1;
      puVar4 = puVar3;
    } while (cVar2 != '\n');
  } while( true );
}

