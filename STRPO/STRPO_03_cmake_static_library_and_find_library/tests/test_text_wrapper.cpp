#include "ds/text_wrapper.hpp"

#include <cassert>
#include <sstream>
#include <string>

int main() {
    using namespace ds;
    MyString text("alpha beta gamma delta");
    TextWrapper wrapper(text, 10);
    std::ostringstream out;
    wrapper.print_wrapped(out);
    assert(wrapper.count_lines() == 3);
    assert(out.str() == std::string("alpha beta\ngamma\ndelta"));
    return 0;
}
