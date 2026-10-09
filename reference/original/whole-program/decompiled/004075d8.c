/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004075d8.
 * Inferred types, shared tails and runtime effects require assembly review. */

int FUN_004075d8(undefined4 param_1,undefined4 param_2)

{
  LPVOID pvVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  int iVar2;
  undefined4 local_c;
  undefined local_8;
  
  for (iVar2 = 0; iVar2 < 7; iVar2 = iVar2 + 1) {
    pvVar1 = FUN_00403498();
    param_2 = extraout_EDX;
    if (*(int *)((int)pvVar1 + 4) == (&DAT_004890e0)[iVar2 * 2]) break;
  }
  if (iVar2 < 7) {
    iVar2 = FUN_004074cc(0x405460,CONCAT31((int3)((uint)param_2 >> 8),1),(&DAT_004890e4)[iVar2 * 2])
    ;
  }
  else {
    pvVar1 = FUN_00403498();
    local_c = *(undefined4 *)((int)pvVar1 + 4);
    local_8 = 0;
    iVar2 = FUN_0040753c(0x405460,CONCAT31((int3)((uint)extraout_EDX_00 >> 8),1),0xff88,0,&local_c);
  }
  pvVar1 = FUN_00403498();
  *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)((int)pvVar1 + 4);
  pvVar1 = FUN_00403498();
  *(undefined4 *)((int)pvVar1 + 4) = 0;
  return iVar2;
}

