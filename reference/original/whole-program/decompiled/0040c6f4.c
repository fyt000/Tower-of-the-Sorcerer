/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040c6f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040c6f4(int *param_1,char **param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  char **extraout_EDX;
  char **extraout_EDX_00;
  int iVar3;
  int iVar4;
  char *local_14;
  undefined4 local_10;
  char **local_c;
  int *local_8;
  
  iVar3 = DAT_004891c8[2];
  puVar2 = DAT_004891c8;
  local_10 = param_3;
  local_c = param_2;
  local_8 = param_1;
  if (-1 < iVar3 + -1) {
    iVar4 = 0;
    do {
      iVar1 = FUN_00409a40(DAT_004891c8,iVar4);
      puVar2 = (undefined4 *)*local_c;
      param_2 = extraout_EDX;
      if ((puVar2 == *(undefined4 **)(iVar1 + 4)) &&
         (puVar2 = (undefined4 *)(**(code **)(iVar1 + 8))(local_10,&local_14),
         param_2 = extraout_EDX_00, (char)puVar2 != '\0')) {
        FUN_0040838c(local_8,local_c,local_14);
        return;
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  FUN_0040b8e0(puVar2,param_2);
  return;
}

