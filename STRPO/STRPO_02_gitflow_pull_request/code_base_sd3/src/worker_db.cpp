#include "ds/worker_db.hpp"

#include <iostream>

namespace ds {

WorkerData::WorkerData() : name(""), age(0), role("") {}
WorkerData::WorkerData(const char* name_value, int age_value, const char* role_value)
    : name(name_value), age(age_value), role(role_value) {}

WorkerDb::Iterator::Iterator(WorkerDb* owner, std::size_t index) : owner_(owner), index_(index) {}
WorkerData& WorkerDb::Iterator::operator*() const { return owner_->entries_[index_].value; }
WorkerData* WorkerDb::Iterator::operator->() const { return &owner_->entries_[index_].value; }
WorkerDb::Iterator& WorkerDb::Iterator::operator++() { ++index_; return *this; }
WorkerDb::Iterator WorkerDb::Iterator::operator++(int) { Iterator temp(*this); ++(*this); return temp; }
bool WorkerDb::Iterator::operator==(const Iterator& other) const { return owner_ == other.owner_ && index_ == other.index_; }
bool WorkerDb::Iterator::operator!=(const Iterator& other) const { return !(*this == other); }
const MyString& WorkerDb::Iterator::key() const { return owner_->entries_[index_].key; }

WorkerDb::WorkerDb() : entries_(nullptr), size_(0), capacity_(0) {}
WorkerDb::WorkerDb(const WorkerDb& other) : entries_(nullptr), size_(0), capacity_(0) {
    reserve(other.capacity_);
    size_ = other.size_;
    for (std::size_t i = 0; i < size_; ++i) entries_[i] = other.entries_[i];
}
WorkerDb::WorkerDb(WorkerDb&& other) noexcept : entries_(other.entries_), size_(other.size_), capacity_(other.capacity_) {
    other.entries_ = nullptr; other.size_ = 0; other.capacity_ = 0;
}
WorkerDb& WorkerDb::operator=(const WorkerDb& other) {
    if (this != &other) {
        Entry* new_entries = nullptr;
        if (other.capacity_ > 0) {
            new_entries = new Entry[other.capacity_];
            for (std::size_t i = 0; i < other.size_; ++i) new_entries[i] = other.entries_[i];
        }
        delete[] entries_;
        entries_ = new_entries; size_ = other.size_; capacity_ = other.capacity_;
    }
    return *this;
}
WorkerDb& WorkerDb::operator=(WorkerDb&& other) noexcept {
    if (this != &other) {
        delete[] entries_;
        entries_ = other.entries_; size_ = other.size_; capacity_ = other.capacity_;
        other.entries_ = nullptr; other.size_ = 0; other.capacity_ = 0;
    }
    return *this;
}
WorkerDb::~WorkerDb() { delete[] entries_; }

void WorkerDb::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) return;
    Entry* new_entries = new Entry[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) new_entries[i] = entries_[i];
    delete[] entries_;
    entries_ = new_entries; capacity_ = new_capacity;
}

std::size_t WorkerDb::find_index(const MyString& surname) const {
    for (std::size_t i = 0; i < size_; ++i) if (entries_[i].key == surname) return i;
    return size_;
}

WorkerData& WorkerDb::operator[](const char* surname) { return (*this)[MyString(surname)]; }
WorkerData& WorkerDb::operator[](const MyString& surname) {
    std::size_t index = find_index(surname);
    if (index != size_) return entries_[index].value;
    if (size_ == capacity_) reserve(capacity_ == 0 ? 4 : capacity_ * 2);
    entries_[size_].key = surname;
    entries_[size_].value = WorkerData();
    ++size_;
    return entries_[size_ - 1].value;
}

const WorkerData* WorkerDb::find(const char* surname) const {
    std::size_t index = find_index(MyString(surname));
    return index == size_ ? nullptr : &entries_[index].value;
}

std::size_t WorkerDb::size() const { return size_; }
WorkerDb::Iterator WorkerDb::begin() { return Iterator(this, 0); }
WorkerDb::Iterator WorkerDb::end() { return Iterator(this, size_); }

void print_db(WorkerDb& db) {
    for (auto it = db.begin(); it != db.end(); ++it) {
        std::cout << it.key() << " -> " << it->name << ", age=" << it->age << ", role=" << it->role << '\n';
    }
}

double get_avg_age(WorkerDb& db) {
    if (db.size() == 0) return 0.0;
    int sum = 0;
    for (auto it = db.begin(); it != db.end(); ++it) sum += it->age;
    return static_cast<double>(sum) / static_cast<double>(db.size());
}

}  // namespace ds
