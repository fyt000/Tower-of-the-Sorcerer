/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00431e44.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00431e44(int param_1)

{
  MCIERROR MVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined auStack_3c [4];
  int local_38;
  undefined4 local_34;
  undefined local_30 [4];
  int local_2c [4];
  int local_1c [4];
  
  *(undefined4 *)(param_1 + 0x1dc) = 0x102;
  local_34 = 8;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80b,0x102,(DWORD_PTR)auStack_3c);
  *(char *)(param_1 + 0x1d7) = (char)local_38;
  if ((char)local_38 != '\0') {
    *(byte *)(param_1 + 0x1d6) = *(byte *)(param_1 + 0x1d6) | 4;
  }
  local_34 = 1;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80b,*(DWORD_PTR *)(param_1 + 0x1dc),
                  (DWORD_PTR)auStack_3c);
  *(char *)(param_1 + 0x1da) = (char)local_38;
  if ((char)local_38 != '\0') {
    *(byte *)(param_1 + 0x1d6) = *(byte *)(param_1 + 0x1d6) | 8;
  }
  local_34 = 7;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80b,*(DWORD_PTR *)(param_1 + 0x1dc),
                  (DWORD_PTR)auStack_3c);
  *(char *)(param_1 + 0x1d9) = (char)local_38;
  if ((char)local_38 != '\0') {
    *(byte *)(param_1 + 0x1d6) = *(byte *)(param_1 + 0x1d6) | 2;
  }
  local_34 = 3;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80b,*(DWORD_PTR *)(param_1 + 0x1dc),
                  (DWORD_PTR)auStack_3c);
  *(char *)(param_1 + 0x1db) = (char)local_38;
  if ((char)local_38 != '\0') {
    *(byte *)(param_1 + 0x1d6) = *(byte *)(param_1 + 0x1d6) | 0x10;
  }
  local_34 = 4;
  mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x80b,*(DWORD_PTR *)(param_1 + 0x1dc),
                  (DWORD_PTR)auStack_3c);
  if ((((local_38 == 0x207) || (local_38 == 0x208)) || (local_38 == 0x203)) || (local_38 == 0x201))
  {
    *(undefined *)(param_1 + 0x1d8) = 1;
  }
  if (*(char *)(param_1 + 0x1d8) != '\0') {
    *(byte *)(param_1 + 0x1d6) = *(byte *)(param_1 + 0x1d6) | 1;
  }
  *(undefined4 *)(param_1 + 0x1dc) = 0x20000;
  MVar1 = mciSendCommandA((uint)*(ushort *)(param_1 + 0x1e6),0x843,0x20000,(DWORD_PTR)local_30);
  *(MCIERROR *)(param_1 + 0x1f8) = MVar1;
  piVar3 = local_2c;
  piVar4 = local_1c;
  for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  *(int *)(param_1 + 0x204) = local_1c[2] - local_1c[0];
  *(int *)(param_1 + 0x208) = local_1c[3] - local_1c[1];
  return;
}

