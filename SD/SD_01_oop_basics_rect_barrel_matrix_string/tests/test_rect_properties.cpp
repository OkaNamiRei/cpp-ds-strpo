#include "ds/rect.hpp"
#include <cassert>
int main() {
    ds::Rect r(1, 5, 7, 2);
    assert(r.get_width() == 4);
    assert(r.get_height() == 5);
    assert(r.get_square() == 20);
    r.set_width(10);
    r.set_height(3);
    assert(r.get_width() == 10);
    assert(r.get_height() == 3);
    return 0;
}
