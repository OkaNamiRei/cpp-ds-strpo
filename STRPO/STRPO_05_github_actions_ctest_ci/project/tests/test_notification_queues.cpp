#include "ds/notification.hpp"
#include <cassert>
int main() {
    using namespace ds;
    NotificationQueue fifo;
    fifo.push(make_message_notification(10, "Alice", "hello", 0));
    fifo.push(make_app_notification(12, "Calendar", "Meeting", "soon", 1));
    assert(fifo.size() == 2);
    Notification first = fifo.pop();
    assert(first.type == NotificationType::kMessage);
    NotificationPriorityQueue priority;
    priority.push(make_app_notification(5, "Mail", "Digest", "daily news", 5));
    priority.push(make_message_notification(5, "Bob", "ping", 6));
    priority.push(make_system_notification(8, "Battery low", NotificationSeverity::kUrgent, 7));
    priority.push(make_system_notification(3, "Plain", NotificationSeverity::kNormal, 8));
    Notification best = priority.pop();
    assert(best.type == NotificationType::kSystem);
    assert(best.payload.system.severity == NotificationSeverity::kUrgent);
    Notification next = priority.pop();
    assert(next.timestamp == 3);
    return 0;
}
