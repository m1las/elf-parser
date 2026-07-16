#pragma once
#include <vector>
#include <cstdint>
#include <cstring>


template<typename T>
T readBytes(const std::vector<unsigned char>& buffer, std::size_t offset, bool little_endian = true) {

    static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");

    if (offset + sizeof(T) > buffer.size()) {
        throw std::out_of_range("readBytes: offset out of range");
    }

    T bytes;
    std::memcpy(&bytes, buffer.data() + offset, sizeof(bytes));
    
    // If T is an integral type, check endianness and swap if necessary
    if constexpr(std::is_integral_v<T>) {

        // Assuming the system is little-endian, if the data is big-endian, we need to swap the bytes
        if (!little_endian) {
            if constexpr(sizeof(T) == 2) {
                bytes = (bytes >> 8) | (bytes << 8);

            } else if constexpr(sizeof(T) == 4) {
                bytes = ((bytes >> 24) & 0x000000FF) |
                        ((bytes >> 8)  & 0x0000FF00) |
                        ((bytes << 8)  & 0x00FF0000) |
                        ((bytes << 24) & 0xFF000000);

            } else if constexpr(sizeof(T) == 8) {
                bytes = ((bytes >> 56) & 0x00000000000000FFULL) |
                        ((bytes >> 40) & 0x000000000000FF00ULL) |
                        ((bytes >> 24) & 0x0000000000FF0000ULL) |
                        ((bytes >> 8)  & 0x00000000FF000000ULL) |
                        ((bytes << 8)  & 0x000000FF00000000ULL) |
                        ((bytes << 24) & 0x0000FF0000000000ULL) |
                        ((bytes << 40) & 0x00FF000000000000ULL) |
                        ((bytes << 56) & 0xFF00000000000000ULL);
            }
        }
    }

    return bytes;
}