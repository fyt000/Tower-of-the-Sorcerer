/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004255a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004255a8(int param_1)

{
  tagPOINT tStack_c;
  
  FUN_004254d0(param_1);
  if (*(char *)(param_1 + 0x66) == '\0') {
    GetCursorPos(&tStack_c);
    FUN_00425640(param_1,&tStack_c.x);
  }
  else if (*(char *)(param_1 + 0x66) == '\x01') {
    FUN_004255dc(param_1);
  }
  return;
}

