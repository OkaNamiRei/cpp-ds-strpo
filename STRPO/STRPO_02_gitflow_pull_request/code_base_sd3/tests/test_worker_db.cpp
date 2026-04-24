#include "ds/worker_db.hpp"
#include <cassert>
int main() {
    using namespace ds;
    WorkerDb db;
    db["Ivanov"] = WorkerData("Ivan", 34, "engineer");
    db["Petrov"] = WorkerData("Petr", 43, "manager");
    db["Sidorov"] = WorkerData("Sidr", 23, "intern");
    const WorkerData* worker = db.find("Petrov");
    assert(worker != nullptr);
    assert(worker->age == 43);
    double avg = get_avg_age(db);
    assert(avg > 33.0 && avg < 34.0);
    int count = 0;
    for (auto it = db.begin(); it != db.end(); ++it) { assert(!it.key().empty()); ++count; }
    assert(count == 3);
    return 0;
}
