#include "ds/rect.hpp"
#include <cassert>
int main() {
    ds::Rect r(1, 3, 4, 2);
    r.inflate(1);
    assert(r.get_left() == 0);
    assert(r.get_right() == 4);
    r.move(2, 1);
    assert(r.get_left() == 2);
    assert(r.get_bottom() == 2);
    return 0;
}
