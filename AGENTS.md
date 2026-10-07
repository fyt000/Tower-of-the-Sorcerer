After the C++ build passes, run clang-format with cpp/.clang-format on all C++ sources, headers and tests.
From cpp/: rg --files src include tests -g '*.cpp' -g '*.hpp' | ForEach-Object { clang-format -i --style=file $_ }
