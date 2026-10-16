# Runtime supplement

The [method index](decompiled/INDEX.md) contains 237 initial exports.
`RecoverUiRuntime.java` adds these three, bringing the corpus to 240
C-like/assembly pairs. Exports make exclusions inspectable; they do not
emulate Windows callbacks, allocation, drawing, or dialog delivery.

| Entry | Behavior | Source | Assembly |
|---|---|---|---|
| `0x41C160` | Picture cloning, assignment, change notification | [C](decompiled/0041c160_runtime_41c160.c) | [x86](decompiled/0041c160_runtime_41c160.asm) |
| `0x42CEC8` | Modal dialog wrapper; `RET 4` | [C](decompiled/0042cec8_runtime_42cec8.c) | [x86](decompiled/0042cec8_runtime_42cec8.asm) |
| `0x42C454` | Timer enable byte `+0x20` and registration | [C](decompiled/0042c454_runtime_42c454.c) | [x86](decompiled/0042c454_runtime_42c454.asm) |

See [REVIEW.md](REVIEW.md) for effects, sequences, and remaining limits.
