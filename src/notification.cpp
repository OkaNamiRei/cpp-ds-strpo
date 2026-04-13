#include "ds/notification.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace ds {

    namespace {
        void copy_text(char* dst, std::size_t capacity, const char* src) {
            if (capacity == 0) return;
            if (src == nullptr) { dst[0] = '\0'; return; }
            std::strncpy(dst, src, capacity - 1);
            dst[capacity - 1] = '\0';
        }
    }  // namespace

    Notification make_system_notification(long timestamp, const char* message, NotificationSeverity severity, unsigned long sequence) {
        Notification n{};
        n.timestamp = timestamp; n.sequence = sequence; n.type = NotificationType::kSystem;
        copy_text(n.payload.system.message, sizeof(n.payload.system.message), message);
        n.payload.system.severity = severity;
        return n;
    }

    Notification make_message_notification(long timestamp, const char* contact, const char* text, unsigned long sequence) {
        Notification n{};
        n.timestamp = timestamp; n.sequence = sequence; n.type = NotificationType::kMessage;
        copy_text(n.payload.message.contact, sizeof(n.payload.message.contact), contact);
        copy_text(n.payload.message.text, sizeof(n.payload.message.text), text);
        return n;
    }

    Notification make_app_notification(long timestamp, const char* app_name, const char* title, const char* text, unsigned long sequence) {
        Notification n{};
        n.timestamp = timestamp; n.sequence = sequence; n.type = NotificationType::kApp;
        copy_text(n.payload.app.app_name, sizeof(n.payload.app.app_name), app_name);
        copy_text(n.payload.app.title, sizeof(n.payload.app.title), title);
        copy_text(n.payload.app.text, sizeof(n.payload.app.text), text);
        return n;
    }

    void print_notification(std::ostream& os, const Notification& notification) {
        os << '[' << notification.timestamp << "] ";
        switch (notification.type) {
        case NotificationType::kSystem:
            os << "SYSTEM: " << notification.payload.system.message << " ("
                << (notification.payload.system.severity == NotificationSeverity::kUrgent ? "urgent" : "normal") << ')';
            break;
        case NotificationType::kMessage:
            os << "MESSAGE from " << notification.payload.message.contact << ": " << notification.payload.message.text;
            break;
        case NotificationType::kApp:
            os << "APP " << notification.payload.app.app_name << " / " << notification.payload.app.title
                << ": " << notification.payload.app.text;
            break;
        }
    }

    std::size_t count_notifications_by_type(const Notification* notifications, std::size_t count, NotificationType type) {
        std::size_t total = 0;
        for (std::size_t i = 0; i < count; ++i) {
            if (notifications[i].type == type) {
                ++total;
            }
        }
        return total;
    }

    NotificationQueue::Iterator::Iterator(const NotificationQueue* owner, std::size_t offset)
        : owner_(owner), offset_(offset) {
    }

    const Notification& NotificationQueue::Iterator::operator*() const { return owner_->at_offset(offset_); }
    const Notification* NotificationQueue::Iterator::operator->() const { return &owner_->at_offset(offset_); }
    NotificationQueue::Iterator& NotificationQueue::Iterator::operator++() { ++offset_; return *this; }
    NotificationQueue::Iterator NotificationQueue::Iterator::operator++(int) { Iterator tmp(*this); ++(*this); return tmp; }
    bool NotificationQueue::Iterator::operator==(const Iterator& other) const {
        return owner_ == other.owner_ && offset_ == other.offset_;
    }
    bool NotificationQueue::Iterator::operator!=(const Iterator& other) const { return !(*this == other); }

    NotificationQueue::NotificationQueue() : data_(nullptr), capacity_(0), size_(0), head_(0) {}

    NotificationQueue::NotificationQueue(const NotificationQueue& other)
        : data_(nullptr), capacity_(0), size_(0), head_(0) {
        reserve(other.capacity_);
        size_ = other.size_;
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.at_offset(i);
        }
    }

    NotificationQueue::NotificationQueue(NotificationQueue&& other) noexcept
        : data_(other.data_), capacity_(other.capacity_), size_(other.size_), head_(other.head_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.head_ = 0;
    }

    NotificationQueue& NotificationQueue::operator=(const NotificationQueue& other) {
        if (this != &other) {
            Notification* new_data = other.capacity_ ? new Notification[other.capacity_] : nullptr;
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.at_offset(i);
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = other.capacity_;
            size_ = other.size_;
            head_ = 0;
        }
        return *this;
    }

    NotificationQueue& NotificationQueue::operator=(NotificationQueue&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            head_ = other.head_;
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
            other.head_ = 0;
        }
        return *this;
    }

    NotificationQueue::~NotificationQueue() { delete[] data_; }

    const Notification& NotificationQueue::at_offset(std::size_t offset) const {
        return data_[(head_ + offset) % capacity_];
    }

    void NotificationQueue::reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        Notification* new_data = new Notification[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = at_offset(i);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        head_ = 0;
    }

    void NotificationQueue::push(Notification notification) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 4 : capacity_ * 2);
        }
        data_[(head_ + size_) % capacity_] = notification;
        ++size_;
    }

    std::size_t NotificationQueue::size() const { return size_; }
    bool NotificationQueue::empty() const { return size_ == 0; }

    const Notification& NotificationQueue::front() const {
        if (empty()) {
            throw std::out_of_range("notification queue is empty");
        }
        return data_[head_];
    }

    Notification NotificationQueue::pop() {
        if (empty()) {
            throw std::out_of_range("notification queue is empty");
        }
        Notification result = data_[head_];
        head_ = (head_ + 1) % capacity_;
        --size_;
        return result;
    }

    NotificationQueue::Iterator NotificationQueue::begin() const { return Iterator(this, 0); }
    NotificationQueue::Iterator NotificationQueue::end() const { return Iterator(this, size_); }

    NotificationPriorityQueue::NotificationPriorityQueue() : data_(nullptr), size_(0), capacity_(0) {}

    NotificationPriorityQueue::NotificationPriorityQueue(const NotificationPriorityQueue& other)
        : data_(nullptr), size_(0), capacity_(0) {
        reserve(other.capacity_);
        size_ = other.size_;
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    NotificationPriorityQueue::NotificationPriorityQueue(NotificationPriorityQueue&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    NotificationPriorityQueue& NotificationPriorityQueue::operator=(const NotificationPriorityQueue& other) {
        if (this != &other) {
            Notification* new_data = other.capacity_ ? new Notification[other.capacity_] : nullptr;
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    NotificationPriorityQueue& NotificationPriorityQueue::operator=(NotificationPriorityQueue&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    NotificationPriorityQueue::~NotificationPriorityQueue() { delete[] data_; }

    void NotificationPriorityQueue::reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        Notification* new_data = new Notification[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    int NotificationPriorityQueue::type_rank(const Notification& notification) {
        if (notification.type == NotificationType::kMessage) return 3;
        if (notification.type == NotificationType::kSystem) return 2;
        return 1;
    }

    bool NotificationPriorityQueue::is_more_actual(const Notification& lhs, const Notification& rhs) {
        bool lhs_urgent =
            lhs.type == NotificationType::kSystem &&
            lhs.payload.system.severity == NotificationSeverity::kUrgent;
        bool rhs_urgent =
            rhs.type == NotificationType::kSystem &&
            rhs.payload.system.severity == NotificationSeverity::kUrgent;

        if (lhs_urgent != rhs_urgent) return lhs_urgent;
        if (lhs.timestamp != rhs.timestamp) return lhs.timestamp < rhs.timestamp;

        int lhs_rank = type_rank(lhs);
        int rhs_rank = type_rank(rhs);
        if (lhs_rank != rhs_rank) return lhs_rank > rhs_rank;

        return lhs.sequence < rhs.sequence;
    }

    void NotificationPriorityQueue::push(Notification notification) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 4 : capacity_ * 2);
        }
        data_[size_++] = notification;
    }

    std::size_t NotificationPriorityQueue::size() const { return size_; }
    bool NotificationPriorityQueue::empty() const { return size_ == 0; }

    const Notification& NotificationPriorityQueue::peek() const {
        if (empty()) {
            throw std::out_of_range("notification priority queue is empty");
        }

        std::size_t best = 0;
        for (std::size_t i = 1; i < size_; ++i) {
            if (is_more_actual(data_[i], data_[best])) {
                best = i;
            }
        }
        return data_[best];
    }

    Notification NotificationPriorityQueue::pop() {
        if (empty()) {
            throw std::out_of_range("notification priority queue is empty");
        }

        std::size_t best = 0;
        for (std::size_t i = 1; i < size_; ++i) {
            if (is_more_actual(data_[i], data_[best])) {
                best = i;
            }
        }

        Notification result = data_[best];
        for (std::size_t i = best + 1; i < size_; ++i) {
            data_[i - 1] = data_[i];
        }
        --size_;
        return result;
    }

}  // namespace ds