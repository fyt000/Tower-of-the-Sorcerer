/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0041c468.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0041c468(int param_1,int *param_2)

{
  undefined4 local_14c [16];
  undefined4 local_10c [64];
  
  FUN_00402b7c(**(int **)(param_1 + 4),(byte *)local_10c);
  FUN_00402918(local_14c,local_10c,0x3f);
  (**(code **)(*param_2 + 4))(param_2,local_14c,(byte)local_14c[0] + 1);
  (**(code **)(**(int **)(param_1 + 4) + 0x30))(*(int **)(param_1 + 4),param_2);
  return;
}

