#include "ds/circle_list.hpp"

#include <cstdio>
#include <iostream>

int main() {
    using namespace ds;

    Circle c1(0.0, 0.0, 2.0);
    Circle c2(1.0, 1.0, 1.0);
    Circle c3(2.0, -1.0, 3.0);
    Circle c4(1.0, 1.0, 1.0);

    CircleList list;

    std::cout << "=== push_back / push_front ===\n";
    list.push_back(c1);
    list.push_front(c2);
    list.push_back(c3);
    list.push_back(c4);
    std::cout << list << "\n\n";

    std::cout << "=== remove_first ===\n";
    std::cout << "removed: " << std::boolalpha << list.remove_first(c2) << "\n";
    std::cout << list << "\n\n";

    std::cout << "=== remove_all ===\n";
    std::size_t removed = list.remove_all(c4);
    std::cout << "removed count: " << removed << "\n";
    std::cout << list << "\n\n";

    std::cout << "=== add duplicate and sort_by_area ===\n";
    list.push_front(c2);
    list.push_back(Circle(-2.0, 4.0, 0.5));
    list.sort_by_area();
    std::cout << list << "\n\n";

    std::cout << "=== save_to_file / load_from_file ===\n";
    list.save_to_file("lab4_circles.txt");

    CircleList loaded;
    loaded.load_from_file("lab4_circles.txt");
    std::cout << loaded << "\n\n";

    std::cout << "=== clear ===\n";
    loaded.clear();
    std::cout << loaded << '\n';

    std::remove("lab4_circles.txt");
    return 0;
}
