/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00421868.
 * Inferred types, shared tails and runtime effects require assembly review. */

void root_00421868(int *param_1,int *param_2,undefined param_3)

{
  undefined uVar1;
  int iVar2;
  HBRUSH hbr;
  RECT RStack_1c;
  int *piStack_c;
  int *piStack_8;
  
  piStack_c = param_2;
  piStack_8 = param_1;
  if (*param_2 == 0x14) {
    hbr = (HBRUSH)FUN_0041a188(param_1[0x2f]);
    (**(code **)(*piStack_8 + 0x2c))(piStack_8,&RStack_1c);
    FillRect((HDC)piStack_c[1],&RStack_1c,hbr);
    piStack_c[3] = 1;
  }
  else {
    iVar2 = *param_2 + -0x84;
    uVar1 = (undefined)iVar2;
    if (iVar2 == 0) {
      FUN_0042181c(uVar1,(char)param_2,param_3,&stack0xfffffffc);
      if (piStack_c[3] == 1) {
        piStack_c[3] = -1;
      }
    }
    else {
      FUN_0042181c(uVar1,(char)param_2,param_3,&stack0xfffffffc);
    }
  }
  return;
}

