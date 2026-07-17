#pragma once
#include <vector>
#include <stdexcept>
#include "utils/read_bytes.hpp"

/*
Because the ELF header is fixed size and is read sequentially, we can use a simple iterator/cursor to read the fields in order. 
This avoids the need for storing the header offset and size. 
*/

class ElfIterator {
public:
    ElfIterator(const std::vector<unsigned char>& buffer, size_t start, bool littleEndian)
        : buffer_(buffer), pos_(start), littleEndian_(littleEndian) {}

    template <typename T>
    T read() {
        T value = readBytes<T>(buffer_, pos_, littleEndian_);
        pos_ += sizeof(T);
        return value;
    }

    void seek(std::size_t offset)
    {
        if (offset > buffer_.size())
            throw std::out_of_range("BinaryReader::seek");

        pos_ = offset;
    }

    void skip(std::size_t bytes)
    {
        seek(pos_ + bytes);
    }

    std::size_t tell() const
    {
        return pos_;
    }

private:
    const std::vector<unsigned char>& buffer_;
    size_t pos_;
    bool littleEndian_;
};