#pragma once

#include <cstddef>
#include <iosfwd>

namespace ds {

    enum class NotificationType { kSystem, kMessage, kApp };
    enum class NotificationSeverity { kNormal, kUrgent };

    struct Notification {
        struct SystemData { char message[96]; NotificationSeverity severity; };
        struct MessageData { char contact[48]; char text[96]; };
        struct AppData { char app_name[48]; char title[64]; char text[96]; };

        long timestamp;
        unsigned long sequence;
        NotificationType type;
        union Payload {
            SystemData system;
            MessageData message;
            AppData app;
            Payload() {}
        } payload;
    };

    Notification make_system_notification(long timestamp, const char* message, NotificationSeverity severity,
        unsigned long sequence = 0);
    Notification make_message_notification(long timestamp, const char* contact, const char* text,
        unsigned long sequence = 0);
    Notification make_app_notification(long timestamp, const char* app_name, const char* title, const char* text,
        unsigned long sequence = 0);
    void print_notification(std::ostream& os, const Notification& notification);
    std::size_t count_notifications_by_type(const Notification* notifications, std::size_t count, NotificationType type);

    class NotificationQueue {
    public:
        class Iterator {
        public:
            Iterator(const NotificationQueue* owner, std::size_t offset);
            const Notification& operator*() const;
            const Notification* operator->() const;
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        private:
            const NotificationQueue* owner_;
            std::size_t offset_;
        };

        NotificationQueue();
        NotificationQueue(const NotificationQueue& other);
        NotificationQueue(NotificationQueue&& other) noexcept;
        NotificationQueue& operator=(const NotificationQueue& other);
        NotificationQueue& operator=(NotificationQueue&& other) noexcept;
        ~NotificationQueue();

        void push(Notification notification);
        std::size_t size() const;
        bool empty() const;
        const Notification& front() const;
        Notification pop();

        Iterator begin() const;
        Iterator end() const;

    protected:
        const Notification& at_offset(std::size_t offset) const;
        void reserve(std::size_t new_capacity);

        Notification* data_;
        std::size_t capacity_;
        std::size_t size_;
        std::size_t head_;
    };

    class NotificationPriorityQueue {
    public:
        NotificationPriorityQueue();
        NotificationPriorityQueue(const NotificationPriorityQueue& other);
        NotificationPriorityQueue(NotificationPriorityQueue&& other) noexcept;
        NotificationPriorityQueue& operator=(const NotificationPriorityQueue& other);
        NotificationPriorityQueue& operator=(NotificationPriorityQueue&& other) noexcept;
        ~NotificationPriorityQueue();

        void push(Notification notification);
        std::size_t size() const;
        bool empty() const;
        const Notification& peek() const;
        Notification pop();

    private:
        Notification* data_;
        std::size_t size_;
        std::size_t capacity_;

        void reserve(std::size_t new_capacity);
        static bool is_more_actual(const Notification& lhs, const Notification& rhs);
        static int type_rank(const Notification& notification);
    };

}  // namespace ds