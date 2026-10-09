/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00414628.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_00414628(int param_1,int param_2,char param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (param_3 == '\x01') {
    uVar1 = (uint)(*(int *)(param_1 + 0x28) < *(int *)(param_2 + 0x28));
  }
  else if (param_3 == '\x02') {
    iVar2 = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x30);
    uVar1 = CONCAT31((int3)((uint)iVar2 >> 8),
                     *(int *)(param_2 + 0x28) + *(int *)(param_2 + 0x30) < iVar2);
  }
  else if (param_3 == '\x03') {
    uVar1 = (uint)(*(int *)(param_1 + 0x24) < *(int *)(param_2 + 0x24));
  }
  else if (param_3 == '\x04') {
    iVar2 = *(int *)(param_1 + 0x24) + *(int *)(param_1 + 0x2c);
    uVar1 = CONCAT31((int3)((uint)iVar2 >> 8),
                     *(int *)(param_2 + 0x24) + *(int *)(param_2 + 0x2c) < iVar2);
  }
  return uVar1;
}

