#include "ds/rect.hpp"
#include <cassert>
int main() {
    ds::Rect a(0, 2, 2, 0);
    ds::Rect b(1, 4, 3, -1);
    ds::Rect c = ds::bounding_rect(a, b);
    assert(c.get_left() == 0);
    assert(c.get_right() == 4);
    assert(c.get_top() == 3);
    assert(c.get_bottom() == -1);
    return 0;
}
