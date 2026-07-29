#include <iostream>
#include <iomanip>

#include "elfparser/elf_parser.hpp"
#include "utils/byte_iterator.hpp"
#include "utils/translate_types.hpp"

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
    const std::vector<unsigned char>& raw_buffer = parser.buffer();

    std::cout << "ELF Header:\n";

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


    const std::vector<Elf64_Shdr>& sectionHeaders = parser.sectionHeaders();
    const uint16_t shstrtab_index = h.e_shstrndx;
    const uint64_t shstrtab_offset = sectionHeaders[shstrtab_index].sh_offset;

    std::cout << "\nSection Headers:\n";
    for (const auto& sh : sectionHeaders) {
        std::string sectionName = reinterpret_cast<const char*>(raw_buffer.data() + shstrtab_offset + sh.sh_name);
        if(sectionName.empty()) continue;

        std::cout << "Name: " << sectionName << ", Type: " << section_type_to_string(sh.sh_type) << std::hex << ", Offset: 0x" << sh.sh_offset << ", Size: 0x" << sh.sh_size << std::dec << "\n";
    }
    

    const std::vector<Elf64_Phdr>& programHeaders = parser.programHeaders();
    std::cout << "\nProgram Headers:\n";
    for (const auto& ph : programHeaders) {
        std::cout << "Type: " << segment_type_to_string(ph.p_type) << std::hex << ", Offset: 0x" << ph.p_offset << 
        ", VAddr: 0x" << ph.p_vaddr << ", PAddr: 0x" << ph.p_paddr << ", FileSz: 0x" << ph.p_filesz << 
        ", MemSz: 0x" << ph.p_memsz << ", Flags: " << segment_flags_to_string(ph.p_flags) << ", Align: 0x" << ph.p_align << std::dec << "\n";
    }


    const std::vector<Elf64_Sym>& symbols = parser.symbols();

    if (parser.isStripped()) {
        std::cout << "\nThe ELF file is stripped. No symbols available.\n"; // maybe we will parse dynsym as well later
        return 0;
    }

    std::cout << "\nSymbol Table '.symtab':\n";
    const uint32_t strtab_idx = parser.symtabStrtabIndex();

    for (const auto& sym : symbols) {
        std::string symbolName = "(null)";
        if (sym.st_name != 0) {
            symbolName = reinterpret_cast<const char*>(raw_buffer.data() + sectionHeaders[strtab_idx].sh_offset + sym.st_name);
        }

        uint8_t binding = sym.st_info >> 4; // top nibble
        uint8_t type    = sym.st_info & 0xf; // bottom nibble

        std::cout << "Binding: " << symbol_binding_to_string(binding) << ", Type: " << symbol_type_to_string(type) << 
        ", Section index: " << section_index_to_string(sym.st_shndx) << ", Size: 0x" << sym.st_size << ", Value: 0x" << 
        std::hex << sym.st_value << std::dec << ", Name: " << symbolName << "\n";
    }
    
    return 0;
}




