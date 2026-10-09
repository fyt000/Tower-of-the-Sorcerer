/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00423451.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4
thunk_FUN_00402f4c(undefined param_1,undefined param_2,undefined param_3,PEXCEPTION_RECORD param_4,
                  PVOID param_5)

{
  int iVar1;
  LPVOID pvVar2;
  undefined4 uVar3;
  ULONG_PTR in_stack_0000000c;
  
  if ((param_4->ExceptionFlags & 6) == 0) {
    if (param_4->ExceptionCode == 0xeedface) {
LAB_00402f9a:
      param_4->ExceptionFlags = param_4->ExceptionFlags | 2;
      RtlUnwind(param_5,(PVOID)0x402fbd,param_4,(PVOID)0x0);
      pvVar2 = FUN_00403498();
      *(undefined **)pvVar2 = &stack0xffffffdc;
      iVar1 = *(int *)((int)param_5 + 4);
      *(undefined **)((int)param_5 + 4) = &LAB_00402fe9;
      FUN_00402eb4();
                    /* WARNING: Could not recover jumptable at 0x00402fe7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (*(code *)(iVar1 + 5))();
      return uVar3;
    }
    FUN_00402b6c();
    if (DAT_0048a00c != (code *)0x0) {
      iVar1 = (*DAT_0048a00c)();
      if (iVar1 != 0) {
        FUN_00402e6c(iVar1,in_stack_0000000c);
        goto LAB_00402f9a;
      }
    }
  }
  return 1;
}

