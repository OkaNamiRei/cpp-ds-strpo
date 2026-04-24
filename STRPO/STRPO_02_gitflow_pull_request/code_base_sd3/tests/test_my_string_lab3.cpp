#include "ds/my_string.hpp"
#include <cassert>
#include <sstream>
#include <utility>
int main() {
    using namespace ds;
    MyString s1("abc"), s2("ab"), s3 = s1;
    assert(s2 < s1);
    assert(s1 == s3);
    assert(s1 != s2);
    assert(s1 <= s3);
    assert("ab" == s2);
    assert("aba" < s1);
    assert("aba" <= s3);
    s1 += s2 += "111";
    assert(s2 == "ab111");
    assert(s1 == "abcab111");
    MyString s4;
    s4 += "222" + s1 + "333";
    assert(s4 == "222abcab111333");
    s1[0] = s1[1] = 'd';
    assert(s1 == "ddcab111");
    std::istringstream input("hello stream\n");
    MyString read;
    input >> read;
    assert(read == "hello stream");
    MyString moved = std::move(read);
    assert(moved == "hello stream");
    assert(read.empty());
    return 0;
}
