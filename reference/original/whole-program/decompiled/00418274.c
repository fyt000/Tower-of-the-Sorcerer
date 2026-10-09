/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00418274.
 * Inferred types, shared tails and runtime effects require assembly review. */

bool FUN_00418274(int *param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  HIMAGELIST himlTrack;
  
  bVar1 = FUN_00417800((int)param_1);
  if (bVar1) {
    himlTrack = (HIMAGELIST)FUN_00417984(param_1);
    ImageList_BeginDrag(himlTrack,param_2,param_3,param_4);
    *(undefined *)(param_1 + 0x11) = 1;
  }
  return bVar1;
}

