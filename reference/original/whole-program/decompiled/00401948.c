/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00401948.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00401948(int param_1,int param_2,int **param_3)

{
  uint uVar1;
  uint uVar2;
  int *local_1c;
  int local_18;
  int *local_14;
  int local_10;
  
  uVar1 = param_1 + 0x3fffU & 0xffffc000;
  uVar2 = param_2 + param_1 & 0xffffc000;
  if (uVar1 < uVar2) {
    FUN_00401714(uVar1,uVar2 - uVar1,param_3);
    FUN_004013e8((int **)&DAT_0048a450,param_3,&local_1c);
    if (local_1c != (int *)0x0) {
      FUN_004015c8(local_1c,local_18,&local_14);
      local_1c = local_14;
      local_18 = local_10;
    }
    if (local_1c != (int *)0x0) {
      FUN_0040145c((int **)&DAT_0048a450,&local_1c);
    }
  }
  else {
    *param_3 = (int *)0x0;
  }
  return;
}

