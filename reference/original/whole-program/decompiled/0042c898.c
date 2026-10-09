/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042c898.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0042c898(int *param_1,LPSIZE param_2)

{
  int iVar1;
  HDC hdc;
  char *pcVar2;
  LPSIZE lpsz;
  char local_3c [26];
  char local_22 [26];
  
  pcVar2 = local_3c;
  iVar1 = 0;
  do {
    *pcVar2 = (char)iVar1 + 'A';
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
  } while (iVar1 != 0x1a);
  iVar1 = 0;
  pcVar2 = local_22;
  do {
    *pcVar2 = (char)iVar1 + 'a';
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
  } while (iVar1 != 0x1a);
  iVar1 = 0x34;
  pcVar2 = local_3c;
  lpsz = param_2;
  hdc = (HDC)FUN_0041a950(param_1);
  GetTextExtentPointA(hdc,pcVar2,iVar1,lpsz);
  param_2->cx = param_2->cx / 0x34;
  return;
}

