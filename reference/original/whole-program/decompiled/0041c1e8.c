/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c1e8.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c1e8(int param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  code **in_FS_OFFSET;
  bool bVar3;
  code *pcStackY_4c;
  code *pcStackY_44;
  code *pcVar4;
  undefined **ppuVar5;
  code *pcStack_38;
  code *pcStack_34;
  undefined *puStack_30;
  uint *local_20;
  undefined local_1c;
  int local_18;
  undefined *local_14;
  int *local_10;
  uint *local_c;
  int local_8;
  
  puStack_30 = &stack0xfffffffc;
  local_14 = (undefined *)0x0;
  local_18 = 0;
  local_c = (uint *)0x0;
  pcStack_34 = thunk_FUN_00403140;
  pcStack_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = (code *)&pcStack_38;
  ppuVar5 = &local_14;
  local_8 = param_2;
  FUN_00405fec(param_2,&local_18);
  FUN_00403854(local_18,2,0x7fffffff,(int *)ppuVar5);
  FUN_004059cc(local_14,(LPSTR *)&local_c);
  uVar2 = extraout_EDX;
  piVar1 = (int *)PTR_PTR_0048956c;
  do {
    bVar3 = piVar1 == (int *)0x0;
    if (bVar3) {
      local_1c = 0xb;
      pcVar4 = (code *)0x0;
      pcStackY_44 = (code *)0x41c2e4;
      local_20 = local_c;
      uVar2 = FUN_0040753c(0x4189f4,CONCAT31((int3)((uint)uVar2 >> 8),1),0xf020,0,&local_20);
      pcStackY_44 = (code *)0x41c2e9;
      FUN_004031f8(uVar2);
LAB_0041c2e9:
      *in_FS_OFFSET = pcVar4;
      pcStack_38 = (code *)&LAB_0041c313;
      FUN_004034fc(&local_18,2);
      FUN_004034dc((int *)&local_c);
      return;
    }
    FUN_00403760((uint *)piVar1[1],local_c);
    if (bVar3) {
      local_10 = (int *)(**(code **)(*piVar1 + 0xc))(*piVar1,1);
      pcVar4 = thunk_FUN_00402f4c;
      pcStackY_44 = *in_FS_OFFSET;
      *in_FS_OFFSET = (code *)&pcStackY_44;
      (**(code **)(*local_10 + 0x34))(local_10,local_8);
      *in_FS_OFFSET = pcStackY_4c;
      pcStackY_44 = (code *)0x41c2a4;
      FUN_00402c34(*(int **)(param_1 + 4));
      *(int **)(param_1 + 4) = local_10;
      local_10[2] = param_1;
      local_10[1] = (int)FUN_0041c378;
      pcStackY_44 = (code *)0x41c2bd;
      FUN_0041c378(param_1);
      goto LAB_0041c2e9;
    }
    piVar1 = (int *)piVar1[4];
    uVar2 = extraout_EDX_00;
  } while( true );
}

