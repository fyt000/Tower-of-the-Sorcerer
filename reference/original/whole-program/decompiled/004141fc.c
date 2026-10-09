/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004141fc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004141fc(int **param_1,int param_2)

{
  POINT pt;
  BOOL BVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  LONG LStack_24;
  LONG LStack_20;
  RECT RStack_1c;
  
  (*(code *)(*param_1)[-4])(param_1,param_2);
  if ((*(byte *)(param_1 + 0xd) & 2) != 0) {
    FUN_00413758(param_1,'\0');
  }
  if ((*(byte *)((int)param_1 + 0x36) & 2) != 0) {
    *(byte *)((int)param_1 + 0x36) = *(byte *)((int)param_1 + 0x36) & 0xfd;
    FUN_004052e0(*(undefined4 *)(param_2 + 8),&LStack_24);
    (*(code *)(*param_1)[0xb])(param_1,&RStack_1c);
    pt.y = LStack_20;
    pt.x = LStack_24;
    BVar1 = PtInRect(&RStack_1c,pt);
    if (BVar1 != 0) {
      FUN_00402cdc((int *)param_1,extraout_EDX,extraout_ECX);
    }
  }
  FUN_004141c0((int *)param_1,param_2,0);
  return;
}

