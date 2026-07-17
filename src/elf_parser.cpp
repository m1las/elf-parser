#include "../include/elfparser/elf_parser.hpp"
#include "../include/utils/byte_iterator.hpp"
#include <fstream>

bool ElfParser::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) return fail("Could not open file: " + path);

    std::streamsize size = file.tellg();
    if (size < 4) return fail("File too small to be ELF");

    file.seekg(0, std::ios::beg);
    buffer_.resize(static_cast<size_t>(size));

    if (!file.read(reinterpret_cast<char*>(buffer_.data()), size))
        return fail("Failed to read file: " + path);

    if (buffer_[0] != 0x7f || buffer_[1] != 'E' ||
        buffer_[2] != 'L'  || buffer_[3] != 'F')
        return fail("Not an ELF file (bad magic)");

    loaded_ = true;
    return true;
}

bool ElfParser::parseHeader() {
    if (!loaded_) return fail("Must call load() before parseHeader()");


    for (int i = 0; i < 16; ++i) header_.e_ident[i] = buffer_[i];

    unsigned char elfClass = header_.e_ident[4]; // EI_CLASS
    unsigned char elfData  = header_.e_ident[5]; // EI_DATA

    if (elfClass != 2) return fail("Only 64-bit ELF (ELFCLASS64) is supported");
    if (elfData != 1 && elfData != 2) return fail("Invalid EI_DATA (endianness) value");

    littleEndian_ = (elfData == 1);

    ElfIterator c(buffer_, 16, littleEndian_); // 16 = end of e_ident

    header_.e_type      = c.read<uint16_t>();
    header_.e_machine   = c.read<uint16_t>();
    header_.e_version   = c.read<uint32_t>();
    header_.e_entry     = c.read<uint64_t>();
    header_.e_phoff     = c.read<uint64_t>();
    header_.e_shoff     = c.read<uint64_t>();
    header_.e_flags     = c.read<uint32_t>();
    header_.e_ehsize    = c.read<uint16_t>();
    header_.e_phentsize = c.read<uint16_t>();
    header_.e_phnum     = c.read<uint16_t>();
    header_.e_shentsize = c.read<uint16_t>();
    header_.e_shnum     = c.read<uint16_t>();
    header_.e_shstrndx  = c.read<uint16_t>();

    return true;
}