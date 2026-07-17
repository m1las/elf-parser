#include <iostream>
#include <iomanip>

#include "elfparser/elf_parser.hpp"
#include "utils/byte_iterator.hpp"

#include <fstream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }

    ElfParser parser;
    if (!parser.load(argv[1]) || !parser.parseHeader()) {
        std::cerr << "Error: " << parser.lastError() << "\n";
        return 1;
    }

    const ElfHdr64& h = parser.header();
    std::cout << "Type:    " << h.e_type << "\n";
    std::cout << "Machine: " << h.e_machine << "\n";
    std::cout << "Version: " << h.e_version << "\n";
    std::cout << "Entry:   0x" << std::hex << h.e_entry << std::dec << "\n";
    std::cout << "PH offset:  " << h.e_phoff << " (" << h.e_phnum << " entries)\n";
    std::cout << "SH offset:  " << h.e_shoff << " (" << h.e_shnum << " entries)\n";
    std::cout << "Flags:   0x" << std::hex << h.e_flags << std::dec << "\n";
    std::cout << "ELF header size: " << h.e_ehsize << "\n";
    std::cout << "PH entry size: " << h.e_phentsize << "\n";
    std::cout << "PH entry count: " << h.e_phnum << "\n";
    std::cout << "SH entry size: " << h.e_shentsize << "\n";
    std::cout << "SH entry count: " << h.e_shnum << "\n";
    std::cout << "SH str index: " << h.e_shstrndx << "\n";

    // --------- Testing reading section headers ---------
    // Not worried about error handling here, just testing the iterator. Will add a separate class for reading section headers later.

    // logic copied from ElfParser::parseHeader() to get buffer and endianness
    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> tempBuffer(static_cast<size_t>(size));

    tempBuffer.resize(static_cast<size_t>(size));
    file.read(reinterpret_cast<char*>(tempBuffer.data()), size);

    bool littleEndian = (h.e_ident[5] == 1);

    Elf64_Shdr shdr;
    ElfIterator it(tempBuffer, h.e_shoff, littleEndian);

    std::cout << "\nSection Headers:\n";

    for (int i = 0; i < h.e_shnum; ++i) {
        shdr.sh_name      = it.read<uint32_t>();
        shdr.sh_type      = it.read<uint32_t>();
        shdr.sh_flags     = it.read<uint64_t>();
        shdr.sh_addr      = it.read<uint64_t>();
        shdr.sh_offset    = it.read<uint64_t>();
        shdr.sh_size      = it.read<uint64_t>();
        shdr.sh_link      = it.read<uint32_t>();
        shdr.sh_info      = it.read<uint32_t>();
        shdr.sh_addralign = it.read<uint64_t>();
        shdr.sh_entsize   = it.read<uint64_t>();

        std::cout << "Section " << i << ": offset=0x" << std::hex << shdr.sh_offset
                  << ", size=0x" << shdr.sh_size << std::dec << "\n";
    }

    // works against /bin/ls on my machine
    
    return 0;
}




