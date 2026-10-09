/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00422ea4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00422ea4(int param_1,int param_2)

{
  int iVar1;
  LRESULT LVar2;
  
  *(undefined4 *)(param_2 + 0xc) = 0;
  if (((((*(byte *)(param_1 + 0x1c) & 0x10) != 0) || (*(char *)(param_1 + 0x11a) == '\x01')) ||
      (*(int *)(param_1 + 0x128) == 0)) || (*(char *)(*(int *)(param_1 + 0x128) + 0x34) != '\0')) {
    iVar1 = *(int *)(param_2 + 8);
    FUN_00422768(param_1,0);
    LVar2 = FUN_00412200(0xb017,*(WPARAM *)(iVar1 + 4),(uint)*(ushort *)(iVar1 + 8));
    if (LVar2 != 0) {
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
  }
  return;
}

