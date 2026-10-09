/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421574.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421574(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if ((*(char *)(param_1 + 0x11a) == '\x01') && (*(char *)(param_1 + 0x37) != '\0')) {
    uVar1 = FUN_004074cc(0x41117c,CONCAT31((int3)((uint)param_2 >> 8),1),0xf030);
    FUN_004031f8(uVar1);
  }
  return;
}

