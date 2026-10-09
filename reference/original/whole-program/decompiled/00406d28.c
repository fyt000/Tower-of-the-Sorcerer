/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406d28.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406d28(void)

{
  LCID LVar1;
  undefined4 uVar2;
  uint uVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int extraout_ECX_03;
  undefined4 extraout_ECX_04;
  undefined4 extraout_ECX_05;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_c;
  undefined4 *local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_8 = (undefined4 *)0x0;
  local_c = 0;
  puStack_20 = &LAB_00406f35;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  LVar1 = GetSystemDefaultLCID();
  FUN_004067dc(LVar1,0x14,0,(int *)&local_8);
  FUN_0040352c(&DAT_0048a548,local_8);
  FUN_004067dc(LVar1,0x1b,0x406f4c,(int *)&local_8);
  uVar2 = FUN_00405bd8((byte *)local_8,0,extraout_ECX);
  DAT_0048a54c = (undefined)uVar2;
  FUN_004067dc(LVar1,0x1c,0x406f4c,(int *)&local_8);
  uVar2 = FUN_00405bd8((byte *)local_8,0,extraout_ECX_00);
  DAT_0048a54d = (undefined)uVar2;
  uVar3 = FUN_00406828(LVar1,0xf,CONCAT31((int3)((uint)extraout_ECX_01 >> 8),0x2c));
  DAT_0048a54e = (undefined)uVar3;
  uVar3 = FUN_00406828(LVar1,0xe,CONCAT31((int3)((uint)extraout_ECX_02 >> 8),0x2e));
  DAT_0048a54f = (undefined)uVar3;
  FUN_004067dc(LVar1,0x19,0x406f4c,(int *)&local_8);
  uVar2 = FUN_00405bd8((byte *)local_8,0,extraout_ECX_03);
  DAT_0048a550 = (undefined)uVar2;
  uVar3 = FUN_00406828(LVar1,0x1d,CONCAT31((int3)((uint)extraout_ECX_04 >> 8),0x2f));
  DAT_0048a551 = (undefined)uVar3;
  uVar3 = FUN_00406828(LVar1,0x1e,CONCAT31((int3)((uint)extraout_ECX_05 >> 8),0x3a));
  DAT_0048a55c = (undefined)uVar3;
  FUN_004067dc(LVar1,0x1f,0x406f58,&local_c);
  FUN_00406994(local_c,(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a554,local_8);
  FUN_004067dc(LVar1,0x20,0x406f68,&local_c);
  FUN_00406994(local_c,(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a558,local_8);
  FUN_004067dc(LVar1,0x28,0x406f80,(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a560,local_8);
  FUN_004067dc(LVar1,0x29,0x406f8c,(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a564,local_8);
  FUN_004067dc(LVar1,0x1003,0x406f98,&local_c);
  FUN_00406ad8(local_c,'\0',(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a568,local_8);
  FUN_004067dc(LVar1,0x1003,0x406fa8,&local_c);
  FUN_00406ad8(local_c,'\x01',(int *)&local_8);
  FUN_0040352c((int *)&DAT_0048a56c,local_8);
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_00406f3c;
  puStack_20 = (undefined *)0x406f34;
  FUN_004034fc(&local_c,2);
  return;
}

