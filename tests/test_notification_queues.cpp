#include "ds/notification.hpp"

#include <cassert>

int main() {
    using namespace ds;

    NotificationQueue fifo;
    assert(fifo.empty());

    fifo.push(make_message_notification(10, "Alice", "hello", 0));
    fifo.push(make_app_notification(12, "Calendar", "Meeting", "soon", 1));

    assert(fifo.size() == 2);
    assert(!fifo.empty());

    const Notification& fifo_front = fifo.front();
    assert(fifo_front.type == NotificationType::kMessage);
    assert(fifo_front.timestamp == 10);

    Notification first = fifo.pop();
    assert(first.type == NotificationType::kMessage);
    assert(fifo.size() == 1);

    const Notification& second_front = fifo.front();
    assert(second_front.type == NotificationType::kApp);
    assert(second_front.timestamp == 12);

    NotificationPriorityQueue priority;
    assert(priority.empty());

    priority.push(make_app_notification(5, "Mail", "Digest", "daily news", 5));
    priority.push(make_message_notification(5, "Bob", "ping", 6));
    priority.push(make_system_notification(8, "Battery low", NotificationSeverity::kUrgent, 7));
    priority.push(make_system_notification(3, "Plain", NotificationSeverity::kNormal, 8));

    assert(priority.size() == 4);
    assert(!priority.empty());

    const Notification& best_peek = priority.peek();
    assert(best_peek.type == NotificationType::kSystem);
    assert(best_peek.payload.system.severity == NotificationSeverity::kUrgent);
    assert(priority.size() == 4);

    Notification best = priority.pop();
    assert(best.type == NotificationType::kSystem);
    assert(best.payload.system.severity == NotificationSeverity::kUrgent);
    assert(priority.size() == 3);

    const Notification& next_peek = priority.peek();
    assert(next_peek.timestamp == 3);

    Notification next = priority.pop();
    assert(next.timestamp == 3);

    return 0;
}