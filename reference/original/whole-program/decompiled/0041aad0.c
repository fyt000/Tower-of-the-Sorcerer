/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041aad0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041aad0(int param_1)

{
  HGDIOBJ h;
  COLORREF color;
  
  h = (HGDIOBJ)FUN_00419c90(*(int *)(param_1 + 0xc));
  SelectObject(*(HDC *)(param_1 + 4),h);
  color = FUN_00419b00(*(uint *)(*(int *)(param_1 + 0xc) + 0x10));
  SetTextColor(*(HDC *)(param_1 + 4),color);
  return;
}

