/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004082ec.
 * Inferred types, shared tails and runtime effects require assembly review. */

uint FUN_004082ec(int *param_1,int param_2)

{
  uint uVar1;
  code *pcVar2;
  
  pcVar2 = *(code **)(param_2 + 0xc);
  if (((uint)pcVar2 & 0xffffff00) != 0) {
    if (*(byte *)(param_2 + 0xf) < 0xfe) {
      uVar1 = (*pcVar2)(param_1,*(undefined4 *)(param_2 + 0x10));
      return uVar1;
    }
    if (*(byte *)(param_2 + 0xf) != 0xff) {
      uVar1 = (**(code **)((int)(short)pcVar2 + *param_1))();
      return uVar1;
    }
    pcVar2 = (code *)(uint)*(byte *)((int)param_1 + ((uint)pcVar2 & 0xffffff));
  }
  return CONCAT31((int3)((uint)param_1 >> 8),(char)pcVar2);
}

