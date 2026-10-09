/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040258c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040258c(undefined4 *param_1,uint param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_20;
  
  if ((DAT_0048a419 == '\0') && (cVar1 = FUN_004019d4(), cVar1 == '\0')) {
    return 0;
  }
  uStack_20 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_20;
  if (DAT_0048a036 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  uVar2 = FUN_004023bc((int)param_1,param_2);
  if ((char)uVar2 == '\0') {
    puVar3 = FUN_00402090(param_2);
    uVar4 = (param_1[-1] & 0x7ffffffc) - 4;
    if ((int)param_2 < (int)uVar4) {
      uVar4 = param_2;
    }
    if (puVar3 != (uint *)0x0) {
      FUN_00402870(param_1,puVar3,uVar4);
      FUN_00402218((int)param_1);
    }
  }
  uVar2 = 0;
  *in_FS_OFFSET = uStack_20;
  if (DAT_0048a036 != '\0') {
    uStack_20 = 0x40263d;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0048a420);
  }
  return uVar2;
}

