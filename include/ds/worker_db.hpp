#pragma once

#include "ds/my_string.hpp"
#include <cstddef>

namespace ds {

    struct WorkerData {
        MyString name;
        int age;
        MyString role;
        WorkerData();
        WorkerData(const char* name_value, int age_value, const char* role_value);
    };

    class WorkerDb {
    public:
        class Iterator {
        public:
            Iterator(WorkerDb* owner, std::size_t index);
            WorkerData& operator*() const;
            WorkerData* operator->() const;
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
            const MyString& key() const;
        private:
            WorkerDb* owner_;
            std::size_t index_;
        };

        WorkerDb();
        WorkerDb(const WorkerDb& other);
        WorkerDb(WorkerDb&& other) noexcept;
        WorkerDb& operator=(const WorkerDb& other);
        WorkerDb& operator=(WorkerDb&& other) noexcept;
        ~WorkerDb();

        WorkerData& operator[](const char* surname);
        WorkerData& operator[](const MyString& surname);
        const WorkerData* find(const char* surname) const;

        bool contains(const char* surname) const;
        bool contains(const MyString& surname) const;

        bool erase(const char* surname);
        bool erase(const MyString& surname);

        std::size_t size() const;
        Iterator begin();
        Iterator end();

    private:
        struct Entry { MyString key; WorkerData value; };
        Entry* entries_;
        std::size_t size_;
        std::size_t capacity_;
        void reserve(std::size_t new_capacity);
        std::size_t find_index(const MyString& surname) const;
    };

    void print_db(WorkerDb& db);
    double get_avg_age(WorkerDb& db);

}  // namespace ds