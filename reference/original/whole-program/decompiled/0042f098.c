/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042f098.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042f098(int *param_1,undefined *param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined **ppuVar4;
  undefined4 *in_FS_OFFSET;
  bool bVar5;
  undefined4 uStackY_38;
  code *pcStackY_34;
  undefined4 local_2c;
  code *pcStack_28;
  undefined *puStack_24;
  int local_14;
  undefined *local_10;
  uint *local_c;
  int *local_8;
  
  puStack_24 = &stack0xfffffffc;
  local_c = (uint *)0x0;
  local_10 = (undefined *)0x0;
  local_14 = 0;
  pcStack_28 = thunk_FUN_00403140;
  local_2c = *in_FS_OFFSET;
  *in_FS_OFFSET = &local_2c;
  ppuVar4 = &local_10;
  pcStackY_34 = (code *)0x42f0c5;
  local_8 = param_1;
  FUN_00405fec((int)param_2,&local_14);
  pcStackY_34 = (code *)0x42f0d7;
  FUN_00403854(local_14,2,0x7fffffff,(int *)ppuVar4);
  FUN_004059cc(local_10,(LPSTR *)&local_c);
  uVar2 = extraout_ECX;
  uVar3 = extraout_EDX;
  ppuVar4 = (undefined **)PTR_PTR_004897e4;
  while ((bVar5 = ppuVar4 == (undefined **)0x0, !bVar5 &&
         (FUN_00403760((uint *)ppuVar4[1],local_c), uVar2 = extraout_ECX_00, uVar3 = extraout_EDX_00
         , !bVar5))) {
    ppuVar4 = (undefined **)ppuVar4[2];
  }
  if (ppuVar4 == (undefined **)0x0) {
    ppuVar4 = &PTR_PTR_FUN_004897d8;
  }
  iVar1 = FUN_00402c0c((int)*ppuVar4,CONCAT31((int3)((uint)uVar3 >> 8),1),uVar2);
  local_8[4] = iVar1;
  pcStackY_34 = thunk_FUN_00402f4c;
  uStackY_38 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStackY_38;
  FUN_0040a788(local_8,param_2);
  *in_FS_OFFSET = uStackY_38;
  *in_FS_OFFSET = local_2c;
  puStack_24 = &LAB_0042f180;
  pcStack_28 = (code *)0x42f178;
  FUN_004034fc(&local_14,3);
  return;
}

