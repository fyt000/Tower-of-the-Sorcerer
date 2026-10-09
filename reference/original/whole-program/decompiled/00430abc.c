/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430abc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430abc(int *param_1,int param_2)

{
  POINT pt;
  BOOL BVar1;
  LONG LStack_14;
  LONG LStack_10;
  
  if (*(char *)(param_1 + 0x67) != '\0') {
    FUN_00409224((int)*(short *)(param_2 + 8),(int)*(short *)(param_2 + 10),&LStack_14);
    pt.y = LStack_10;
    pt.x = LStack_14;
    BVar1 = PtInRect((RECT *)(param_1 + 0x68),pt);
    if ((BVar1 != 0) != (bool)*(byte *)((int)param_1 + 0x19d)) {
      *(byte *)((int)param_1 + 0x19d) = *(byte *)((int)param_1 + 0x19d) ^ 1;
      FUN_00430420(param_1,*(byte *)((int)param_1 + 0x19e),param_1[0x68]);
    }
  }
  return;
}

