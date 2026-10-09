/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040af1c.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0040af1c(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined2 extraout_var;
  
  uVar1 = (**(code **)(*param_1 + 8))(param_1,0,1);
  uVar2 = (**(code **)(*param_1 + 8))(param_1,0,CONCAT22(extraout_var,2));
  (**(code **)(*param_1 + 8))(param_1,uVar1,0);
  return uVar2;
}

