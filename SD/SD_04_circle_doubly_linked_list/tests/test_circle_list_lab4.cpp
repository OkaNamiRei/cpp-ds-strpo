#include "ds/circle_list.hpp"

#include <cassert>
#include <cstdio>
#include <sstream>
#include <string>

int main() {
    using namespace ds;

    Circle a(0.0, 0.0, 2.0);
    Circle b(1.0, 1.0, 1.0);
    Circle c(2.0, 2.0, 3.0);
    Circle d(-1.0, 5.0, 0.5);

    CircleList list;
    assert(list.empty());

    list.push_back(a);
    list.push_front(b);
    list.push_back(c);
    list.push_back(b);
    assert(list.size() == 4);

    assert(list.remove_first(b));
    assert(list.size() == 3);

    std::size_t removed = list.remove_all(b);
    assert(removed == 1);
    assert(list.size() == 2);

    list.push_back(d);
    list.sort_by_area();

    std::ostringstream out;
    out << list;
    const std::string text = out.str();
    assert(text.find("r=0.5") < text.find("r=2"));
    assert(text.find("r=2") < text.find("r=3"));

    list.save_to_file("test_lab4_circles.txt");
    CircleList loaded;
    loaded.load_from_file("test_lab4_circles.txt");
    std::ostringstream out_loaded;
    out_loaded << loaded;
    assert(out_loaded.str() == out.str());

    CircleList copied(loaded);
    std::ostringstream out_copied;
    out_copied << copied;
    assert(out_copied.str() == out.str());

    CircleList moved(std::move(copied));
    std::ostringstream out_moved;
    out_moved << moved;
    assert(out_moved.str() == out.str());

    moved.clear();
    assert(moved.empty());

    std::remove("test_lab4_circles.txt");
    return 0;
}
