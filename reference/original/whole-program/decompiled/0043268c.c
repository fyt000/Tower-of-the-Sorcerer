/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0043268c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0043268c(uint param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  HBITMAP pHVar2;
  uint uVar3;
  
  uVar3 = param_1 & 0x7f;
  if (*(int *)(&DAT_0048a734 + uVar3 * 4) == 0) {
    iVar1 = FUN_0041d718(0x4193b4,CONCAT31((int3)((uint)param_2 >> 8),1),param_3);
    *(int *)(&DAT_0048a734 + uVar3 * 4) = iVar1;
    pHVar2 = LoadBitmapA(DAT_0048a014,*(LPCSTR *)(&DAT_00489864 + uVar3 * 4));
    FUN_0041e0ec(*(int *)(&DAT_0048a734 + (param_1 & 0xff) * 4),pHVar2);
  }
  return *(undefined4 *)(&DAT_0048a734 + uVar3 * 4);
}

