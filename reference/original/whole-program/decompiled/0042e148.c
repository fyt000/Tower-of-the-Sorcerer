/* Original SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779; entry 0x0042e148.
 * Inferred types, shared tails and runtime effects require assembly review. */

undefined4 FUN_0042e148(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined3 uVar4;
  undefined4 auStack_3c [6];
  undefined local_23;
  
  uVar2 = FUN_0042de88(param_1,auStack_3c);
  uVar3 = CONCAT31((int3)((uint)uVar2 >> 8),local_23) & 0xffffff03;
  cVar1 = (char)uVar3;
  uVar4 = (undefined3)(uVar3 >> 8);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else if (cVar1 == '\x01') {
    uVar2 = CONCAT31(uVar4,2);
  }
  else if (cVar1 == '\x02') {
    uVar2 = CONCAT31(uVar4,1);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

