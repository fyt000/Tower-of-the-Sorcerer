/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042314c.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042314c(int param_1,int param_2)

{
  int iVar1;
  SHORT SVar2;
  undefined4 uVar3;
  
  SVar2 = GetKeyState(0x12);
  if (-1 < SVar2) {
    if (*(short *)(param_2 + 4) == 9) {
      SVar2 = GetKeyState(0x11);
      if (-1 < SVar2) {
        uVar3 = 1;
        SVar2 = GetKeyState(0x10);
        root_0041706c(param_1,*(undefined4 *)(param_1 + 0x10c),-1 < SVar2,uVar3);
        *(undefined4 *)(param_2 + 0xc) = 1;
        return;
      }
    }
    else if ((ushort)(*(short *)(param_2 + 4) - 0x25U) < 4) {
      iVar1 = *(int *)(param_1 + 0x10c);
      if (iVar1 == 0) {
        return;
      }
      if ((*(short *)(param_2 + 4) == 0x27) || (*(short *)(param_2 + 4) == 0x28)) {
        uVar3 = 1;
      }
      else {
        uVar3 = 0;
      }
      root_0041706c(*(undefined4 *)(iVar1 + 0x20),iVar1,uVar3,0);
      *(undefined4 *)(param_2 + 0xc) = 1;
      return;
    }
  }
  FUN_004162d4(param_1,param_2);
  return;
}

