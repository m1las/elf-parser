#pragma once
#include <cstdint>

// Section Header Types

#define SHT_NULL            0
#define SHT_PROGBITS        1
#define SHT_SYMTAB          2
#define SHT_STRTAB          3
#define SHT_RELA            4
#define SHT_HASH            5
#define SHT_DYNAMIC         6
#define SHT_NOTE            7
#define SHT_NOBITS          8
#define SHT_REL             9
#define SHT_SHLIB           10
#define SHT_DYNSYM          11
#define SHT_INIT_ARRAY      14
#define SHT_FINI_ARRAY      15
#define SHT_PREINIT_ARRAY   16
#define SHT_GROUP           17
#define SHT_SYMTAB_SHNDX    18

#define SHT_LOOS            0x60000000
#define SHT_GNU_ATTRIBUTES  0x6ffffff5
#define SHT_GNU_HASH        0x6ffffff6
#define SHT_GNU_LIBLIST     0x6ffffff7
#define SHT_CHECKSUM        0x6ffffff8
#define SHT_SUNW_move       0x6ffffffa
#define SHT_SUNW_COMDAT     0x6ffffffb
#define SHT_SUNW_syminfo    0x6ffffffc
#define SHT_GNU_verdef      0x6ffffffd
#define SHT_GNU_verneed     0x6ffffffe
#define SHT_GNU_versym      0x6fffffff
#define SHT_HIOS            0x6fffffff

#define SHT_LOPROC          0x70000000
#define SHT_HIPROC          0x7fffffff

#define SHT_LOUSER          0x80000000
#define SHT_HIUSER          0xffffffff


// Program Header Types

#define PT_NULL             0
#define PT_LOAD             1
#define PT_DYNAMIC          2
#define PT_INTERP           3
#define PT_NOTE             4
#define PT_SHLIB            5
#define PT_PHDR             6
#define PT_TLS              7

#define PT_LOOS             0x60000000
#define PT_HIOS             0x6fffffff

#define PT_GNU_EH_FRAME     0x6474e550
#define PT_GNU_STACK        0x6474e551
#define PT_GNU_RELRO        0x6474e552
#define PT_GNU_PROPERTY     0x6474e553

#define PT_LOPROC           0x70000000
#define PT_HIPROC           0x7fffffff


struct ElfHdr64 {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

 struct Elf64_Shdr {
    uint32_t sh_name; 
    uint32_t sh_type; 
    uint64_t sh_flags; 
    uint64_t sh_addr; 
    uint64_t sh_offset; 
    uint64_t sh_size; 
    uint32_t sh_link; 
    uint32_t sh_info; 
    uint64_t sh_addralign; 
    uint64_t sh_entsize; 
};

struct Elf64_Phdr {
  uint32_t p_type;
  uint32_t p_flags;
  uint64_t p_offset;
  uint64_t p_vaddr;
  uint64_t p_paddr;
  uint64_t p_filesz;
  uint64_t p_memsz;
  uint64_t p_align;	
};