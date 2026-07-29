#pragma once
#include <string>
#include <sstream>
#include <cstdint>
#include <iomanip>
#include "../elfparser/elf_types.hpp"

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4

inline std::string segment_flags_to_string(uint32_t flags) {
    std::string out;
    out += (flags & PF_R) ? 'R' : '-';
    out += (flags & PF_W) ? 'W' : '-';
    out += (flags & PF_X) ? 'E' : '-';
    return out;
}

inline std::string section_type_to_string(uint32_t type) {
    switch (type)
    {
        case SHT_NULL:          return "NULL";
        case SHT_PROGBITS:      return "PROGBITS";
        case SHT_SYMTAB:        return "SYMTAB";
        case SHT_STRTAB:        return "STRTAB";
        case SHT_RELA:          return "RELA";
        case SHT_HASH:          return "HASH";
        case SHT_DYNAMIC:       return "DYNAMIC";
        case SHT_NOTE:          return "NOTE";
        case SHT_NOBITS:        return "NOBITS";
        case SHT_REL:           return "REL";
        case SHT_SHLIB:         return "SHLIB";
        case SHT_DYNSYM:        return "DYNSYM";
        case SHT_INIT_ARRAY:    return "INIT_ARRAY";
        case SHT_FINI_ARRAY:    return "FINI_ARRAY";
        case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
        case SHT_GROUP:         return "GROUP";
        case SHT_SYMTAB_SHNDX:  return "SYMTAB_SHNDX";
        case SHT_GNU_ATTRIBUTES:return "GNU_ATTRIBUTES";
        case SHT_GNU_HASH:      return "GNU_HASH";
        case SHT_GNU_LIBLIST:   return "GNU_LIBLIST";
        case SHT_CHECKSUM:      return "CHECKSUM";
        case SHT_SUNW_move:     return "SUNW_move";
        case SHT_SUNW_COMDAT:   return "SUNW_COMDAT";
        case SHT_SUNW_syminfo:  return "SUNW_syminfo";
        case SHT_GNU_verdef:    return "GNU_verdef";
        case SHT_GNU_verneed:   return "GNU_verneed";
        case SHT_GNU_versym:    return "GNU_versym";
        default:
        {
            std::ostringstream oss;
            oss << "UNKNOWN (0x" << std::hex << type << ")";
            return oss.str();
        }
    }
}

inline std::string segment_type_to_string(uint32_t type) {
    switch (type)
    {
        case PT_NULL:         return "NULL";
        case PT_LOAD:         return "LOAD";
        case PT_DYNAMIC:      return "DYNAMIC";
        case PT_INTERP:       return "INTERP";
        case PT_NOTE:         return "NOTE";
        case PT_SHLIB:        return "SHLIB";
        case PT_PHDR:         return "PHDR";
        case PT_TLS:          return "TLS";
        case PT_GNU_EH_FRAME: return "GNU_EH_FRAME";
        case PT_GNU_STACK:    return "GNU_STACK";
        case PT_GNU_RELRO:    return "GNU_RELRO";
        case PT_GNU_PROPERTY: return "GNU_PROPERTY";
        default:
        {
            std::ostringstream oss;
            oss << "UNKNOWN (0x" << std::hex << type << ")";
            return oss.str();
        }
    }
}