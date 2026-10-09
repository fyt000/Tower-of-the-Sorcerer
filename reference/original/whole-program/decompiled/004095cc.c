/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004095cc.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_004095cc(undefined *param_1,int **param_2)

{
  LPCSTR lpName;
  HRSRC hResData;
  int *piVar1;
  int *piVar2;
  undefined4 extraout_EDX;
  undefined4 *in_FS_OFFSET;
  undefined4 uVar3;
  LPCSTR lpType;
  
  lpType = (LPCSTR)0xa;
  lpName = FUN_00403814(param_1);
  hResData = FindResourceA(DAT_0048a014,lpName,lpType);
  if (hResData != (HRSRC)0x0) {
    FreeResource(hResData);
    piVar1 = (int *)FUN_0040b3d4(0x408fbc,CONCAT31((int3)((uint)extraout_EDX >> 8),1),DAT_0048a014,
                                 (LPCSTR)0xa,param_1);
    uVar3 = *in_FS_OFFSET;
    *in_FS_OFFSET = &stack0xffffffe4;
    piVar2 = (int *)FUN_0040afc0(piVar1,*param_2);
    *param_2 = piVar2;
    *in_FS_OFFSET = uVar3;
    FUN_00402c34(piVar1);
    return;
  }
  return;
}

