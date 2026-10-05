/* Original TSW v1.2, SHA-256 41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779.
 * Function entry 0046cb1c. Ghidra C-like inspection output.
 * Review assembly/probes before treating inferred types or arithmetic as verified.
 */


void ichicheck(int param_1)

{
  undefined4 *in_FS_OFFSET;
  undefined4 uStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  int local_c;
  int local_8;

  puStack_1c = &stack0xfffffffc;
  local_c = 0;
  puStack_20 = &LAB_004770c4;
  uStack_24 = *in_FS_OFFSET;
  *in_FS_OFFSET = &uStack_24;
  local_8 = param_1;
  if (original_hero.floor - 10U < 0x28) {
                    /* WARNING: Could not emulate address calculation at 0x0046cb56 */
                    /* WARNING: Treating indirect jump as call */
    puStack_1c = &stack0xfffffffc;
    (**(code **)(&DAT_0046cb8b +
                CONCAT31((int3)(original_hero.floor - 10U >> 8),
                         *(undefined *)(original_hero.floor + 0x46cb59)) * 4))();
    return;
  }
  if (0 < (int)event_cursor) {
    start_event_timer(param_1);
  }
  *in_FS_OFFSET = uStack_24;
  puStack_1c = &LAB_004770cb;
  puStack_20 = (undefined *)0x4770c3;
  FUN_004034dc(&local_c);
  return;
}
