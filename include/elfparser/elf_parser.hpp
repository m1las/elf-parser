#pragma once
#include <string>
#include <vector>
#include "elf_types.hpp"

class ElfParser {
public:
    bool load(const std::string& path);
    bool parseHeader();

    const ElfHdr64& header() const { return header_; }
    const std::string& lastError() const { return lastError_; }

private:
    std::vector<unsigned char> buffer_;
    ElfHdr64 header_{};
    bool littleEndian_ = true;
    bool loaded_ = false;

    std::string lastError_;
    bool fail(const std::string& msg) { lastError_ = msg; return false; }
};
