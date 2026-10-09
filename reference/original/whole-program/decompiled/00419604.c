/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00419604.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 * FUN_00419604(int param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = FUN_004195ac((byte *)param_2,(uint)*(ushort *)(param_1 + 8));
  for (puVar3 = *(undefined4 **)(param_1 + 4); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if ((short)uVar2 == *(short *)(puVar3 + 3)) {
      cVar1 = FUN_004195c0((char *)(puVar3 + 4),(char *)param_2,(uint)*(ushort *)(param_1 + 8));
      if (cVar1 != '\0') break;
    }
  }
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)FUN_00402650(*(ushort *)(param_1 + 8) + 0x10);
    *puVar3 = *(undefined4 *)(param_1 + 4);
    puVar3[1] = 0;
    puVar3[2] = *param_2;
    *(short *)(puVar3 + 3) = (short)uVar2;
    FUN_00402870(param_2,puVar3 + 4,(uint)*(ushort *)(param_1 + 8));
    *(undefined4 **)(param_1 + 4) = puVar3;
  }
  puVar3[1] = puVar3[1] + 1;
  return puVar3;
}

