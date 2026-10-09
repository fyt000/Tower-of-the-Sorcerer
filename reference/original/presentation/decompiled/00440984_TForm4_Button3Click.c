/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00440984.
 * Inferred types and shared tails require assembly review. */

void TForm4_Button3Click(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *puStack_c;
  uint *puStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_8 = (uint *)0x0;
  puStack_c = (undefined4 *)0x0;
  puStack_20 = &UNK_00440a2b;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  FUN_004135a4(*(int **)(param_1 + 0x1c8),(int *)&puStack_c);
  FUN_0040369c((int *)&puStack_8,puStack_c,(undefined4 *)&UNK_00440a44);
  cVar1 = FUN_0042cf9c((uint *)"Make holder",(uint *)"Please, input the name of holder",&puStack_8);
  if (cVar1 == '\x01') {
    bVar2 = FUN_00406090((undefined *)puStack_8);
    if (bVar2) {
      FUN_004135d4(*(int **)(param_1 + 0x1c8),puStack_8);
      FUN_0043e08c(*(int **)(param_1 + 0x1b0),*(byte *)puStack_8);
      (**(code **)(**(int **)(param_1 + 0x1b4) + 0x8c))(*(int **)(param_1 + 0x1b4),puStack_8);
    }
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &UNK_00440a32;
  puStack_20 = (undefined *)0x440a22;
  FUN_004034dc((int *)&puStack_c);
  puStack_20 = (undefined *)0x440a2a;
  FUN_004034dc((int *)&puStack_8);
  return;
}

