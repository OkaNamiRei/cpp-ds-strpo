#pragma once

#include <cstddef>

namespace ds {

    class BoolArray {
    public:
        class BitReference {
        public:
            BitReference(unsigned char* byte, unsigned char mask);
            BitReference& operator=(bool value);
            BitReference& operator=(const BitReference& other);
            operator bool() const;
            bool operator!() const;
        private:
            unsigned char* byte_;
            unsigned char mask_;
        };

        BoolArray();
        explicit BoolArray(std::size_t size, bool value = false);
        BoolArray(const BoolArray& other);
        BoolArray(BoolArray&& other) noexcept;
        BoolArray& operator=(const BoolArray& other);
        BoolArray& operator=(BoolArray&& other) noexcept;
        ~BoolArray();

        std::size_t size() const;
        void resize(std::size_t new_size, bool fill_value = false);

        std::size_t count_true() const;
        void flip(std::size_t index);

        BitReference operator[](std::size_t index);
        bool operator[](std::size_t index) const;

    private:
        unsigned char* data_;
        std::size_t size_;
        std::size_t capacity_bytes_;

        static std::size_t bytes_for_size(std::size_t size);
        void ensure_index(std::size_t index) const;
        bool get_bit(std::size_t index) const;
    };

}  // namespace ds