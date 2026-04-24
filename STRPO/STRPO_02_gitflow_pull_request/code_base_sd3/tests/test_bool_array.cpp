#include "ds/bool_array.hpp"
#include <cassert>
int main() {
    using namespace ds;
    BoolArray ar1(10);
    BoolArray ar2(5, true);
    BoolArray ar3(ar2);
    assert(ar3.size() == 5);
    assert(ar3[0]);
    ar1[4] = ar1[6] = true;
    ar1[2] = (!ar1[6] && ar1[8]) || (ar1[0] != true);
    assert(ar1[2] == true);
    assert(ar1[4] == true);
    assert(ar1[6] == true);
    ar1.resize(12, true);
    assert(ar1.size() == 12);
    assert(ar1[10] == true);
    assert(ar1[11] == true);
    ar1.resize(4, true);
    assert(ar1.size() == 4);
    assert(ar1[2] == true);
    return 0;
}
