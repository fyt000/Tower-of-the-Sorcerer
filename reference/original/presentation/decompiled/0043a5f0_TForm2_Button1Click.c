/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; published entry 0043a5f0.
 * Inferred types and shared tails require assembly review. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TForm2_Button1Click(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined4 *puStack_c;
  int iStack_8;
  
  puStack_1c = &stack0xfffffffc;
  puStack_c = (undefined4 *)0x0;
  puStack_20 = &UNK_0043bbba;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  iStack_8 = param_1;
  iVar1 = FUN_0042cec8((uint *)"Initialize this data. Is it true?",
                       CONCAT31((int3)((uint)param_2 >> 8),2),_DAT_0043bbc8,0);
  if (iVar1 == 6) {
    DAT_0048aa18 = _DAT_0048a768;
    switch(_DAT_0048a768) {
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
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x21c) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x220) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x224) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x228) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x22c) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x230) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x234) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x238) + 0x118) + 0x38))();
    (**(code **)(**(int **)(*(int *)(iStack_8 + 0x23c) + 0x118) + 0x38))();
    switch(_DAT_0048a768) {
    case 1:
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Skeleton A");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x21c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Priest");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x220) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Skeleton B");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x224) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Gate-Keeper C");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x228) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Skeleton C");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x22c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,&DAT_0043bc64);
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x230) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Red Slime");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x234) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Green Slime");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x238) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Iron Sword");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x23c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Iron Shield");
      break;
    case 2:
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Vampire");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x21c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Superion Priest");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x220) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Zombie Knight");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x224) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Gate-Keeper B");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x228) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,&DAT_0043bd18);
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x22c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Big Octopus");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x230) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Zombie");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x234) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Big Bat");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x238) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Big Slime");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x23c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Blue Crystal");
      break;
    case 3:
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Magic Master");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x21c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Thief");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x220) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Fairy");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x224) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Merchant");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x228) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Princess");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x22c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Old Man");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x230) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Brave Man");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x234) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Mattock");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x238) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Cross");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x23c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Lucky Gold");
      break;
    case 4:
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Golden Knight");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x21c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Knight");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x220) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Fancer");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x224) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Soldier");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x228) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Ghost Soldier");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x22c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Dragon");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x230) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Swordsman");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x234) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Slime Man");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x238) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Sword of Knight");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x23c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Shield of Knight");
      break;
    case 5:
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x2b8) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,&DAT_0043bf0c);
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x21c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Magician A");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x220) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Black Knight");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x224) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Magic Sergeant");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x228) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Gate-Keeper A");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x22c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Bloodsucker Bat");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x230) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Magician B");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x234) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"King Slime");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x238) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Holy Sword");
      piVar3 = *(int **)(*(int *)(iStack_8 + 0x23c) + 0x118);
      (**(code **)(*piVar3 + 0x1c))(piVar3,0,"Holy Shield");
    }
    iVar1 = 10;
    piVar3 = &DAT_0048c3fc;
    do {
      *piVar3 = 0;
      iVar2 = 4;
      piVar4 = piVar3 + -4;
      do {
        *piVar3 = *piVar3 + *piVar4;
        piVar4 = piVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      piVar3[1] = 0;
      iVar2 = 1;
      piVar4 = piVar3 + -4;
      do {
        switch(iVar2) {
        case 1:
        case 3:
        case 5:
          piVar3[1] = piVar3[1] + *piVar4;
          break;
        case 2:
        case 4:
          piVar3[1] = piVar3[1] - *piVar4;
        }
        iVar2 = iVar2 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar2 != 6);
      piVar3 = piVar3 + 6;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    iVar1 = 6;
    piVar3 = &DAT_0048c4dc;
    do {
      *piVar3 = 0;
      iVar2 = 10;
      piVar4 = piVar3 + -0x3c;
      do {
        *piVar3 = *piVar3 + *piVar4;
        piVar4 = piVar4 + 6;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      piVar3[6] = 0;
      iVar2 = 1;
      piVar4 = piVar3 + -0x3c;
      do {
        switch(iVar2) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        case 0xb:
          piVar3[6] = piVar3[6] + *piVar4;
          break;
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
          piVar3[6] = piVar3[6] - *piVar4;
        }
        iVar2 = iVar2 + 1;
        piVar4 = piVar4 + 6;
      } while (iVar2 != 0xc);
      piVar3 = piVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    DAT_0048c508 = DAT_0048ab30 * 100 - DAT_0048aa18;
    switch(_DAT_0048a768) {
    case 1:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option1.dat");
      break;
    case 2:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option2.dat");
      break;
    case 3:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option3.dat");
      break;
    case 4:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option4.dat");
      break;
    case 5:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option5.dat");
    }
    FUN_0040414d((undefined4 *)&DAT_0048a770,DAT_0048a76c);
    FUN_004045a4((HANDLE *)&DAT_0048a770,(HANDLE)0x1);
    FUN_00402710();
    FUN_00404254((HANDLE *)&DAT_0048a770,&DAT_0048c3ec,0x120,(uint *)0x0);
    FUN_00402710();
    FUN_004042b8(&DAT_0048a770);
    FUN_00402710();
    switch(_DAT_0048a768) {
    case 1:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option11.dat");
      break;
    case 2:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option21.dat");
      break;
    case 3:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option31.dat");
      break;
    case 4:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option41.dat");
      break;
    case 5:
      piVar3 = *(int **)(*(int *)(DAT_0048c510 + 0x444) + 0x118);
      (**(code **)(*piVar3 + 0xc))(piVar3,0,&puStack_c);
      FUN_0040369c((int *)&DAT_0048a76c,puStack_c,(undefined4 *)"\\option51.dat");
    }
    (**(code **)(**(int **)(*(int *)(iStack_8 + 700) + 0x118) + 0x38))();
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x2b8) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x21c) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x220) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x224) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x228) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x22c) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x230) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x234) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x238) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x34))(piVar3,*(undefined4 *)(*(int *)(iStack_8 + 0x23c) + 0x118));
    piVar3 = *(int **)(*(int *)(iStack_8 + 700) + 0x118);
    (**(code **)(*piVar3 + 0x5c))(piVar3,DAT_0048a76c);
    FUN_00436c14(iStack_8,DAT_0048a768);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_0043bbc1;
  puStack_20 = (undefined *)0x43bbb9;
  FUN_004034dc((int *)&puStack_c);
  return;
}

