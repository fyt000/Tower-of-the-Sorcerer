/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406850.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406850(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *in_FS_OFFSET;
  undefined4 **ppuVar4;
  undefined4 uStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  int local_14;
  undefined4 *local_10;
  LCID local_c;
  int local_8;
  
  puStack_24 = &stack0xfffffffc;
  local_10 = (undefined4 *)0x0;
  local_14 = 0;
  puStack_28 = &LAB_00406986;
  uStack_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_2c;
  local_c = GetSystemDefaultLCID();
  iVar1 = 1;
  piVar2 = (int *)&DAT_0048a570;
  piVar3 = (int *)&DAT_0048a5a0;
  do {
    ppuVar4 = &local_10;
    FUN_00405bf0(iVar1 + 0xffbf,&local_14);
    FUN_004067dc(local_c,iVar1 + 0x43,local_14,(int *)ppuVar4);
    FUN_0040352c(piVar2,local_10);
    ppuVar4 = &local_10;
    FUN_00405bf0(iVar1 + 0xffcf,&local_14);
    FUN_004067dc(local_c,iVar1 + 0x37,local_14,(int *)ppuVar4);
    FUN_0040352c(piVar3,local_10);
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 != 0xd);
  iVar1 = 1;
  piVar2 = (int *)&DAT_0048a5d0;
  piVar3 = (int *)&DAT_0048a5ec;
  do {
    local_8 = (iVar1 + 5) % 7;
    ppuVar4 = &local_10;
    FUN_00405bf0(iVar1 + 0xffdf,&local_14);
    FUN_004067dc(local_c,local_8 + 0x31,local_14,(int *)ppuVar4);
    FUN_0040352c(piVar2,local_10);
    ppuVar4 = &local_10;
    FUN_00405bf0(iVar1 + 0xffe6,&local_14);
    FUN_004067dc(local_c,local_8 + 0x2a,local_14,(int *)ppuVar4);
    FUN_0040352c(piVar3,local_10);
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 != 8);
  *in_FS_OFFSET = uStack_2c;
  puStack_24 = &LAB_0040698d;
  puStack_28 = (undefined *)0x406985;
  FUN_004034fc(&local_14,2);
  return;
}

