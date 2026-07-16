# elf-parser
 
A dependency-free ELF64 binary parser written in C++ without third-party libraries. Parsed from raw bytes against the [System V ABI ELF specification](https://refspecs.linuxfoundation.org/elf/elf.pdf).

Built as a systems programming learning project.

## Features

- ELF header parsing (`e_ident`, class, endianness, type, machine, entry point)

### Eventually: 
- Section header table with name resolution via `.shstrtab`
- Program header table (segment types, flags, virtual/physical addresses)
- Symbol table (`.symtab` / `.dynsym` with name resolution)
- Dynamic section (`.dynamic`, `DT_NEEDED` imported library names)

## Usage

```sh
cmake --build build
./build/elfparser /bin/ls
```

Requires CMake ≥ 3.15 and a C++17 compiler.
