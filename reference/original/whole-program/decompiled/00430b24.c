/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00430b24.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00430b24(int *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 extraout_EDX;
  undefined4 uStack_c;
  
  uStack_c = CONCAT31((int3)((uint)param_3 >> 8),1);
  FUN_00402cdc(param_1,CONCAT31((int3)((uint)param_2 >> 8),*(undefined *)((int)param_1 + 0x19e)),
               &uStack_c);
  if ((char)uStack_c != '\0') {
    switch(*(undefined *)((int)param_1 + 0x19e)) {
    case 0:
      FUN_00431250(param_1,extraout_EDX);
      break;
    case 1:
      func_0x004314cc(param_1);
      break;
    case 2:
      func_0x00431438(param_1);
      break;
    case 3:
      FUN_00431660(param_1,extraout_EDX);
      break;
    case 4:
      func_0x004317f0(param_1);
      break;
    case 5:
      func_0x004319ac(param_1);
      break;
    case 6:
      func_0x00431a88(param_1);
      break;
    case 7:
      func_0x00431360(param_1);
      break;
    case 8:
      func_0x00431b4c(param_1);
    }
    root_00430be4(param_1,*(undefined *)((int)param_1 + 0x19e));
  }
  return;
}

