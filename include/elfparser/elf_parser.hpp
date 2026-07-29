#pragma once
#include <string>
#include <vector>
#include "elf_types.hpp"

class ElfParser {
public:
    bool load(const std::string& path);
    bool parseHeader();

    const std::vector<unsigned char>& buffer() const { return buffer_; }

    const ElfHdr64& header() const { return header_; }
    const std::vector<Elf64_Shdr>& sectionHeaders() const { return sectionHeaders_; }
    const std::vector<Elf64_Phdr>& programHeaders() const { return programHeaders_; }
    const std::vector<Elf64_Sym>& symbols() const { return symbols_; }
    uint32_t symtabStrtabIndex() const { return symtabStrtabIndex_; }

    bool isStripped() const { return stripped_; }
    bool isLittleEndian() const { return littleEndian_; }
    const std::string& lastError() const { return lastError_; }

private:
    std::vector<unsigned char> buffer_;
    ElfHdr64 header_{};
    std::vector<Elf64_Shdr> sectionHeaders_{};
    std::vector<Elf64_Phdr> programHeaders_{};
    std::vector<Elf64_Sym> symbols_{};
    uint32_t symtabStrtabIndex_ = 0;

    bool littleEndian_ = true;
    bool loaded_ = false;
    bool stripped_ = true;

    std::string lastError_;
    bool fail(const std::string& msg) { lastError_ = msg; return false; }
};
