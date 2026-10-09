/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430718.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430718(int *param_1)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  
  piVar1 = (int *)param_1[0x40];
  FUN_0041a20c((int *)piVar1[5],'\x01');
  FUN_00419fa8((int *)piVar1[4],0x80000006);
  FUN_0041a060((int *)piVar1[4],1);
  FUN_0041a73c(piVar1,0,0,param_1[0xc],param_1[0xb]);
  iVar3 = 0;
  bVar2 = 0;
  do {
    if (*(char *)(param_1 + (uint)bVar2 * 4 + 0x41) != '\0') {
      FUN_00430420(param_1,bVar2,iVar3);
      iVar3 = iVar3 + param_1[0x6c] + -1;
    }
    bVar2 = bVar2 + 1;
  } while (bVar2 != 9);
  return;
}

