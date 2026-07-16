#include <iostream>
#include <iomanip>

#include "elfparser/elf_parser.hpp"


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
    std::cout << "Entry:   0x" << std::hex << h.e_entry << std::dec << "\n";
    std::cout << "PH off:  " << h.e_phoff << " (" << h.e_phnum << " entries)\n";
    std::cout << "SH off:  " << h.e_shoff << " (" << h.e_shnum << " entries)\n";
}




