#include "ds/matrix.hpp"
#include <cassert>
#include <utility>
int main() {
    using namespace ds;
    Matrix m1(2), m2(2, 2, 1.0);
    m2 += m1;
    assert(m2.get(0,0) == 2.0);
    assert(m2.get(1,1) == 2.0);
    Matrix m3 = (m1 + m2) * m1 * 4.0 / 2.0 - m2;
    assert(m3.get(0,0) == 4.0);
    assert(m3.get(1,1) == 4.0);
    Matrix moved = std::move(m3);
    assert(moved.get(0,0) == 4.0);
    return 0;
}
