/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x004031a8.
 * Inferred types, shared tails and runtime effects require assembly review. */

PVOID root_004031a8(void)

{
  PVOID pvVar1;
  undefined4 *in_FS_OFFSET;
  PEXCEPTION_RECORD in_stack_00000004;
  PVOID in_stack_00000008;
  
  FUN_00402b6c();
  if ((in_stack_00000004->ExceptionFlags & 6) == 0) {
    in_stack_00000004->ExceptionFlags = in_stack_00000004->ExceptionFlags | 2;
    RtlUnwind(in_stack_00000008,(PVOID)0x4031d0,in_stack_00000004,(PVOID)0x0);
    if (in_stack_00000004->ExceptionCode == 0xeedface) {
      pvVar1 = (PVOID)in_stack_00000004->ExceptionInformation[0];
    }
    else {
      pvVar1 = in_stack_00000004->ExceptionAddress;
    }
    *in_FS_OFFSET = *(undefined4 *)*in_FS_OFFSET;
    return pvVar1;
  }
  return (PVOID)0x1;
}

