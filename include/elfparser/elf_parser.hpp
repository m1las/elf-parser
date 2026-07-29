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
    const std::string& lastError() const { return lastError_; }

private:
    std::vector<unsigned char> buffer_;
    ElfHdr64 header_{};
    std::vector<Elf64_Shdr> sectionHeaders_{};
    std::vector<Elf64_Phdr> programHeaders_{};

    bool littleEndian_ = true;
    bool loaded_ = false;

    std::string lastError_;
    bool fail(const std::string& msg) { lastError_ = msg; return false; }
};
