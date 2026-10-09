/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00409cbc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00409cbc(int param_1,uint param_2,char param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  
  if (*(uint *)(param_1 + 4) <= param_2) {
    if ((int)param_2 < 0) {
      uVar2 = FUN_004074cc(0x4089fc,CONCAT31((int3)(param_2 >> 8),1),0xf0b8);
      FUN_004031f8(uVar2);
      return;
    }
    FUN_00409c18(param_1,param_2 + 1);
  }
  if (param_3 != '\0') {
    pbVar1 = (byte *)(*(int *)(param_1 + 8) + ((int)param_2 >> 3));
    *pbVar1 = *pbVar1 | '\x01' << (param_2 & 7);
    return;
  }
  pbVar1 = (byte *)(*(int *)(param_1 + 8) + ((int)param_2 >> 3));
  *pbVar1 = *pbVar1 & ~('\x01' << (param_2 & 7));
  return;
}

