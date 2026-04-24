#include "ds/rect.hpp"
#include <cassert>
int main() {
    ds::Rect r;
    assert(r.get_left() == 0);
    r.set_all(1, 5, 6, 2);
    assert(r.get_left() == 1);
    assert(r.get_right() == 5);
    assert(r.get_top() == 6);
    assert(r.get_bottom() == 2);
    return 0;
}
