/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041667c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0041667c(int *param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
    uVar1 = (uint)*(ushort *)(param_2 + 4);
    if (uVar1 < 0x1c) {
      if ((((uVar1 != 0x1b) && (uVar1 != 3)) && (uVar1 != 9)) && (uVar1 != 0xd)) {
        return;
      }
    }
    else if ((3 < uVar1 - 0x25) && (uVar1 - 0x25 != 6)) {
      return;
    }
    uVar2 = FUN_00413cb8(param_1,0xb01e,(uint)*(ushort *)(param_2 + 4),0);
    *(undefined4 *)(param_2 + 0xc) = uVar2;
  }
  return;
}

