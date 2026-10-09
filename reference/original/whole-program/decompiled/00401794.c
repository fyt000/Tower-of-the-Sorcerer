/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401794.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401794(int param_1,int **param_2)

{
  int **ppiVar1;
  uint uVar2;
  int *local_18 [2];
  
  uVar2 = param_1 + 0x3fffU & 0xffffc000;
  ppiVar1 = DAT_0048a450;
  do {
    for (; (int ***)ppiVar1 != &DAT_0048a450; ppiVar1 = (int **)*ppiVar1) {
      if ((int)uVar2 <= (int)ppiVar1[3]) {
        FUN_00401680((uint)ppiVar1[2],uVar2,param_2);
        if (*param_2 == (int *)0x0) {
          return;
        }
        ppiVar1[2] = (int *)((int)ppiVar1[2] + (int)param_2[1]);
        ppiVar1[3] = (int *)((int)ppiVar1[3] - (int)param_2[1]);
        if (ppiVar1[3] != (int *)0x0) {
          return;
        }
        FUN_004013d0((int *)ppiVar1);
        return;
      }
    }
    FUN_004014ec(uVar2,param_2);
    if (*param_2 == (int *)0x0) {
      return;
    }
    FUN_004013e8((int **)&DAT_0048a450,param_2,local_18);
    ppiVar1 = DAT_0048a450;
  } while (local_18[0] != (int *)0x0);
  FUN_004015c8(*param_2,(int)param_2[1],local_18);
  *param_2 = (int *)0x0;
  return;
}

