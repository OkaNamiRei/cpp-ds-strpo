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

    assert(db.contains("Ivanov"));
    assert(db.contains("Petrov"));
    assert(!db.contains("Smirnov"));

    bool removed = db.erase("Petrov");
    assert(removed);
    assert(!db.contains("Petrov"));
    assert(db.find("Petrov") == nullptr);
    assert(db.size() == 2);

    bool missing_removed = db.erase("Smirnov");
    assert(!missing_removed);
    assert(db.size() == 2);

    double avg = get_avg_age(db);
    assert(avg > 28.0 && avg < 29.0);

    int count = 0;
    for (auto it = db.begin(); it != db.end(); ++it) {
        assert(!it.key().empty());
        ++count;
    }
    assert(count == 2);

    return 0;
}