# Original game function export

Source SHA-256: `41cb9844d9bdcf2641a34d4b152d6fbbb0455077abe0e9d7bfed77761a4d2779`. Generated with Ghidra 11.0.3.

C-like decompiler output for every detected function entering 0x440000..0x488FFF. This is an inspection corpus, not compilable game source or proof that each branch is verified. Unknown fields and helper names remain explicit. Reviewed routines and probe evidence are indexed in ../README.md.

The initial 106-function export is supplemented by ten recovered callbacks/item
helpers and 16 save routines below. The repaired `0x46CB1C` export recovers the two-level arrival
switch missed by initial analysis. The runnable readable C++ implementation is
in [C++](../../../cpp/README.md), with [fidelity evidence](../../../cpp/FIDELITY.md).
The [presentation/input supplement](../presentation/REVIEW.md) independently
recovers published method tables and serialized form events, extending this
initial detected-function export.

| Entry | Function | Source | Result |
|---|---|---|---|
| `0x004402B0` | `FUN_004402b0` | [004402b0_FUN_004402b0.c](004402b0_FUN_004402b0.c) | Exported |
| `0x00442C38` | `FUN_00442c38` | [00442c38_FUN_00442c38.c](00442c38_FUN_00442c38.c) | Exported |
| `0x00442DC8` | `kaidanwork` | [00442dc8_kaidanwork.c](00442dc8_kaidanwork.c) | Exported |
| `0x00442F80` | `FUN_00442f80` | [00442f80_FUN_00442f80.c](00442f80_FUN_00442f80.c) | Exported |
| `0x00443050` | `FUN_00443050` | [00443050_FUN_00443050.c](00443050_FUN_00443050.c) | Exported |
| `0x00443120` | `FUN_00443120` | [00443120_FUN_00443120.c](00443120_FUN_00443120.c) | Exported |
| `0x004433A4` | `FUN_004433a4` | [004433a4_FUN_004433a4.c](004433a4_FUN_004433a4.c) | Exported |
| `0x00443648` | `FUN_00443648` | [00443648_FUN_00443648.c](00443648_FUN_00443648.c) | Exported |
| `0x00443808` | `FUN_00443808` | [00443808_FUN_00443808.c](00443808_FUN_00443808.c) | Exported |
| `0x00443A34` | `FUN_00443a34` | [00443a34_FUN_00443a34.c](00443a34_FUN_00443a34.c) | Exported |
| `0x00443C08` | `FUN_00443c08` | [00443c08_FUN_00443c08.c](00443c08_FUN_00443c08.c) | Exported |
| `0x00443DE8` | `FUN_00443de8` | [00443de8_FUN_00443de8.c](00443de8_FUN_00443de8.c) | Exported |
| `0x004440E8` | `FUN_004440e8` | [004440e8_FUN_004440e8.c](004440e8_FUN_004440e8.c) | Exported |
| `0x0044439C` | `FUN_0044439c` | [0044439c_FUN_0044439c.c](0044439c_FUN_0044439c.c) | Exported |
| `0x00444490` | `handan` | [00444490_handan.c](00444490_handan.c) | Exported |
| `0x00449014` | `syounin` | [00449014_syounin.c](00449014_syounin.c) | Exported |
| `0x00449708` | `roujin` | [00449708_roujin.c](00449708_roujin.c) | Exported |
| `0x00449E18` | `FUN_00449e18` | [00449e18_FUN_00449e18.c](00449e18_FUN_00449e18.c) | Exported |
| `0x0044A480` | `taisen` | [0044a480_taisen.c](0044a480_taisen.c) | Exported |
| `0x0044B6F4` | `FUN_0044b6f4` | [0044b6f4_FUN_0044b6f4.c](0044b6f4_FUN_0044b6f4.c) | Exported |
| `0x0044B78C` | `FUN_0044b78c` | [0044b78c_FUN_0044b78c.c](0044b78c_FUN_0044b78c.c) | Exported |
| `0x0044BC0C` | `start_event_timer` | [0044bc0c_start_event_timer.c](0044bc0c_start_event_timer.c) | Exported |
| `0x0044BC34` | `toroad2` | [0044bc34_toroad2.c](0044bc34_toroad2.c) | Exported |
| `0x0044BED8` | `FUN_0044bed8` | [0044bed8_FUN_0044bed8.c](0044bed8_FUN_0044bed8.c) | Exported |
| `0x0044C04C` | `FUN_0044c04c` | [0044c04c_FUN_0044c04c.c](0044c04c_FUN_0044c04c.c) | Exported |
| `0x0044C464` | `FUN_0044c464` | [0044c464_FUN_0044c464.c](0044c464_FUN_0044c464.c) | Exported |
| `0x0044C5C4` | `mazyutu1` | [0044c5c4_mazyutu1.c](0044c5c4_mazyutu1.c) | Exported |
| `0x0044C9F0` | `FUN_0044c9f0` | [0044c9f0_FUN_0044c9f0.c](0044c9f0_FUN_0044c9f0.c) | Exported |
| `0x0044CB34` | `FUN_0044cb34` | [0044cb34_FUN_0044cb34.c](0044cb34_FUN_0044cb34.c) | Exported |
| `0x0044CCD8` | `FUN_0044ccd8` | [0044ccd8_FUN_0044ccd8.c](0044ccd8_FUN_0044ccd8.c) | Exported |
| `0x0044DA10` | `dialogue_continue` | [0044da10_dialogue_continue.c](0044da10_dialogue_continue.c) | Exported |
| `0x0044E1CC` | `accept_merchant_or_altar` | [0044e1cc_accept_merchant_or_altar.c](0044e1cc_accept_merchant_or_altar.c) | Recovered callback |
| `0x0044EAF4` | `confirm_flight` | [0044eaf4_confirm_flight.c](0044eaf4_confirm_flight.c) | Recovered callback |
| `0x0044ED1C` | `preview_flight_down` | [0044ed1c_preview_flight_down.c](0044ed1c_preview_flight_down.c) | Recovered callback |
| `0x0044ED94` | `preview_flight_up` | [0044ed94_preview_flight_up.c](0044ed94_preview_flight_up.c) | Recovered callback |
| `0x0044F0E8` | `close_wisdom` | [0044f0e8_close_wisdom.c](0044f0e8_close_wisdom.c) | Recovered callback |
| `0x0044F26C` | `FUN_0044f26c` | [0044f26c_FUN_0044f26c.c](0044f26c_FUN_0044f26c.c) | Exported |
| `0x0044FF0C` | `FUN_0044ff0c` | [0044ff0c_FUN_0044ff0c.c](0044ff0c_FUN_0044ff0c.c) | Exported |
| `0x00450064` | `FUN_00450064` | [00450064_FUN_00450064.c](00450064_FUN_00450064.c) | Exported |
| `0x00450288` | `FUN_00450288` | [00450288_FUN_00450288.c](00450288_FUN_00450288.c) | Exported |
| `0x004502D0` | `FUN_004502d0` | [004502d0_FUN_004502d0.c](004502d0_FUN_004502d0.c) | Exported |
| `0x0045031C` | `FUN_0045031c` | [0045031c_FUN_0045031c.c](0045031c_FUN_0045031c.c) | Exported |
| `0x00450360` | `FUN_00450360` | [00450360_FUN_00450360.c](00450360_FUN_00450360.c) | Exported |
| `0x004503A8` | `FUN_004503a8` | [004503a8_FUN_004503a8.c](004503a8_FUN_004503a8.c) | Exported |
| `0x00450758` | `FUN_00450758` | [00450758_FUN_00450758.c](00450758_FUN_00450758.c) | Exported |
| `0x00450880` | `FUN_00450880` | [00450880_FUN_00450880.c](00450880_FUN_00450880.c) | Exported |
| `0x00450BC5` | `use_selected_item` | [00450bc5_use_selected_item.c](00450bc5_use_selected_item.c) | Exported |
| `0x00451B98` | `mattock_wall` | [00451b98_mattock_wall.c](00451b98_mattock_wall.c) | Recovered helper |
| `0x00451C20` | `classify_neighbor` | [00451c20_classify_neighbor.c](00451c20_classify_neighbor.c) | Exported |
| `0x00451D3C` | `crystal_lava` | [00451d3c_crystal_lava.c](00451d3c_crystal_lava.c) | Recovered helper |
| `0x00451E1C` | `altar_health` | [00451e1c_altar_health.c](00451e1c_altar_health.c) | Recovered callback |
| `0x004520B4` | `altar_attack` | [004520b4_altar_attack.c](004520b4_altar_attack.c) | Recovered callback |
| `0x00452360` | `altar_defense` | [00452360_altar_defense.c](00452360_altar_defense.c) | Recovered callback |
| `0x004526C0` | `FUN_004526c0` | [004526c0_FUN_004526c0.c](004526c0_FUN_004526c0.c) | Exported |
| `0x004548A0` | `FUN_004548a0` | [004548a0_FUN_004548a0.c](004548a0_FUN_004548a0.c) | Exported |
| `0x00454A58` | `FUN_00454a58` | [00454a58_FUN_00454a58.c](00454a58_FUN_00454a58.c) | Exported |
| `0x00454C10` | `FUN_00454c10` | [00454c10_FUN_00454c10.c](00454c10_FUN_00454c10.c) | Exported |
| `0x00454DA0` | `FUN_00454da0` | [00454da0_FUN_00454da0.c](00454da0_FUN_00454da0.c) | Exported |
| `0x00454DE8` | `FUN_00454de8` | [00454de8_FUN_00454de8.c](00454de8_FUN_00454de8.c) | Exported |
| `0x00455CB8` | `initialize_cycle` | [00455cb8_initialize_cycle.c](00455cb8_initialize_cycle.c) | Exported |
| `0x00460BD8` | `FUN_00460bd8` | [00460bd8_FUN_00460bd8.c](00460bd8_FUN_00460bd8.c) | Exported |
| `0x004610C4` | `FUN_004610c4` | [004610c4_FUN_004610c4.c](004610c4_FUN_004610c4.c) | Exported |
| `0x0046171C` | `FUN_0046171c` | [0046171c_FUN_0046171c.c](0046171c_FUN_0046171c.c) | Exported |
| `0x00461944` | `FUN_00461944` | [00461944_FUN_00461944.c](00461944_FUN_00461944.c) | Exported |
| `0x004619CC` | `FUN_004619cc` | [004619cc_FUN_004619cc.c](004619cc_FUN_004619cc.c) | Exported |
| `0x00461A0C` | `FUN_00461a0c` | [00461a0c_FUN_00461a0c.c](00461a0c_FUN_00461a0c.c) | Exported |
| `0x00461EF4` | `FUN_00461ef4` | [00461ef4_FUN_00461ef4.c](00461ef4_FUN_00461ef4.c) | Exported |
| `0x00462560` | `FUN_00462560` | [00462560_FUN_00462560.c](00462560_FUN_00462560.c) | Exported |
| `0x0046397C` | `mevent` | [0046397c_mevent.c](0046397c_mevent.c) | Exported |
| `0x00464048` | `opening_capture` | [00464048_opening_capture.c](00464048_opening_capture.c) | Exported |
| `0x004653B8` | `FUN_004653b8` | [004653b8_FUN_004653b8.c](004653b8_FUN_004653b8.c) | Exported |
| `0x00465900` | `touzoku` | [00465900_touzoku.c](00465900_touzoku.c) | Exported |
| `0x004660D0` | `doorstackin` | [004660d0_doorstackin.c](004660d0_doorstackin.c) | Exported |
| `0x004664E4` | `moncheck` | [004664e4_moncheck.c](004664e4_moncheck.c) | Exported |
| `0x0046CB1C` | `ichicheck` | [0046cb1c_arrival_recovered.c](0046cb1c_arrival_recovered.c) | Recovered two-level switch; initial [incomplete export](0046cb1c_ichicheck.c) retained |
| `0x004770E0` | `FUN_004770e0` | [004770e0_FUN_004770e0.c](004770e0_FUN_004770e0.c) | Exported |
| `0x00478F0C` | `FUN_00478f0c` | [00478f0c_FUN_00478f0c.c](00478f0c_FUN_00478f0c.c) | Exported |
| `0x0047BEAC` | `doorcheck` | [0047beac_doorcheck.c](0047beac_doorcheck.c) | Exported |
| `0x0047C258` | `FUN_0047c258` | [0047c258_FUN_0047c258.c](0047c258_FUN_0047c258.c) | Exported |
| `0x0047C2BC` | `FUN_0047c2bc` | [0047c2bc_FUN_0047c2bc.c](0047c2bc_FUN_0047c2bc.c) | Exported |
| `0x0047C8F8` | `FUN_0047c8f8` | [0047c8f8_FUN_0047c8f8.c](0047c8f8_FUN_0047c8f8.c) | Exported |
| `0x0047C978` | `FUN_0047c978` | [0047c978_FUN_0047c978.c](0047c978_FUN_0047c978.c) | Exported |
| `0x0047D2D8` | `FUN_0047d2d8` | [0047d2d8_FUN_0047d2d8.c](0047d2d8_FUN_0047d2d8.c) | Exported |
| `0x0047D324` | `FUN_0047d324` | [0047d324_FUN_0047d324.c](0047d324_FUN_0047d324.c) | Exported |
| `0x0047D4A4` | `FUN_0047d4a4` | [0047d4a4_FUN_0047d4a4.c](0047d4a4_FUN_0047d4a4.c) | Exported |
| `0x0047D9D4` | `FUN_0047d9d4` | [0047d9d4_FUN_0047d9d4.c](0047d9d4_FUN_0047d9d4.c) | Exported |
| `0x0047E7D4` | `FUN_0047e7d4` | [0047e7d4_FUN_0047e7d4.c](0047e7d4_FUN_0047e7d4.c) | Exported |
| `0x0047F47C` | `FUN_0047f47c` | [0047f47c_FUN_0047f47c.c](0047f47c_FUN_0047f47c.c) | Exported |
| `0x0047F4E0` | `FUN_0047f4e0` | [0047f4e0_FUN_0047f4e0.c](0047f4e0_FUN_0047f4e0.c) | Exported |
| `0x0047F544` | `FUN_0047f544` | [0047f544_FUN_0047f544.c](0047f544_FUN_0047f544.c) | Exported |
| `0x0047F5A8` | `FUN_0047f5a8` | [0047f5a8_FUN_0047f5a8.c](0047f5a8_FUN_0047f5a8.c) | Exported |
| `0x0047F7D4` | `FUN_0047f7d4` | [0047f7d4_FUN_0047f7d4.c](0047f7d4_FUN_0047f7d4.c) | Exported |
| `0x0048028C` | `FUN_0048028c` | [0048028c_FUN_0048028c.c](0048028c_FUN_0048028c.c) | Exported |
| `0x004802FC` | `FUN_004802fc` | [004802fc_FUN_004802fc.c](004802fc_FUN_004802fc.c) | Exported |
| `0x00480340` | `FUN_00480340` | [00480340_FUN_00480340.c](00480340_FUN_00480340.c) | Exported |
| `0x00480384` | `FUN_00480384` | [00480384_FUN_00480384.c](00480384_FUN_00480384.c) | Exported |
| `0x00480A90` | `FUN_00480a90` | [00480a90_FUN_00480a90.c](00480a90_FUN_00480a90.c) | Exported |
| `0x00480EE0` | `FUN_00480ee0` | [00480ee0_FUN_00480ee0.c](00480ee0_FUN_00480ee0.c) | Exported |
| `0x00480F60` | `FUN_00480f60` | [00480f60_FUN_00480f60.c](00480f60_FUN_00480f60.c) | Exported |
| `0x0048198C` | `FUN_0048198c` | [0048198c_FUN_0048198c.c](0048198c_FUN_0048198c.c) | Exported |
| `0x00481E80` | `FUN_00481e80` | [00481e80_FUN_00481e80.c](00481e80_FUN_00481e80.c) | Exported |
| `0x0048201C` | `FUN_0048201c` | [0048201c_FUN_0048201c.c](0048201c_FUN_0048201c.c) | Exported |
| `0x00482128` | `FUN_00482128` | [00482128_FUN_00482128.c](00482128_FUN_00482128.c) | Exported |
| `0x00482234` | `FUN_00482234` | [00482234_FUN_00482234.c](00482234_FUN_00482234.c) | Exported |
| `0x00482340` | `FUN_00482340` | [00482340_FUN_00482340.c](00482340_FUN_00482340.c) | Exported |
| `0x0048244C` | `FUN_0048244c` | [0048244c_FUN_0048244c.c](0048244c_FUN_0048244c.c) | Exported |
| `0x00482558` | `FUN_00482558` | [00482558_FUN_00482558.c](00482558_FUN_00482558.c) | Exported |
| `0x00482664` | `FUN_00482664` | [00482664_FUN_00482664.c](00482664_FUN_00482664.c) | Exported |
| `0x00482770` | `FUN_00482770` | [00482770_FUN_00482770.c](00482770_FUN_00482770.c) | Exported |
| `0x0048287C` | `FUN_0048287c` | [0048287c_FUN_0048287c.c](0048287c_FUN_0048287c.c) | Exported |
| `0x00482988` | `FUN_00482988` | [00482988_FUN_00482988.c](00482988_FUN_00482988.c) | Exported |
| `0x00482E60` | `FUN_00482e60` | [00482e60_FUN_00482e60.c](00482e60_FUN_00482e60.c) | Exported |
| `0x00484CAC` | `FUN_00484cac` | [00484cac_FUN_00484cac.c](00484cac_FUN_00484cac.c) | Exported |
| `0x00484DE8` | `FUN_00484de8` | [00484de8_FUN_00484de8.c](00484de8_FUN_00484de8.c) | Exported |
| `0x00484F48` | `FUN_00484f48` | [00484f48_FUN_00484f48.c](00484f48_FUN_00484f48.c) | Exported |
| `0x00488D50` | `entry` | [00488d50_entry.c](00488d50_entry.c) | Exported |
| `0x0047DB94` | `load_slot_2` | [0047db94_load_slot_2.c](0047db94_load_slot_2.c) | Recovered save routine |
| `0x0047DD54` | `load_slot_3` | [0047dd54_load_slot_3.c](0047dd54_load_slot_3.c) | Recovered save routine |
| `0x0047DF14` | `load_slot_4` | [0047df14_load_slot_4.c](0047df14_load_slot_4.c) | Recovered save routine |
| `0x0047E0D4` | `load_slot_5` | [0047e0d4_load_slot_5.c](0047e0d4_load_slot_5.c) | Recovered save routine |
| `0x0047E294` | `load_slot_6` | [0047e294_load_slot_6.c](0047e294_load_slot_6.c) | Recovered save routine |
| `0x0047E454` | `load_slot_7` | [0047e454_load_slot_7.c](0047e454_load_slot_7.c) | Recovered save routine |
| `0x0047E614` | `load_slot_8` | [0047e614_load_slot_8.c](0047e614_load_slot_8.c) | Recovered save routine |
| `0x0047EADC` | `write_original_save` | [0047eadc_write_original_save.c](0047eadc_write_original_save.c) | Recovered save routine |
| `0x0047ECC4` | `save_slot_1` | [0047ecc4_save_slot_1.c](0047ecc4_save_slot_1.c) | Recovered save routine |
| `0x0047EDB8` | `save_slot_2` | [0047edb8_save_slot_2.c](0047edb8_save_slot_2.c) | Recovered save routine |
| `0x0047EEAC` | `save_slot_3` | [0047eeac_save_slot_3.c](0047eeac_save_slot_3.c) | Recovered save routine |
| `0x0047EFA0` | `save_slot_4` | [0047efa0_save_slot_4.c](0047efa0_save_slot_4.c) | Recovered save routine |
| `0x0047F094` | `save_slot_5` | [0047f094_save_slot_5.c](0047f094_save_slot_5.c) | Recovered save routine |
| `0x0047F188` | `save_slot_6` | [0047f188_save_slot_6.c](0047f188_save_slot_6.c) | Recovered save routine |
| `0x0047F27C` | `save_slot_7` | [0047f27c_save_slot_7.c](0047f27c_save_slot_7.c) | Recovered save routine |
| `0x0047F370` | `save_slot_8` | [0047f370_save_slot_8.c](0047f370_save_slot_8.c) | Recovered save routine |

Exported 106 detected functions; failed 0.

Supplement: ten recovered callbacks/helpers; repaired arrival export. Recovery
scripts are `tools/ghidra/RecoverCallbacks.java` and `RecoverArrival.java`.

Save supplement: the shared writer, eight save callbacks and seven load
callbacks were recovered by `tools/ghidra/RecoverSaves.java`. The shared
loader `0x47E7D4` was already exported. `baseline/tools/verify_saves.py`
checks original writer bytes, checksum acceptance and Zeno reconstruction.
