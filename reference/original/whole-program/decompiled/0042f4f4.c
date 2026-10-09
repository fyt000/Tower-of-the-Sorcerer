/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f4f4.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_0042f4f4(int param_1)

{
  root_00429244(param_1);
  if (*(HMODULE *)(param_1 + 0x128) != (HMODULE)0x0) {
    FreeLibrary(*(HMODULE *)(param_1 + 0x128));
  }
  return;
}

