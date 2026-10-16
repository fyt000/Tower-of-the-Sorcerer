After the C++ build passes, run clang-format with cpp/.clang-format on all C++ sources, headers and tests.
From cpp/: rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { clang-format -i --style=file $_ }

Only run audio tests when the current changes touch audio code, audio assets, audio dependencies, or audio-related configuration. Otherwise, skip audio tests, including during broader test runs; use `ctest -LE audio` to exclude the audio-labeled CTest checks.
