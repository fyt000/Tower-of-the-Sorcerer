/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041dccc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041dccc(int param_1,undefined4 param_2,HGDIOBJ param_3,HPALETTE param_4)

{
  char cVar1;
  undefined uVar2;
  undefined4 uVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_50;
  code *pcStack_4c;
  undefined *puStack_48;
  undefined4 local_44;
  code *pcStack_40;
  undefined *puStack_3c;
  undefined local_20 [4];
  int local_1c;
  int local_18;
  short local_10;
  short local_e;
  BOOL local_8;
  
  if (((short)param_2 != 2) || (param_3 == (HGDIOBJ)0x0)) {
    FUN_0041ac20(0xf021,param_2);
  }
  FUN_0041db9c(param_1);
  puStack_3c = (undefined *)0x41dd00;
  GetObjectA(param_3,0x18,local_20);
  if ((local_10 == 1) && (local_e == 1)) {
    cVar1 = '\x01';
  }
  else {
    cVar1 = '\0';
  }
  puStack_3c = (undefined *)0x41dd28;
  local_8 = FUN_0041d400(param_3,param_4,local_1c,cVar1,0,local_18);
  pcStack_40 = thunk_FUN_00402f4c;
  local_44 = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_44;
  puStack_48 = (undefined *)0x41dd41;
  puStack_3c = &stack0xfffffffc;
  uVar3 = FUN_0041d66c(param_4);
  pcStack_4c = thunk_FUN_00402f4c;
  uStack_50 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_50;
  if ((local_10 == 1) && (local_e == 1)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  puStack_48 = &stack0xfffffffc;
  FUN_0041de0c(param_1,local_8,uVar3,0,0,0,0,uVar2,local_18,local_1c);
  *in_FS_OFFSET = uStack_50;
  *in_FS_OFFSET = local_44;
  puStack_3c = (undefined *)0x41ddd1;
  FUN_0041bd8c(param_1);
  return;
}

