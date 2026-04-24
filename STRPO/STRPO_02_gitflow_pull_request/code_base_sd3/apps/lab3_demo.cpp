#include "ds/base_file.hpp"
#include "ds/bool_array.hpp"
#include "ds/matrix.hpp"
#include "ds/my_string.hpp"
#include "ds/notification.hpp"
#include "ds/worker_db.hpp"

#include <cstdio>
#include <iostream>
#include <utility>

int main() {
    using namespace ds;

    std::cout << "=== Matrix operators ===\n";
    Matrix m1(2), m2(2, 2, 1.0);
    m2 += m1;
    Matrix m3 = (m1 + m2) * m1 * 4.0 / 2.0 - m2;
    std::cout << "m3(0,0) = " << m3.get(0, 0) << "\n\n";

    std::cout << "=== MyString operators ===\n";
    MyString s1("abc"), s2("def"), s3;
    s1 += s2 += "111";
    s2 += "222" + s1 + "333";
    s3 = s1 + "|" + s2;
    std::cout << s3 << "\n\n";

    std::cout << "=== WorkerDb ===\n";
    WorkerDb db;
    db["Ivanov"] = WorkerData("Ivan", 34, "engineer");
    db["Petrov"] = WorkerData("Petr", 43, "manager");
    print_db(db);
    std::cout << "avg age = " << get_avg_age(db) << "\n\n";

    std::cout << "=== Notification queues ===\n";
    NotificationQueue fifo;
    fifo.push(make_message_notification(10, "Alice", "hello", 0));
    fifo.push(make_app_notification(12, "Calendar", "Meeting", "Starts in 5 min", 1));
    Notification first = fifo.pop();
    print_notification(std::cout, first);
    std::cout << "\n";

    NotificationPriorityQueue priority;
    priority.push(make_app_notification(5, "Mail", "Digest", "daily news", 5));
    priority.push(make_message_notification(5, "Bob", "ping", 6));
    priority.push(make_system_notification(8, "Battery low", NotificationSeverity::kUrgent, 7));
    Notification actual = priority.pop();
    print_notification(std::cout, actual);
    std::cout << "\n\n";

    std::cout << "=== BaseFile move ===\n";
    {
        BaseFile file1("lab3_move_demo.txt", "wb");
        BaseFile file2 = std::move(file1);
        const char* text = "move works";
        file2.write(text, 10);
    }
    std::remove("lab3_move_demo.txt");

    std::cout << "=== BoolArray ===\n";
    BoolArray bits(10);
    bits[4] = bits[6] = true;
    bits[2] = (!bits[6] && bits[8]) || (bits[0] != true);
    bits.resize(12, true);
    for (std::size_t i = 0; i < bits.size(); ++i) std::cout << static_cast<bool>(bits[i]);
    std::cout << '\n';
    return 0;
}
