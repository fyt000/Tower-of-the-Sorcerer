/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00406402.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00406402(undefined param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  char extraout_CL;
  uint uVar5;
  byte bVar6;
  int unaff_EBP;
  int unaff_ESI;
  byte *pbVar8;
  char cVar7;
  
  iVar2 = 1;
  uVar3 = *(uint *)(unaff_EBP + -8);
  if (uVar3 <= *(uint *)(unaff_EBP + 8)) {
    *(int *)(unaff_EBP + -8) = *(int *)(unaff_EBP + -8) + 1;
    puVar1 = (undefined4 *)(*(int *)(unaff_EBP + 0xc) + uVar3 * 8);
                    /* WARNING: Could not recover jumptable at 0x00406422. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(&DAT_00406429 + (uint)*(byte *)(puVar1 + 1) * 4))
              (*puVar1,param_2,CONCAT31((int3)((uint)param_3 >> 8),param_1) & 0xffffffdf);
    return;
  }
  do {
    uVar3 = FUN_0040627c(iVar2,*(undefined4 **)(unaff_EBP + -0x10),
                         *(int *)(unaff_EBP + -0x20) - (int)*(undefined4 **)(unaff_EBP + -0x10));
    if (extraout_CL == 'D') {
      if ((int)uVar3 < 0) {
        FUN_00406498(-uVar3);
        *(undefined *)(unaff_ESI + -1) = 0x2d;
        return;
      }
code_r0x00406498:
      uVar5 = 10;
LAB_0040649d:
      pbVar8 = (byte *)(unaff_EBP + -0x38);
      do {
        uVar4 = uVar3 / uVar5;
        cVar7 = (char)(uVar3 % uVar5);
        bVar6 = cVar7 + 0x30;
        if (0x39 < bVar6) {
          bVar6 = cVar7 + 0x37;
        }
        pbVar8 = pbVar8 + -1;
        *pbVar8 = bVar6;
        uVar3 = uVar4;
      } while (uVar4 != 0);
      uVar5 = (unaff_EBP + -0x38) - (int)pbVar8;
      uVar3 = *(uint *)(unaff_EBP + -0x1c);
      if (uVar3 < 0x10) {
        iVar2 = uVar3 - uVar5;
        if (uVar5 <= uVar3 && iVar2 != 0) {
          do {
            pbVar8 = pbVar8 + -1;
            *pbVar8 = 0x30;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        return;
      }
      return;
    }
    if (extraout_CL == 'U') goto code_r0x00406498;
    if (extraout_CL == 'X') {
      uVar5 = 0x10;
      goto LAB_0040649d;
    }
    iVar2 = 0;
  } while( true );
}

