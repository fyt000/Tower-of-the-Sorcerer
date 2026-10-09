/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431dec.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431dec(int param_1,undefined4 *param_2)

{
  MCIERROR MVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined auStack_20 [4];
  undefined4 local_1c [4];
  
  if ((*(char *)(param_1 + 0x1d5) != '\0') && (*(char *)(param_1 + 0x1db) != '\0')) {
    *(undefined4 *)(param_1 + 0x1dc) = 0x40000;
    MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x843,0x40000,(DWORD_PTR)auStack_20);
    *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
    puVar3 = local_1c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_2 = *puVar3;
      puVar3 = puVar3 + 1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

