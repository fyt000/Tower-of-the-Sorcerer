/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423c94.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00423c94(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  HCURSOR pHVar3;
  
  puVar2 = *(undefined4 **)(param_1 + 0x34);
  while (puVar2 != (undefined4 *)0x0) {
    if (((int)puVar2[1] < -0xb) || (0 < (int)puVar2[1])) {
      DestroyCursor((HCURSOR)puVar2[2]);
    }
    puVar1 = (undefined4 *)*puVar2;
    FUN_00402668((int)puVar2);
    puVar2 = puVar1;
  }
  pHVar3 = LoadCursorA((HINSTANCE)0x0,&DAT_00007f00);
  if (pHVar3 != *(HCURSOR *)(param_1 + 0x38)) {
    DestroyCursor(*(HCURSOR *)(param_1 + 0x38));
  }
  return;
}

