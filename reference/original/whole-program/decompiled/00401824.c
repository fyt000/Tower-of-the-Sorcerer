/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401824.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401824(LPVOID param_1,int param_2,LPVOID *param_3)

{
  int **ppiVar1;
  uint uVar2;
  int *local_20;
  int local_1c;
  int *local_18 [2];
  
  uVar2 = param_2 + 0x3fffU & 0xffffc000;
  ppiVar1 = DAT_0048a450;
LAB_0040184a:
  do {
    for (; ((int ***)ppiVar1 != &DAT_0048a450 && ((int *)param_1 != ppiVar1[2]));
        ppiVar1 = (int **)*ppiVar1) {
    }
    if ((int *)param_1 == ppiVar1[2]) {
      if ((int)uVar2 <= (int)ppiVar1[3]) goto LAB_004018f7;
      FUN_00401550((LPVOID)((int)ppiVar1[2] + (int)ppiVar1[3]),uVar2 - (int)ppiVar1[3],&local_20);
      if (local_20 != (int *)0x0) {
        FUN_004013e8((int **)&DAT_0048a450,&local_20,local_18);
        ppiVar1 = DAT_0048a450;
        if (local_18[0] == (int *)0x0) {
          FUN_004015c8(local_20,local_1c,local_18);
          *param_3 = (LPVOID)0x0;
          return;
        }
        goto LAB_0040184a;
      }
    }
    FUN_00401550(param_1,uVar2,&local_20);
    if (local_20 == (int *)0x0) {
LAB_004018f7:
      if (((int *)param_1 != ppiVar1[2]) || ((int)ppiVar1[3] < (int)uVar2)) {
        *param_3 = (LPVOID)0x0;
        return;
      }
      FUN_00401680((uint)ppiVar1[2],uVar2,param_3);
      if (*param_3 == (LPVOID)0x0) {
        return;
      }
      ppiVar1[2] = (int *)((int)ppiVar1[2] + (int)param_3[1]);
      ppiVar1[3] = (int *)((int)ppiVar1[3] - (int)param_3[1]);
      if (ppiVar1[3] != (int *)0x0) {
        return;
      }
      FUN_004013d0((int *)ppiVar1);
      return;
    }
    FUN_004013e8((int **)&DAT_0048a450,&local_20,local_18);
    ppiVar1 = DAT_0048a450;
    if (local_18[0] == (int *)0x0) {
      FUN_004015c8(local_20,local_1c,local_18);
      *param_3 = (LPVOID)0x0;
      return;
    }
  } while( true );
}

