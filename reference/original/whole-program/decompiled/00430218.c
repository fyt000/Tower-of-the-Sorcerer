/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430218.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430218(int *param_1,undefined2 param_2)

{
  uint uVar1;
  bool bVar2;
  
  *(undefined2 *)((int)param_1 + 0x196) = param_2;
  uVar1 = 0;
  do {
    bVar2 = (byte)uVar1 < 0xf;
    if ((byte)uVar1 < 0x10) {
      bVar2 = (*(byte *)((int)param_1 + ((int)(uVar1 & 0x7f) >> 3) + 0x196) >> (uVar1 & 7) & 1) != 0
      ;
    }
    *(bool *)((int)param_1 + (uVar1 & 0xff) * 0x10 + 0x105) = bVar2;
    uVar1 = uVar1 + 1;
  } while ((char)uVar1 != '\t');
  (**(code **)(*param_1 + 0x44))();
  return;
}

