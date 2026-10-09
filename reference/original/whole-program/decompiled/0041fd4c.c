/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041fd4c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined *
FUN_0041fd4c(undefined param_1,undefined param_2,undefined param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  
  puVar1 = DAT_0048a71c;
  if (DAT_0048a720 == (undefined *)0x0) {
    puVar1 = (undefined4 *)VirtualAlloc((LPVOID)0x0,0x1000,0x1000,0x40);
    *puVar1 = DAT_0048a71c;
    FUN_00402870((undefined4 *)&DAT_004895a0,puVar1 + 1,2);
    iVar2 = FUN_0041fd44((int)puVar1 + 5,0x41fd24);
    *(int *)((int)puVar1 + 6) = iVar2;
    puVar3 = (undefined *)((int)puVar1 + 10);
    do {
      puVar4 = puVar3;
      *puVar4 = 0xe8;
      iVar2 = FUN_0041fd44((int)puVar4,(int)(puVar1 + 1));
      *(int *)(puVar4 + 1) = iVar2;
      *(undefined **)(puVar4 + 5) = DAT_0048a720;
      puVar3 = puVar4 + 0xd;
      DAT_0048a720 = puVar4;
    } while ((int)(puVar4 + 0xd) - (int)puVar1 < 0xffc);
  }
  DAT_0048a71c = puVar1;
  puVar3 = DAT_0048a720;
  puVar1 = (undefined4 *)(DAT_0048a720 + 5);
  DAT_0048a720 = (undefined *)*(undefined4 *)(DAT_0048a720 + 5);
  *puVar1 = param_4;
  *(undefined4 *)(puVar3 + 9) = param_5;
  return puVar3;
}

