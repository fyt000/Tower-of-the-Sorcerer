/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 00454c10. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


uint FUN_00454c10(void)

{
  uint uVar1;

  door_opened = 0;
  uVar1 = DAT_0048c5a8;
  switch(DAT_0048c5a8) {
  case 0:
    goto switchD_00454c2a_caseD_0;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
    door_opened = 0;
    return 0;
  case 0xd:
    door_opened = 0x93;
    return DAT_0048c5a8;
  case 0xe:
    door_opened = 0x93;
    return DAT_0048c5a8;
  case 0xf:
    door_opened = 0;
    return 0;
  case 0x10:
    door_opened = 2;
    return DAT_0048c5a8;
  case 0x11:
  case 0x12:
    door_opened = 0;
    return 0;
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
    door_opened = 1;
    return DAT_0048c5a8;
  default:
    if ((int)DAT_0048c5a8 < 0x6a) {
      if (DAT_0048c5a8 - 0x1b < 2) {
        if (original_hero._464_4_ != 1) {
          door_opened = 1;
          return DAT_0048c5a8 - 0x1d;
        }
        uVar1 = 0;
        door_opened = 0;
      }
      else {
        if (DAT_0048c5a8 - 0x1d < 0x20) {
          door_opened = 0;
          return 0;
        }
        if (DAT_0048c5a8 - 0x3d < 0x24) {
          door_opened = 1;
          return DAT_0048c5a8 - 0x61;
        }
        uVar1 = DAT_0048c5a8 - 0x6a;
        if (DAT_0048c5a8 - 0x61 < 9) {
          door_opened = 9;
          return uVar1;
        }
      }
    }
    else {
      if (DAT_0048c5a8 - 0x6a < 9) {
        door_opened = 0;
        return 0;
      }
      if (DAT_0048c5a8 - 0x73 < 9) {
        door_opened = 9;
        return DAT_0048c5a8 - 0x7c;
      }
      if (DAT_0048c5a8 - 0x7c < 9) {
        door_opened = 0;
        return 0;
      }
      uVar1 = DAT_0048c5a8 - 0x9e;
      if (DAT_0048c5a8 - 0x85 < 0x19) {
        door_opened = 1;
      }
    }
switchD_00454c2a_caseD_0:
    return uVar1;
  }
}
