/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004314cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_004314cc(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*(char *)(param_1 + 0x1d5) == '\0') {
    uVar2 = FUN_004074cc(0x42fa18,CONCAT31((int3)((uint)param_2 >> 8),1),0xf0d0);
    FUN_004031f8(uVar2);
  }
  cVar1 = FUN_0043206c(param_1);
  if (cVar1 == '\x02') {
    root_00431518(param_1);
    return;
  }
  cVar1 = FUN_0043206c(param_1);
  if (cVar1 == '\x05') {
    root_004315ac(param_1);
  }
  return;
}

