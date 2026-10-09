/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0040ee88.
 * Inferred types, shared tails and runtime effects require assembly review. */

void FUN_0040ee88(undefined4 param_1,char param_2)

{
  int iVar1;
  
  if ((DAT_0048a624 != 0) && (param_2 != '\0')) {
    if (param_2 == '\x01') {
      (*DAT_0048a628)();
    }
    else {
      (*DAT_0048a628)();
      iVar1 = (*DAT_0048a630)();
      if (iVar1 != 0) {
        (*DAT_0048a634)();
        if (param_2 == '\x02') {
          (*DAT_0048a63c)();
        }
        else if (param_2 == '\x03') {
          (*DAT_0048a63c)();
        }
        else {
          (*DAT_0048a63c)();
          (*DAT_0048a634)();
          switch(param_2) {
          case '\x04':
            break;
          case '\x05':
            break;
          case '\x06':
            break;
          case '\a':
            break;
          case '\b':
          }
        }
        (*DAT_0048a640)();
      }
      (*DAT_0048a638)();
    }
  }
  return;
}

