/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040fd90.
 * Inferred types, shared tails and runtime effects require assembly review. */

int * root_0040fd90(int *param_1,char param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((int *)param_1[0x11] != (int *)0x0) {
    FUN_004106d8((int *)param_1[0x11],(int)param_1);
    param_1[0x11] = 0;
  }
  if (param_1[9] != 0) {
    FUN_00410120(param_1,0);
    DestroyMenu((HMENU)param_1[9]);
    FUN_0040fe58((int)param_1);
  }
  while( true ) {
    iVar2 = FUN_0041040c((int)param_1);
    if (iVar2 < 1) break;
    piVar1 = (int *)FUN_0041041c((int)param_1,0);
    FUN_00402c34(piVar1);
  }
  FUN_00402c34((int *)param_1[0xf]);
  if (*(ushort *)(param_1 + 0xc) != 0) {
    FUN_00409cbc(DAT_0048a68c,(uint)*(ushort *)(param_1 + 0xc),'\0');
  }
  FUN_0040e4fc(param_1,'\0');
  if (param_2 != '\0') {
    FUN_00402e48(param_1);
  }
  return param_1;
}

