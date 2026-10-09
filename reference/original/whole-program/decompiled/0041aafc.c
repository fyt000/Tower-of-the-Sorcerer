/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041aafc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041aafc(int param_1)

{
  HGDIOBJ h;
  
  h = (HGDIOBJ)FUN_00419fd0(*(int *)(param_1 + 0x10));
  SelectObject(*(HDC *)(param_1 + 4),h);
  SetROP2(*(HDC *)(param_1 + 4),
          (uint)*(ushort *)(&DAT_004894fc + (uint)*(byte *)(*(int *)(param_1 + 0x10) + 0x10) * 2));
  return;
}

