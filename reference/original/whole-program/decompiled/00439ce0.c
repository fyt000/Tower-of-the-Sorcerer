/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00439ce0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00439ce0(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *local_c;
  int local_8;
  
  puStack_1c = &stack0xfffffffc;
  local_c = (undefined4 *)0x0;
  puStack_20 = &LAB_0043a2ea;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  iVar3 = 10;
  piVar4 = &DAT_0048c3fc;
  do {
    *piVar4 = 0;
    iVar2 = 4;
    piVar5 = piVar4 + -4;
    do {
      *piVar4 = *piVar4 + *piVar5;
      piVar5 = piVar5 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    piVar4[1] = 0;
    iVar2 = 1;
    piVar5 = piVar4 + -4;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
        piVar4[1] = piVar4[1] + *piVar5;
        break;
      case 2:
      case 4:
        piVar4[1] = piVar4[1] - *piVar5;
      }
      iVar2 = iVar2 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar2 != 6);
    piVar4 = piVar4 + 6;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 6;
  piVar4 = &DAT_0048c4dc;
  do {
    *piVar4 = 0;
    iVar2 = 10;
    piVar5 = piVar4 + -0x3c;
    do {
      *piVar4 = *piVar4 + *piVar5;
      piVar5 = piVar5 + 6;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    piVar4[6] = 0;
    iVar2 = 1;
    piVar5 = piVar4 + -0x3c;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 9:
      case 0xb:
        piVar4[6] = piVar4[6] + *piVar5;
        break;
      case 2:
      case 4:
      case 6:
      case 8:
      case 10:
        piVar4[6] = piVar4[6] - *piVar5;
      }
      iVar2 = iVar2 + 1;
      piVar5 = piVar5 + 6;
    } while (iVar2 != 0xc);
    piVar4 = piVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  DAT_0048c508 = DAT_0048ab30 * 100 - DAT_0048aa18;
  puVar1 = &stack0xfffffffc;
  local_8 = param_1;
  switch(DAT_0048aa18) {
  case 1:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_1c = &stack0xfffffffc;
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option1.dat");
    puVar1 = puStack_1c;
    break;
  case 2:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_1c = &stack0xfffffffc;
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option2.dat");
    puVar1 = puStack_1c;
    break;
  case 3:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_1c = &stack0xfffffffc;
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option3.dat");
    puVar1 = puStack_1c;
    break;
  case 4:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_1c = &stack0xfffffffc;
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option4.dat");
    puVar1 = puStack_1c;
    break;
  case 5:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option5.dat");
    puVar1 = puStack_1c;
  }
  puStack_1c = puVar1;
  FUN_0040414d((undefined4 *)&DAT_0048a770,DAT_0048a76c);
  FUN_004045a4((HANDLE *)&DAT_0048a770,(HANDLE)0x1);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048a770,&DAT_0048c3ec,0x120,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048a770);
  FUN_00402710();
  switch(DAT_0048aa18) {
  case 1:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option11.dat");
    break;
  case 2:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option21.dat");
    break;
  case 3:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option31.dat");
    break;
  case 4:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option41.dat");
    break;
  case 5:
    piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
    FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\option51.dat");
  }
  (**(code **)(**(int **)(*(int *)(local_8 + 700) + 0x118) + 0x38))();
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x2b8) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x21c) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x220) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x224) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x228) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x22c) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x230) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x234) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x238) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x34))(piVar4,*(undefined4 *)(*(int *)(local_8 + 0x23c) + 0x118));
  piVar4 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  (**(code **)(*piVar4 + 0x5c))(piVar4,DAT_0048a76c);
  if (DAT_0048aa10 != 0) {
    DAT_0048aa10 = 0;
  }
  if (DAT_0048aa14 != 0) {
    DAT_0048aa14 = 0;
  }
  if (DAT_0048aa18 != 0) {
    DAT_0048aa18 = 0;
  }
  piVar4 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
  (**(code **)(*piVar4 + 0xc))(piVar4,0,&local_c);
  FUN_0040369c((int *)&DAT_0048a76c,local_c,(undefined4 *)"\\save0.dat");
  FUN_0040414d((undefined4 *)&DAT_0048a770,DAT_0048a76c);
  FUN_004045a4((HANDLE *)&DAT_0048a770,(HANDLE)0x1);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048a770,&DAT_0048ab68,0x1881,(uint *)0x0);
  FUN_00402710();
  FUN_00404254((HANDLE *)&DAT_0048a770,&DAT_0048a8bc,0x2ac,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048a770);
  FUN_00402710();
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0043a2f1;
  puStack_20 = (undefined *)0x43a2e9;
  FUN_004034dc((int *)&local_c);
  return;
}

