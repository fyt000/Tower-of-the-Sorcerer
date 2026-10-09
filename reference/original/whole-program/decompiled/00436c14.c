/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00436c14.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00436c14(int param_1,undefined param_2)

{
  int *piVar1;
  int iVar2;
  undefined *puVar3;
  char cVar4;
  char cVar5;
  undefined4 *puVar6;
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  uint *local_10;
  undefined4 *local_c;
  undefined local_5;
  
  puStack_20 = &stack0xfffffffc;
  local_10 = (uint *)0x0;
  puStack_24 = &LAB_00437589;
  uStack_28 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_28;
  puVar3 = &stack0xfffffffc;
  local_5 = param_2;
  switch(param_2) {
  case 1:
    puStack_20 = &stack0xfffffffc;
    FUN_00437f2c(param_1,1);
    puVar3 = puStack_20;
    break;
  case 2:
    puStack_20 = &stack0xfffffffc;
    FUN_00437f2c(param_1,2);
    puVar3 = puStack_20;
    break;
  case 3:
    puStack_20 = &stack0xfffffffc;
    FUN_00437f2c(param_1,3);
    puVar3 = puStack_20;
    break;
  case 4:
    puStack_20 = &stack0xfffffffc;
    FUN_00437f2c(param_1,4);
    puVar3 = puStack_20;
    break;
  case 5:
    FUN_00437f2c(param_1,5);
    puVar3 = puStack_20;
  }
  puStack_20 = puVar3;
  if (0 < DAT_0048aa14) {
    FUN_004034dc(&DAT_0048a76c);
    cVar4 = FUN_0042cf9c((uint *)"Input your name",(uint *)"Please input within 18 words",
                         (uint **)&DAT_0048a76c);
    if (cVar4 == '\x01') {
      if ((DAT_0048aa14 < 10) && (DAT_0048a76c != 0)) {
        (**(code **)(**(int **)(*(int *)(param_1 + 0x23c) + 0x118) + 0x38))();
        piVar1 = *(int **)(*(int *)(param_1 + 0x238) + 0x118);
        (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
        piVar1 = *(int **)(*(int *)(param_1 + 0x23c) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
        if (DAT_0048aa14 < 9) {
          (**(code **)(**(int **)(*(int *)(param_1 + 0x238) + 0x118) + 0x38))();
          piVar1 = *(int **)(*(int *)(param_1 + 0x234) + 0x118);
          (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
          piVar1 = *(int **)(*(int *)(param_1 + 0x238) + 0x118);
          (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
          if (DAT_0048aa14 < 8) {
            (**(code **)(**(int **)(*(int *)(param_1 + 0x234) + 0x118) + 0x38))();
            piVar1 = *(int **)(*(int *)(param_1 + 0x230) + 0x118);
            (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
            piVar1 = *(int **)(*(int *)(param_1 + 0x234) + 0x118);
            (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
            if (DAT_0048aa14 < 7) {
              (**(code **)(**(int **)(*(int *)(param_1 + 0x230) + 0x118) + 0x38))();
              piVar1 = *(int **)(*(int *)(param_1 + 0x22c) + 0x118);
              (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
              piVar1 = *(int **)(*(int *)(param_1 + 0x230) + 0x118);
              (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
              if (DAT_0048aa14 < 6) {
                (**(code **)(**(int **)(*(int *)(param_1 + 0x22c) + 0x118) + 0x38))();
                piVar1 = *(int **)(*(int *)(param_1 + 0x228) + 0x118);
                (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
                piVar1 = *(int **)(*(int *)(param_1 + 0x22c) + 0x118);
                (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
                if (DAT_0048aa14 < 5) {
                  (**(code **)(**(int **)(*(int *)(param_1 + 0x228) + 0x118) + 0x38))();
                  piVar1 = *(int **)(*(int *)(param_1 + 0x224) + 0x118);
                  (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
                  piVar1 = *(int **)(*(int *)(param_1 + 0x228) + 0x118);
                  (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
                  if (DAT_0048aa14 < 4) {
                    (**(code **)(**(int **)(*(int *)(param_1 + 0x224) + 0x118) + 0x38))();
                    piVar1 = *(int **)(*(int *)(param_1 + 0x220) + 0x118);
                    (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
                    piVar1 = *(int **)(*(int *)(param_1 + 0x224) + 0x118);
                    (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
                    if (DAT_0048aa14 < 3) {
                      (**(code **)(**(int **)(*(int *)(param_1 + 0x220) + 0x118) + 0x38))();
                      piVar1 = *(int **)(*(int *)(param_1 + 0x21c) + 0x118);
                      (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
                      piVar1 = *(int **)(*(int *)(param_1 + 0x220) + 0x118);
                      (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
                      if (DAT_0048aa14 < 2) {
                        (**(code **)(**(int **)(*(int *)(param_1 + 0x21c) + 0x118) + 0x38))();
                        piVar1 = *(int **)(*(int *)(param_1 + 0x2b8) + 0x118);
                        (**(code **)(*piVar1 + 0xc))(piVar1,0,&local_10);
                        piVar1 = *(int **)(*(int *)(param_1 + 0x21c) + 0x118);
                        (**(code **)(*piVar1 + 0x1c))(piVar1,0,local_10);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (DAT_0048a76c == 0) {
        DAT_0048aa14 = 0;
      }
      switch(DAT_0048aa14) {
      case 1:
        piVar1 = *(int **)(*(int *)(param_1 + 0x2b8) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 2:
        piVar1 = *(int **)(*(int *)(param_1 + 0x21c) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 3:
        piVar1 = *(int **)(*(int *)(param_1 + 0x220) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 4:
        piVar1 = *(int **)(*(int *)(param_1 + 0x224) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 5:
        piVar1 = *(int **)(*(int *)(param_1 + 0x228) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 6:
        piVar1 = *(int **)(*(int *)(param_1 + 0x22c) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 7:
        piVar1 = *(int **)(*(int *)(param_1 + 0x230) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 8:
        piVar1 = *(int **)(*(int *)(param_1 + 0x234) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 9:
        piVar1 = *(int **)(*(int *)(param_1 + 0x238) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
        break;
      case 10:
        piVar1 = *(int **)(*(int *)(param_1 + 0x23c) + 0x118);
        (**(code **)(*piVar1 + 0x1c))(piVar1,0,DAT_0048a76c);
      }
      if (0 < DAT_0048aa14) {
        if ((DAT_0048aa14 < 10) && ((byte)DAT_0048aa14 < 10)) {
          cVar4 = (byte)DAT_0048aa14 - 10;
          local_c = &DAT_0048c4ac;
          do {
            cVar5 = '\x04';
            puVar6 = local_c;
            do {
              puVar6[6] = *puVar6;
              puVar6 = puVar6 + 1;
              cVar5 = cVar5 + -1;
            } while (cVar5 != '\0');
            local_c = local_c + -6;
            cVar4 = cVar4 + '\x01';
          } while (cVar4 != '\0');
        }
        iVar2 = DAT_0048aa14;
        *(undefined4 *)(&DAT_0048c3d4 + DAT_0048aa14 * 0x18) = DAT_0048aa10;
        *(undefined4 *)(&DAT_0048c3d8 + iVar2 * 0x18) = DAT_0048a8bc;
        *(undefined4 *)(&DAT_0048c3dc + iVar2 * 0x18) = DAT_0048a8c0;
        *(undefined4 *)(&DAT_0048c3e0 + iVar2 * 0x18) = DAT_0048a8c4;
      }
    }
  }
  FUN_00405b6c(DAT_0048c3ec,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x1f0),local_10);
  FUN_00405b6c(DAT_0048c404,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 500),local_10);
  FUN_00405b6c(DAT_0048c41c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x1f8),local_10);
  FUN_00405b6c(DAT_0048c434,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x1fc),local_10);
  FUN_00405b6c(DAT_0048c44c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x200),local_10);
  FUN_00405b6c(DAT_0048c464,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x204),local_10);
  FUN_00405b6c(DAT_0048c47c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x208),local_10);
  FUN_00405b6c(DAT_0048c494,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x20c),local_10);
  FUN_00405b6c(DAT_0048c4ac,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x210),local_10);
  FUN_00405b6c(DAT_0048c4c4,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x214),local_10);
  FUN_00405b6c(DAT_0048c3f0,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x240),local_10);
  FUN_00405b6c(DAT_0048c408,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x244),local_10);
  FUN_00405b6c(DAT_0048c420,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x248),local_10);
  FUN_00405b6c(DAT_0048c438,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x24c),local_10);
  FUN_00405b6c(DAT_0048c450,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x250),local_10);
  FUN_00405b6c(DAT_0048c468,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x254),local_10);
  FUN_00405b6c(DAT_0048c480,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 600),local_10);
  FUN_00405b6c(DAT_0048c498,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x25c),local_10);
  FUN_00405b6c(DAT_0048c4b0,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x260),local_10);
  FUN_00405b6c(DAT_0048c4c8,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x264),local_10);
  FUN_00405b6c(DAT_0048c3f4,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x268),local_10);
  FUN_00405b6c(DAT_0048c40c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x26c),local_10);
  FUN_00405b6c(DAT_0048c424,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x270),local_10);
  FUN_00405b6c(DAT_0048c43c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x274),local_10);
  FUN_00405b6c(DAT_0048c454,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x278),local_10);
  FUN_00405b6c(DAT_0048c46c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x27c),local_10);
  FUN_00405b6c(DAT_0048c484,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x280),local_10);
  FUN_00405b6c(DAT_0048c49c,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x284),local_10);
  FUN_00405b6c(DAT_0048c4b4,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x288),local_10);
  FUN_00405b6c(DAT_0048c4cc,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x28c),local_10);
  FUN_00405b6c(DAT_0048c3f8,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x290),local_10);
  FUN_00405b6c(DAT_0048c410,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x294),local_10);
  FUN_00405b6c(DAT_0048c428,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x298),local_10);
  FUN_00405b6c(DAT_0048c440,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x29c),local_10);
  FUN_00405b6c(DAT_0048c458,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2a0),local_10);
  FUN_00405b6c(DAT_0048c470,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2a4),local_10);
  FUN_00405b6c(DAT_0048c488,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2a8),local_10);
  FUN_00405b6c(DAT_0048c4a0,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2ac),local_10);
  FUN_00405b6c(DAT_0048c4b8,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2b0),local_10);
  FUN_00405b6c(DAT_0048c4d0,(int *)&local_10);
  FUN_004135d4(*(int **)(param_1 + 0x2b4),local_10);
  if (0 < DAT_0048aa14) {
    FUN_00439ce0(param_1);
  }
  *in_FS_OFFSET = uStack_28;
  puStack_20 = &LAB_00437590;
  puStack_24 = (undefined *)0x437588;
  FUN_004034dc((int *)&local_10);
  return;
}

