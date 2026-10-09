/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040f7e0.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040f7e0(undefined2 param_1,int *param_2)

{
  UINT UVar1;
  undefined4 local_106;
  undefined2 local_6;
  
  local_6 = param_1;
  FUN_004034dc(param_2);
  UVar1 = MapVirtualKeyA((uint)(byte)local_6,0);
  if (UVar1 << 0x10 != 0) {
    GetKeyNameTextA(UVar1 << 0x10,(LPSTR)&local_106,0x100);
    if ((local_106._1_1_ == '\0') && ((char)local_106 != '\0')) {
      FUN_00403638(param_2,&local_106,0x100);
    }
  }
  return;
}

