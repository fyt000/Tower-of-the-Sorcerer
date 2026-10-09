/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421ac4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421ac4(int **param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  char cVar3;
  
  cVar3 = (char)param_2;
  if (cVar3 != *(char *)((int)param_1 + 0x11a)) {
    if ((cVar3 == '\x01') && (*(char *)((int)param_1 + 0x11b) == '\0')) {
      FUN_00421dc4(param_1,'\x01');
      param_3 = extraout_ECX;
      param_2 = extraout_EDX;
    }
    if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
      FUN_00415130((int *)param_1);
      param_3 = extraout_ECX_00;
      param_2 = extraout_EDX_00;
    }
    cVar1 = *(char *)((int)param_1 + 0x11a);
    *(char *)((int)param_1 + 0x11a) = cVar3;
    if (((cVar3 == '\x02') || (cVar1 == '\x02')) && (*(char *)((int)param_1 + 0xc5) == '\0')) {
      iVar2 = root_00421e40(param_1);
      FUN_004136e8((int *)param_1,iVar2);
      param_3 = extraout_ECX_01;
      param_2 = extraout_EDX_01;
    }
    if ((*(byte *)(param_1 + 7) & 0x10) == 0) {
      FUN_004152ac(param_1);
      param_3 = extraout_ECX_02;
      param_2 = extraout_EDX_02;
    }
    if (cVar3 == '\x01') {
      FUN_00421548((int *)param_1,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    }
  }
  return;
}

