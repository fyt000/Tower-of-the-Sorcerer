/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004302d4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004302d4(int *param_1,undefined2 param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  *(undefined2 *)(param_1 + 0x65) = param_2;
  uVar1 = 0;
  do {
    bVar3 = (byte)uVar1 < 0xf;
    if ((byte)uVar1 < 0x10) {
      bVar3 = (*(byte *)((int)param_1 + ((int)(uVar1 & 0x7f) >> 3) + 0x194) >> (uVar1 & 7) & 1) != 0
      ;
    }
    *(bool *)(param_1 + (uVar1 & 0xff) * 4 + 0x41) = bVar3;
    uVar1 = uVar1 + 1;
  } while ((char)uVar1 != '\t');
  if ((*(byte *)(param_1 + 7) & 0x40) != 0) {
    iVar2 = FUN_00430344((int)param_1);
    param_1[0x6c] = (param_1[0xb] + -1) / iVar2 + 1;
    (**(code **)(*param_1 + 0x44))();
    return;
  }
  FUN_0043036c(param_1);
  return;
}

