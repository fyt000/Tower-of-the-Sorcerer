/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040e318.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040e318(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined uVar1;
  undefined uVar2;
  
  if (param_3[2] != 0) {
    uVar1 = *(undefined *)*param_3;
    uVar2 = SUB41(param_3,0);
    switch(uVar1) {
    case 1:
    case 2:
    case 3:
    case 6:
      FUN_0040dc78(uVar1,(undefined)param_2,uVar2,&stack0xfffffffc);
      break;
    case 4:
      FUN_0040dda8(uVar1,(undefined)param_2,uVar2,&stack0xfffffffc);
      break;
    case 5:
    case 10:
      FUN_0040de7c(uVar1,(undefined)param_2,uVar2,&stack0xfffffffc);
      break;
    case 7:
      FUN_0040dfdc(uVar1,(undefined)param_2,uVar2,&stack0xfffffffc);
      break;
    case 8:
      FUN_0040e260(uVar1,(undefined)param_2,uVar2,&stack0xfffffffc);
    }
  }
  return;
}

