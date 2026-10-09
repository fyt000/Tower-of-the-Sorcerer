/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004083e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004083e8(int *param_1,int param_2,byte *param_3)

{
  code *pcVar1;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = *(byte **)(param_2 + 0x10);
  if (*(byte **)(param_2 + 0x10) == (byte *)0x80000000) {
    pbVar3 = param_3;
  }
  pcVar1 = *(code **)(param_2 + 4);
  if (*(byte *)(param_2 + 7) == 0xff) {
    pbVar3 = (byte *)(((uint)pcVar1 & 0xffffff) + (int)param_1);
    iVar2 = *pbVar3 + 1;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_3 = *pbVar3;
      pbVar3 = pbVar3 + 1;
      param_3 = param_3 + 1;
    }
  }
  else if (*(byte *)(param_2 + 7) < 0xfe) {
    (*pcVar1)(param_1,pbVar3);
  }
  else {
    (**(code **)((int)(short)pcVar1 + *param_1))();
  }
  return;
}

