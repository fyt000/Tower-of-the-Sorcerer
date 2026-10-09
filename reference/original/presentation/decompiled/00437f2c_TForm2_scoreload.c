/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 00437f2c.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00437f2c(int param_1,byte param_2)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_3c;
  undefined *puStack_38;
  undefined *puStack_34;
  undefined4 uStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined4 *local_18;
  int local_14;
  int local_10;
  byte local_9;
  int local_8;
  
  puStack_28 = &stack0xfffffffc;
  local_18 = (undefined4 *)0x0;
  puStack_2c = &LAB_00439b19;
  uStack_30 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_30;
  puVar1 = &stack0xfffffffc;
  local_9 = param_2;
  local_8 = param_1;
  switch(param_2) {
  case 1:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x437f96;
    puStack_28 = &stack0xfffffffc;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x437fa8;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option1.dat");
    puVar1 = puStack_28;
    break;
  case 2:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x437fc8;
    puStack_28 = &stack0xfffffffc;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x437fda;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option2.dat");
    puVar1 = puStack_28;
    break;
  case 3:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x437ffa;
    puStack_28 = &stack0xfffffffc;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43800c;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option3.dat");
    puVar1 = puStack_28;
    break;
  case 4:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x438029;
    puStack_28 = &stack0xfffffffc;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43803b;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option4.dat");
    puVar1 = puStack_28;
    break;
  case 5:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x438058;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43806a;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option5.dat");
    puVar1 = puStack_28;
  }
  puStack_28 = puVar1;
  puStack_38 = &LAB_00438c60;
  uStack_3c = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_3c;
  puStack_34 = &stack0xfffffffc;
  FUN_0040414d((undefined4 *)&DAT_0048a770,DAT_0048a76c);
  FUN_0040458d((HANDLE *)&DAT_0048a770,(HANDLE)0x1);
  FUN_00402710();
  FUN_004041f0((HANDLE *)&DAT_0048a770,&DAT_0048c3ec,0x120,(uint *)0x0);
  FUN_00402710();
  FUN_004042b8(&DAT_0048a770);
  FUN_00402710();
  local_14 = 0;
  local_10 = 10;
  piVar5 = &DAT_0048c3ec;
  do {
    iVar4 = 0;
    iVar2 = 4;
    piVar3 = piVar5;
    do {
      iVar4 = iVar4 + *piVar3;
      piVar3 = piVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar4 != piVar5[4]) {
      local_14 = 1;
    }
    iVar4 = 0;
    iVar2 = 1;
    piVar3 = piVar5;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
        iVar4 = iVar4 + *piVar3;
        break;
      case 2:
      case 4:
        iVar4 = iVar4 - *piVar3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 != 6);
    if (iVar4 != piVar5[5]) {
      local_14 = 1;
    }
    piVar5 = piVar5 + 6;
    local_10 = local_10 + -1;
  } while (local_10 != 0);
  local_10 = 1;
  piVar5 = &DAT_0048c3ec;
  do {
    iVar4 = 0;
    iVar2 = 10;
    piVar3 = piVar5;
    do {
      iVar4 = iVar4 + *piVar3;
      piVar3 = piVar3 + 6;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    if (iVar4 != piVar5[0x3c]) {
      local_14 = 1;
    }
    iVar4 = 0;
    iVar2 = 1;
    piVar3 = piVar5;
    do {
      switch(iVar2) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 9:
      case 0xb:
        iVar4 = iVar4 + *piVar3;
        break;
      case 2:
      case 4:
      case 6:
      case 8:
      case 10:
        iVar4 = iVar4 - *piVar3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 6;
    } while (iVar2 != 0xc);
    if ((local_10 != 6) && (iVar4 != piVar5[0x42])) {
      local_14 = 1;
    }
    local_10 = local_10 + 1;
    piVar5 = piVar5 + 1;
  } while (local_10 != 7);
  if ((local_14 == 0) && (DAT_0048c508 / 100 != DAT_0048ab30)) {
    local_14 = 2;
  }
  if ((local_14 == 0) && (DAT_0048ab30 * -100 + DAT_0048c508 != -(uint)local_9)) {
    local_14 = 2;
  }
  if ((local_14 == 1) || (local_14 == 2)) {
    if (local_14 == 1) {
      FUN_0042cf78((uint *)"Ranking data is abnormal. Use a temporary Ranking.");
    }
    else if (local_14 == 2) {
      FUN_0042cf78((uint *)"Version of Ranking data is abnormal. Use a temporary Ranking.");
    }
    switch(local_9) {
    case 1:
      DAT_0048c3ec = 100;
      DAT_0048c3f0 = 500;
      DAT_0048c3f4 = 0x19;
      DAT_0048c3f8 = 0x19;
      DAT_0048c3fc = 0;
      DAT_0048c400 = 0;
      DAT_0048c404 = 0x5a;
      DAT_0048c408 = 0x1c2;
      DAT_0048c40c = 0x18;
      DAT_0048c410 = 0x18;
      DAT_0048c414 = 0;
      _DAT_0048c418 = 0;
      DAT_0048c41c = 0x50;
      DAT_0048c420 = 400;
      DAT_0048c424 = 0x17;
      DAT_0048c428 = 0x17;
      _DAT_0048c42c = 0;
      _DAT_0048c430 = 0;
      DAT_0048c434 = 0x46;
      DAT_0048c438 = 0x15e;
      DAT_0048c43c = 0x16;
      DAT_0048c440 = 0x16;
      _DAT_0048c444 = 0;
      _DAT_0048c448 = 0;
      DAT_0048c44c = 0x3c;
      DAT_0048c450 = 300;
      DAT_0048c454 = 0x15;
      DAT_0048c458 = 0x15;
      _DAT_0048c45c = 0;
      _DAT_0048c460 = 0;
      DAT_0048c464 = 0x32;
      DAT_0048c468 = 0xfa;
      DAT_0048c46c = 0x14;
      DAT_0048c470 = 0x14;
      _DAT_0048c474 = 0;
      _DAT_0048c478 = 0;
      DAT_0048c47c = 0x28;
      DAT_0048c480 = 200;
      DAT_0048c484 = 0x13;
      DAT_0048c488 = 0x13;
      _DAT_0048c48c = 0;
      _DAT_0048c490 = 0;
      DAT_0048c494 = 0x1e;
      DAT_0048c498 = 0x96;
      DAT_0048c49c = 0x12;
      DAT_0048c4a0 = 0x12;
      _DAT_0048c4a4 = 0;
      _DAT_0048c4a8 = 0;
      DAT_0048c4ac = 0x14;
      DAT_0048c4b0 = 100;
      DAT_0048c4b4 = 0x11;
      DAT_0048c4b8 = 0x11;
      _DAT_0048c4bc = 0;
      _DAT_0048c4c0 = 0;
      DAT_0048c4c4 = 10;
      DAT_0048c4c8 = 0x32;
      DAT_0048c4cc = 0x10;
      DAT_0048c4d0 = 0x10;
      _DAT_0048c4d4 = 0;
      _DAT_0048c4d8 = 0;
      DAT_0048c4dc = 0;
      DAT_0048c4e0 = 0;
      _DAT_0048c4e4 = 0;
      _DAT_0048c4e8 = 0;
      _DAT_0048c4ec = 0;
      _DAT_0048c4f0 = 0;
      DAT_0048c4f4 = 0;
      _DAT_0048c4f8 = 0;
      _DAT_0048c4fc = 0;
      _DAT_0048c500 = 0;
      _DAT_0048c504 = 0;
      DAT_0048c508 = 0;
      break;
    case 2:
      DAT_0048c3ec = 100;
      DAT_0048c3f0 = 1000;
      DAT_0048c3f4 = 0x32;
      DAT_0048c3f8 = 0x32;
      DAT_0048c3fc = 0;
      DAT_0048c400 = 0;
      DAT_0048c404 = 0x5a;
      DAT_0048c408 = 900;
      DAT_0048c40c = 0x2d;
      DAT_0048c410 = 0x2d;
      DAT_0048c414 = 0;
      _DAT_0048c418 = 0;
      DAT_0048c41c = 0x50;
      DAT_0048c420 = 800;
      DAT_0048c424 = 0x28;
      DAT_0048c428 = 0x28;
      _DAT_0048c42c = 0;
      _DAT_0048c430 = 0;
      DAT_0048c434 = 0x46;
      DAT_0048c438 = 700;
      DAT_0048c43c = 0x23;
      DAT_0048c440 = 0x23;
      _DAT_0048c444 = 0;
      _DAT_0048c448 = 0;
      DAT_0048c44c = 0x3c;
      DAT_0048c450 = 600;
      DAT_0048c454 = 0x1e;
      DAT_0048c458 = 0x1e;
      _DAT_0048c45c = 0;
      _DAT_0048c460 = 0;
      DAT_0048c464 = 0x32;
      DAT_0048c468 = 500;
      DAT_0048c46c = 0x19;
      DAT_0048c470 = 0x19;
      _DAT_0048c474 = 0;
      _DAT_0048c478 = 0;
      DAT_0048c47c = 0x28;
      DAT_0048c480 = 400;
      DAT_0048c484 = 0x14;
      DAT_0048c488 = 0x14;
      _DAT_0048c48c = 0;
      _DAT_0048c490 = 0;
      DAT_0048c494 = 0x1e;
      DAT_0048c498 = 300;
      DAT_0048c49c = 0xf;
      DAT_0048c4a0 = 0xf;
      _DAT_0048c4a4 = 0;
      _DAT_0048c4a8 = 0;
      DAT_0048c4ac = 0x14;
      DAT_0048c4b0 = 200;
      DAT_0048c4b4 = 10;
      DAT_0048c4b8 = 10;
      _DAT_0048c4bc = 0;
      _DAT_0048c4c0 = 0;
      DAT_0048c4c4 = 10;
      DAT_0048c4c8 = 100;
      DAT_0048c4cc = 5;
      DAT_0048c4d0 = 5;
      _DAT_0048c4d4 = 0;
      _DAT_0048c4d8 = 0;
      DAT_0048c4dc = 0;
      DAT_0048c4e0 = 0;
      _DAT_0048c4e4 = 0;
      _DAT_0048c4e8 = 0;
      _DAT_0048c4ec = 0;
      _DAT_0048c4f0 = 0;
      DAT_0048c4f4 = 0;
      _DAT_0048c4f8 = 0;
      _DAT_0048c4fc = 0;
      _DAT_0048c500 = 0;
      _DAT_0048c504 = 0;
      DAT_0048c508 = 0;
      break;
    case 3:
    case 5:
      DAT_0048c3ec = 100;
      DAT_0048c3f0 = 10000;
      DAT_0048c3f4 = 500;
      DAT_0048c3f8 = 500;
      DAT_0048c3fc = 0;
      DAT_0048c400 = 0;
      DAT_0048c404 = 0x5a;
      DAT_0048c408 = 9000;
      DAT_0048c40c = 0x1c2;
      DAT_0048c410 = 0x1c2;
      DAT_0048c414 = 0;
      _DAT_0048c418 = 0;
      DAT_0048c41c = 0x50;
      DAT_0048c420 = 8000;
      DAT_0048c424 = 400;
      DAT_0048c428 = 400;
      _DAT_0048c42c = 0;
      _DAT_0048c430 = 0;
      DAT_0048c434 = 0x46;
      DAT_0048c438 = 7000;
      DAT_0048c43c = 0x15e;
      DAT_0048c440 = 0x15e;
      _DAT_0048c444 = 0;
      _DAT_0048c448 = 0;
      DAT_0048c44c = 0x3c;
      DAT_0048c450 = 6000;
      DAT_0048c454 = 300;
      DAT_0048c458 = 300;
      _DAT_0048c45c = 0;
      _DAT_0048c460 = 0;
      DAT_0048c464 = 0x32;
      DAT_0048c468 = 5000;
      DAT_0048c46c = 0xfa;
      DAT_0048c470 = 0xfa;
      _DAT_0048c474 = 0;
      _DAT_0048c478 = 0;
      DAT_0048c47c = 0x28;
      DAT_0048c480 = 4000;
      DAT_0048c484 = 200;
      DAT_0048c488 = 200;
      _DAT_0048c48c = 0;
      _DAT_0048c490 = 0;
      DAT_0048c494 = 0x1e;
      DAT_0048c498 = 3000;
      DAT_0048c49c = 0x96;
      DAT_0048c4a0 = 0x96;
      _DAT_0048c4a4 = 0;
      _DAT_0048c4a8 = 0;
      DAT_0048c4ac = 0x14;
      DAT_0048c4b0 = 2000;
      DAT_0048c4b4 = 100;
      DAT_0048c4b8 = 100;
      _DAT_0048c4bc = 0;
      _DAT_0048c4c0 = 0;
      DAT_0048c4c4 = 10;
      DAT_0048c4c8 = 1000;
      DAT_0048c4cc = 0x32;
      DAT_0048c4d0 = 0x32;
      _DAT_0048c4d4 = 0;
      _DAT_0048c4d8 = 0;
      DAT_0048c4dc = 0;
      DAT_0048c4e0 = 0;
      _DAT_0048c4e4 = 0;
      _DAT_0048c4e8 = 0;
      _DAT_0048c4ec = 0;
      _DAT_0048c4f0 = 0;
      DAT_0048c4f4 = 0;
      _DAT_0048c4f8 = 0;
      _DAT_0048c4fc = 0;
      _DAT_0048c500 = 0;
      _DAT_0048c504 = 0;
      DAT_0048c508 = 0;
      break;
    case 4:
      DAT_0048c3ec = 100;
      DAT_0048c3f0 = 5000;
      DAT_0048c3f4 = 200;
      DAT_0048c3f8 = 200;
      DAT_0048c3fc = 0;
      DAT_0048c400 = 0;
      DAT_0048c404 = 0x5a;
      DAT_0048c408 = 0x1194;
      DAT_0048c40c = 0xbe;
      DAT_0048c410 = 0xbe;
      DAT_0048c414 = 0;
      _DAT_0048c418 = 0;
      DAT_0048c41c = 0x50;
      DAT_0048c420 = 4000;
      DAT_0048c424 = 0xb4;
      DAT_0048c428 = 0xb4;
      _DAT_0048c42c = 0;
      _DAT_0048c430 = 0;
      DAT_0048c434 = 0x46;
      DAT_0048c438 = 0xdac;
      DAT_0048c43c = 0xaa;
      DAT_0048c440 = 0xaa;
      _DAT_0048c444 = 0;
      _DAT_0048c448 = 0;
      DAT_0048c44c = 0x3c;
      DAT_0048c450 = 3000;
      DAT_0048c454 = 0xa0;
      DAT_0048c458 = 0xa0;
      _DAT_0048c45c = 0;
      _DAT_0048c460 = 0;
      DAT_0048c464 = 0x32;
      DAT_0048c468 = 0x9c4;
      DAT_0048c46c = 0x96;
      DAT_0048c470 = 0x96;
      _DAT_0048c474 = 0;
      _DAT_0048c478 = 0;
      DAT_0048c47c = 0x28;
      DAT_0048c480 = 2000;
      DAT_0048c484 = 0x8c;
      DAT_0048c488 = 0x8c;
      _DAT_0048c48c = 0;
      _DAT_0048c490 = 0;
      DAT_0048c494 = 0x1e;
      DAT_0048c498 = 0x5dc;
      DAT_0048c49c = 0x82;
      DAT_0048c4a0 = 0x82;
      _DAT_0048c4a4 = 0;
      _DAT_0048c4a8 = 0;
      DAT_0048c4ac = 0x14;
      DAT_0048c4b0 = 1000;
      DAT_0048c4b4 = 0x78;
      DAT_0048c4b8 = 0x78;
      _DAT_0048c4bc = 0;
      _DAT_0048c4c0 = 0;
      DAT_0048c4c4 = 10;
      DAT_0048c4c8 = 500;
      DAT_0048c4cc = 0x6e;
      DAT_0048c4d0 = 0x6e;
      _DAT_0048c4d4 = 0;
      _DAT_0048c4d8 = 0;
      DAT_0048c4dc = 0;
      DAT_0048c4e0 = 0;
      _DAT_0048c4e4 = 0;
      _DAT_0048c4e8 = 0;
      _DAT_0048c4ec = 0;
      _DAT_0048c4f0 = 0;
      DAT_0048c4f4 = 0;
      _DAT_0048c4f8 = 0;
      _DAT_0048c4fc = 0;
      _DAT_0048c500 = 0;
      _DAT_0048c504 = 0;
      DAT_0048c508 = 0;
    }
  }
  *in_FS_OFFSET = uStack_3c;
  switch(local_9) {
  case 1:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x4396b8;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x4396ca;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option11.dat");
    break;
  case 2:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x4396ea;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x4396fc;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option21.dat");
    break;
  case 3:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x43971c;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43972e;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option31.dat");
    break;
  case 4:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x43974b;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43975d;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option41.dat");
    break;
  case 5:
    piVar5 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
    puStack_34 = (undefined *)0x43977a;
    (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
    puStack_34 = (undefined *)0x43978c;
    FUN_0040369c((int *)&DAT_0048a76c,local_18,(undefined4 *)"\\option51.dat");
  }
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x4397a6;
  (**(code **)(*piVar5 + 0x50))(piVar5,DAT_0048a76c);
  puStack_34 = (undefined *)0x4397ba;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x2b8) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x4397ce;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x21c) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x4397e2;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x220) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x4397f6;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x224) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x43980a;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x228) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x43981e;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x22c) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x439832;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x230) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x439846;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x234) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x43985a;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x238) + 0x118) + 0x38))();
  puStack_34 = (undefined *)0x43986e;
  (**(code **)(**(int **)(*(int *)(local_8 + 0x23c) + 0x118) + 0x38))();
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x439887;
  (**(code **)(*piVar5 + 0xc))(piVar5,0,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x2b8) + 0x118);
  puStack_34 = (undefined *)0x4398a0;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x4398bc;
  (**(code **)(*piVar5 + 0xc))(piVar5,1,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x21c) + 0x118);
  puStack_34 = (undefined *)0x4398d5;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x4398f1;
  (**(code **)(*piVar5 + 0xc))(piVar5,2,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x220) + 0x118);
  puStack_34 = (undefined *)0x43990a;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x439926;
  (**(code **)(*piVar5 + 0xc))(piVar5,3,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x224) + 0x118);
  puStack_34 = (undefined *)0x43993f;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x43995b;
  (**(code **)(*piVar5 + 0xc))(piVar5,4,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x228) + 0x118);
  puStack_34 = (undefined *)0x439974;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x439990;
  (**(code **)(*piVar5 + 0xc))(piVar5,5,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x22c) + 0x118);
  puStack_34 = (undefined *)0x4399a9;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x4399c5;
  (**(code **)(*piVar5 + 0xc))(piVar5,6,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x230) + 0x118);
  puStack_34 = (undefined *)0x4399de;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x4399fa;
  (**(code **)(*piVar5 + 0xc))(piVar5,7,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x234) + 0x118);
  puStack_34 = (undefined *)0x439a13;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x439a2f;
  (**(code **)(*piVar5 + 0xc))(piVar5,8,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x238) + 0x118);
  puStack_34 = (undefined *)0x439a48;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 700) + 0x118);
  puStack_34 = (undefined *)0x439a64;
  (**(code **)(*piVar5 + 0xc))(piVar5,9,&local_18);
  piVar5 = *(int **)(*(int *)(local_8 + 0x23c) + 0x118);
  puStack_34 = (undefined *)0x439a7d;
  (**(code **)(*piVar5 + 0x1c))(piVar5,0,local_18);
  switch(local_9) {
  case 1:
    puStack_34 = (undefined *)0x439ab7;
    (**(code **)(**(int **)(local_8 + 0x2c0) + 0x80))();
    break;
  case 2:
    puStack_34 = (undefined *)0x439aca;
    (**(code **)(**(int **)(local_8 + 0x2c4) + 0x80))();
    break;
  case 3:
    puStack_34 = (undefined *)0x439add;
    (**(code **)(**(int **)(local_8 + 0x2c8) + 0x80))();
    break;
  case 4:
    puStack_34 = (undefined *)0x439af0;
    (**(code **)(**(int **)(local_8 + 0x2cc) + 0x80))();
    break;
  case 5:
    puStack_34 = (undefined *)0x439b03;
    (**(code **)(**(int **)(local_8 + 0x2d0) + 0x80))();
  }
  *in_FS_OFFSET = uStack_30;
  puStack_28 = &LAB_00439b20;
  puStack_2c = (undefined *)0x439b18;
  FUN_004034dc((int *)&local_18);
  return;
}

