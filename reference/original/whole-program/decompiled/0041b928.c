/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041b928.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041b928(HANDLE param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined auStack_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  short local_10;
  short local_e;
  
  GetObjectA(param_1,0x18,auStack_20);
  *param_2 = 0x28;
  param_2[1] = local_1c;
  param_2[2] = local_18;
  if (param_3 == 0) {
    *(short *)((int)param_2 + 0xe) = local_e * local_10;
  }
  else if (param_3 == 2) {
    *(undefined2 *)((int)param_2 + 0xe) = 1;
  }
  else if (param_3 == 0x10) {
    *(undefined2 *)((int)param_2 + 0xe) = 4;
  }
  else if (param_3 == 0x100) {
    *(undefined2 *)((int)param_2 + 0xe) = 8;
  }
  *(undefined2 *)(param_2 + 3) = 1;
  param_2[6] = 0;
  param_2[7] = 0;
  param_2[8] = 0;
  param_2[9] = 0;
  param_2[4] = 0;
  if ((*(short *)((int)param_2 + 0xe) == 0x10) || (*(short *)((int)param_2 + 0xe) == 0x20)) {
    *(undefined2 *)((int)param_2 + 0xe) = 0x18;
  }
  iVar1 = FUN_0041b46c(param_2[1] * (uint)*(ushort *)((int)param_2 + 0xe));
  param_2[5] = iVar1 * param_2[2];
  return;
}

