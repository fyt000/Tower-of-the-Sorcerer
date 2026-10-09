/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x00402768.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_00402768(char param_1,int *param_2)

{
  char local_214;
  undefined local_213;
  undefined local_212;
  undefined4 local_210 [65];
  CHAR local_10c [260];
  
  if (param_1 != '\0') {
    local_214 = param_1 + '@';
    local_213 = 0x3a;
    local_212 = 0;
    GetCurrentDirectoryA(0x104,local_10c);
    SetCurrentDirectoryA(&local_214);
  }
  GetCurrentDirectoryA(0x104,(LPSTR)local_210);
  if (param_1 != '\0') {
    SetCurrentDirectoryA(local_10c);
  }
  FUN_00403638(param_2,local_210,0x104);
  return;
}

